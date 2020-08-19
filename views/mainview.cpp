#include "mainview.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QPushButton>

MainView::MainView(QWidget* parent)
    : QWidget(parent)
    , _chart{ new ChartView(this) }
    , _startButton{ new QPushButton("Start", this) }
    , _pauseButton{ new QPushButton("Pause", this) }
    , _stopButton{ new QPushButton("Stop", this) }
{
    // buttons
    QHBoxLayout* buttons = new QHBoxLayout;
    buttons->addWidget(_startButton);
    buttons->addWidget(_pauseButton);
    buttons->addWidget(_stopButton);
    buttons->addStretch();

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addLayout(buttons);

    layout->addWidget(_chart);

    setLayout(layout);

}

ChartView* MainView::chart() const {
    return _chart;

}

QPushButton* MainView::startButton() const {
    return _startButton;
}

QPushButton* MainView::pauseButton() const {
    return _pauseButton;
}

QPushButton* MainView::stopButton() const {
    return _stopButton;
}
