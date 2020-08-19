#include "generatorthread.h"

#include <QtCore>

GeneratorThread::GeneratorThread(QObject* parent)
    : QThread(parent)
    , _needStop{ false }
{

}


void GeneratorThread::stop() {
    _mutex.lock();
    _needStop = true;
    _mutex.unlock();
}

void GeneratorThread::run() {
    for (;;) {
        if (needToStop()) {
            return;
        }
        auto vec = generateData();
        if (needToStop()) {
            return;
        }
        emit dataReady();
        if (needToStop()) {
            return;
        }
        emit data(vec);
    }
}

GeneratedData GeneratorThread::generateData() {
    static int add = 0;
    GeneratedData data;
    ++add;
    add %= 10;
    double x = 0.0;
    for (int i = 0; i < 10; ++i) {
        x += QRandomGenerator::global()->bounded(100);
        data.xMax = x > data.xMax ? x : data.xMax;
        data.xMin = x < data.xMin ? x : data.xMin;

        double y = -i*0.5 + add;
        data.yMax = y > data.yMax ? y : data.yMax;
        data.yMin = y < data.yMin ? y : data.yMin;

        QPointF p(x, y);
        data.points.append(p);
    }
    return data;
}

bool GeneratorThread::needToStop() {
    _mutex.lock();
    bool needStop = _needStop;
    _mutex.unlock();
    if (needStop) {
        _mutex.lock();
        _needStop = false;
        _mutex.unlock();
        return true;
    }
    return false;
}


