
#ifndef DATAREADER_H
#define DATAREADER_H

#include <QThread>
#include <QFile>
#include <sys/time.h>
#include <windows.h>
#include <QMessageBox>

#include "csvProcessor.h"
#include "signalSenter.h"

class DataReader_csv : public QThread
{
public:
    QString filePath;
    QFile* csvFile;
    long long fileSize;
    int maxTimeStamp;
    CsvProcessor* csvProcessor;

    float rate;   //倍速
    int cycle;  //数据刷新周期
    int validTime;  //数据有效时间
    bool keepReading;   //是否保持读取
    int timeIndex;  //当前读取时间索引
    CsvData* dataIndex;

public:
    DataReader_csv(QString _filePath, float _rate = 1, int _cycle = 100, int _validTime = 300000);
    ~DataReader_csv();

    void setStartTime(int startTime);
    Signal solveData(CsvData csvData);

private:
    virtual void run();
};

#endif // DATAREADER_H
