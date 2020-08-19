#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <QtCharts/QChartView>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QValueAxis>

#include "models/generateddata.h"

class ChartView : public QtCharts::QChartView
{
    Q_OBJECT
public:
    explicit ChartView(QWidget* parent = nullptr);

    void setData(GeneratedData data);

signals:
    void dataDidSet();

private:
    QtCharts::QScatterSeries* _series;
    QtCharts::QValueAxis* _xAxis;
    QtCharts::QValueAxis* _yAxis;

};

#endif // CHARTVIEW_H
