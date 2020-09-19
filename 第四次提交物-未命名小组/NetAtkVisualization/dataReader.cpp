#include "dataReader.h"

#include <QDebug>

DataReader_csv::DataReader_csv(QString _filePath, float _rate, int _cycle, int _validTime) :
    filePath(_filePath),
    csvFile(new QFile(_filePath)),
    fileSize(csvFile ->size()),
    csvProcessor(new CsvProcessor()),
    rate(_rate),
    cycle(_cycle),
    validTime(_validTime),
    keepReading(true),
    timeIndex(0)
{
    csvFile ->open(QIODevice::ReadOnly | QIODevice::Text);
    csvFile ->seek(fileSize > 200 ? fileSize - 200 : 0);
    CsvData* tempData = new CsvData(csvFile ->readLine());
    while(!csvFile ->atEnd())
    {
        delete tempData;
        tempData = new CsvData(csvFile ->readLine());
    }
    maxTimeStamp = tempData ->timeStamp;
    delete tempData;

    csvFile ->seek(0);
    csvFile ->readLine();
    dataIndex = new CsvData(csvFile ->readLine());
}

DataReader_csv::~DataReader_csv()
{
    csvFile ->close();
    delete csvFile;
}

void DataReader_csv::setStartTime(int startTime)
{
    keepReading = false;

    long long leftIndex = 0, rightIndex = fileSize;
    while(rightIndex - leftIndex > 200)
    {
        long long midIndex = (rightIndex + leftIndex) / 2;
        csvFile ->seek(midIndex);
        csvFile ->readLine();
        delete dataIndex;
        dataIndex = new CsvData(csvFile ->readLine());
        if(dataIndex ->timeStamp > startTime)
        {
            rightIndex = midIndex;
        }
        else
        {
            leftIndex = midIndex;
        }
    }
    csvFile ->seek(leftIndex > 200 ? leftIndex - 200 : 0);
    csvFile ->readLine();
    do
    {
        delete dataIndex;
        dataIndex = new CsvData(csvFile ->readLine());
    }while(dataIndex ->timeStamp < startTime && !csvFile ->atEnd());

    timeIndex = startTime;

    keepReading = true;
}

Signal DataReader_csv::solveData(CsvData csvData)
{

}

void DataReader_csv::run()
{
    while(keepReading)
    {
        struct timeval tpstart,tpend;
        long long timeuse;
        gettimeofday(&tpstart, nullptr);

        if(timeIndex >= dataIndex ->timeStamp)
        {
            do
            {
//                csvProcessor ->dataList ->addNode(*dataIndex, true);


//                switch(solveData(*dataIndex))
//                {

//                }
                Time time(dataIndex ->timeStamp);
                QString message = QString("-%1:%2:%3:%4- IP为 %5 的设备的 %6 端口向IP为 %7 的设备的 %8 端口发送了一个长度为 %9 的使用 %10 协议的数据包")
                        .arg(QString::number(time.h)).arg(QString::number(time.m)).arg(QString::number(time.s)).arg(QString::number(time.ms))
                        .arg(IP_to_QString(dataIndex ->s_Device_IP)).arg(dataIndex->s_Device_port)
                        .arg(IP_to_QString(dataIndex ->d_Device_IP)).arg(dataIndex->d_Device_port)
                        .arg(dataIndex->length).arg(dataIndex ->protocol);
                emit signalSenter ->readData(message);

                delete dataIndex;
                dataIndex = new CsvData(csvFile ->readLine());
            }
            while(timeIndex >= dataIndex ->timeStamp);
        }

        if(csvFile ->atEnd())
        {
            QMessageBox::information(nullptr, "处理完毕", "文件处理完毕！");
        }

        gettimeofday(&tpend, nullptr);
        timeuse=(1000000* (tpend.tv_sec - tpstart.tv_sec) + tpend.tv_usec - tpstart.tv_usec) / 1000;

        if(timeuse < cycle)
        {
            Sleep(cycle - timeuse);
            timeIndex += cycle * rate;
            emit signalSenter ->timeLapse(timeIndex);
        }
        else
        {
            QMessageBox::warning(nullptr, "性能不足", "刷新周期过短或运算量过大，设备性能不足！");
            wait();
        }
    }
}
