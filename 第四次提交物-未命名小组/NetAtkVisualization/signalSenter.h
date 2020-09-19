#ifndef SIGNALSENTER_H
#define SIGNALSENTER_H

#include <QObject>

class SignalSenter : public QObject
{
    Q_OBJECT
public:
    explicit SignalSenter(QObject *parent = nullptr);

signals:
    emit void readData(QString);
    emit void timeLapse(int);

public slots:
};

extern SignalSenter* signalSenter;

#endif // SIGNALSENTER_H
