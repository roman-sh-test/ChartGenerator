#ifndef GENERATORTHREAD_H
#define GENERATORTHREAD_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>

#include "models/generateddata.h"

class GeneratorThread : public QThread
{
    Q_OBJECT
public:
    explicit GeneratorThread(QObject* parent = nullptr);
    void stop();

signals:
    void dataReady();
    void data(GeneratedData data);

protected:
    void run() override;

private:
    GeneratedData generateData();
    bool needToStop();

private:
    QMutex _mutex;
    bool _needStop;

};

#endif // GENERATORTHREAD_H
