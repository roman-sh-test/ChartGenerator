#include "chartview.h"



ChartView::ChartView(QWidget* parent)
    : QtCharts::QChartView(new QtCharts::QChart(), parent)
    , _series{ new QtCharts::QScatterSeries() }
    , _xAxis{ new QtCharts::QValueAxis }
    , _yAxis{ new QtCharts::QValueAxis }
{
    _series->setName("data");
    _series->setMarkerShape(QtCharts::QScatterSeries::MarkerShapeCircle);
    _series->setMarkerSize(15.0);

    _series->append(0, 6);
    _series->append(2, 4);
    _series->append(3, 8);
    _series->append(7, 4);
    _series->append(10, 5);

    chart()->addAxis(_xAxis, Qt::AlignBottom);
    chart()->addAxis(_yAxis, Qt::AlignLeft);

    chart()->addSeries(_series);
    _series->attachAxis(_xAxis);
    _series->attachAxis(_yAxis);

    chart()->legend()->hide();

    connect(_series, &QtCharts::QScatterSeries::pointsReplaced,
            this, &ChartView::dataDidSet);

}

void ChartView::setData(GeneratedData data) {
    _xAxis->setRange(data.xMin, data.xMax);
    _yAxis->setRange(data.yMin, data.yMax);
    _series->replace(data.points);
}
