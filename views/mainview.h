#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QWidget>
#include <QPushButton>

#include "chartview.h"

class MainView : public QWidget
{
    Q_OBJECT

public:
    explicit MainView(QWidget* parent = nullptr);
    ChartView* chart() const;
    QPushButton* startButton() const;
    QPushButton* pauseButton() const;
    QPushButton* stopButton() const;

signals:

private:
    ChartView* _chart;
    QPushButton* _startButton;
    QPushButton* _pauseButton;
    QPushButton* _stopButton;

};

#endif // MAINVIEW_H
