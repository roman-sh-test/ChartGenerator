#include "mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , _view{ new MainView(this) }
    , _thread{ new GeneratorThread(this) }
    , _semaphore(1)
    , _threadState(State::Stopped)
{
    QMainWindow window;
    setCentralWidget(_view);

    connect(_thread, &GeneratorThread::dataReady,
            this, &MainWindow::processDataReady,
            Qt::ConnectionType::DirectConnection);

    connect(_thread, &GeneratorThread::data,
            this, &MainWindow::processData,
            Qt::ConnectionType::QueuedConnection);

    connect(_thread, &GeneratorThread::finished,
            this, &MainWindow::processThreadFinished);

    connect(_view->chart(), &ChartView::dataDidSet,
            this, &MainWindow::processDataDidSet);

    connect(_view->startButton(), &QPushButton::pressed,
            this, &MainWindow::startPressed);
    connect(_view->pauseButton(), &QPushButton::pressed,
            this, &MainWindow::pausePressed);
    connect(_view->stopButton(), &QPushButton::pressed,
            this, &MainWindow::stopPressed);

    updateButtons();

    qRegisterMetaType<GeneratedData>("GeneratedData");
}

MainWindow::~MainWindow() {
    _thread->stop();
    _semaphore.release();
    _thread->wait();
}

void MainWindow::updateForState(MainWindow::State newState) {
    setState(newState);
    updateButtons();
}

void MainWindow::setState(MainWindow::State newState) {
    _threadState = newState;
}

void MainWindow::updateButtons() {
    _view->startButton()->setEnabled(_threadState == State::Paused || _threadState == State::Stopped);
    _view->pauseButton()->setEnabled(_threadState == State::Running);
    _view->stopButton()->setEnabled(_threadState == State::Paused || _threadState == State::Running);
}

void MainWindow::processDataReady() {
    // runs in _thread
    // blocks _thread if old data not processed
    _semaphore.acquire();
}

void MainWindow::processData(GeneratedData data) {
    _view->chart()->setData(data);
}

void MainWindow::processDataDidSet() {
    if (_threadState != State::WaitForPause) {
        _semaphore.release();
    }
    else {
        updateForState(State::Paused);
    }
}

void MainWindow::processThreadFinished() {
    updateForState(State::Stopped);
    if (_semaphore.available() == 0) {
        _semaphore.release();
    }
}

void MainWindow::startPressed() {
    updateForState(State::Running);
    if (_thread->isRunning()) {
        // for paused
        _semaphore.release();
    }
    else {
        _thread->start();
    }
}

void MainWindow::pausePressed() {
    updateForState(State::WaitForPause);
    _semaphore.tryAcquire();
}

void MainWindow::stopPressed() {
    updateForState(State::WaitForStop);
    _thread->stop();
    // for paused
    if (_semaphore.available() == 0) {
        _semaphore.release();
    }

}

