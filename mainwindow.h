#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSemaphore>

#include "views/mainview.h"
#include "generatorthread.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    enum class State {
        Running,
        WaitForPause,
        Paused,
        WaitForStop,
        Stopped
    };

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void updateForState(State newState);
    void setState(State newState);
    void updateButtons();

private slots:
    void processDataReady();
    void processData(GeneratedData data);
    void processDataDidSet();
    void processThreadFinished();

    void startPressed();
    void pausePressed();
    void stopPressed();

private:
    MainView* _view;
    GeneratorThread* _thread;
    QSemaphore _semaphore;
    State _threadState;
};
#endif // MAINWINDOW_H
