#include "csvData.h"


//csvData::csvData(double _timeStamp, unsigned char _s_Device_IP[], unsigned short _s_Device_port, unsigned char _d_Device_IP[],
//                 unsigned short _d_Device_port, Protocol _protocol, unsigned short _length) :
//    timeStamp(_timeStamp),
//    s_Device_IP
//{

//}



CsvData::CsvData() :
    timeStamp(0),
    s_Device_IP(nullptr),
    s_Device_port(0),
    d_Device_IP(nullptr),
    d_Device_port(0),
    protocol(Protocol::OTHER),
    length(0)
{

}

CsvData::CsvData(QString data)
{
    int leftIndex, rightIndex;

    rightIndex = data.indexOf(".", 1);
    int integer = QString(data.mid(1, rightIndex - 1)).toInt();
    leftIndex = rightIndex + 1;
    int decimal = QString(data.mid(leftIndex, 3)).toInt();
    timeStamp = integer * 1000 + decimal;

    leftIndex = data.indexOf(",", leftIndex) + 2;
    rightIndex = data.indexOf(",", leftIndex) - 1;
    s_Device_IP = QString_to_IP(data.mid(leftIndex, rightIndex - leftIndex));

    leftIndex = rightIndex + 3;
    rightIndex = data.indexOf(",", leftIndex) - 1;
    s_Device_port = data.mid(leftIndex, rightIndex - leftIndex).toInt();

    leftIndex = rightIndex + 3;
    rightIndex = data.indexOf(",", leftIndex) - 1;
    d_Device_IP = QString_to_IP(data.mid(leftIndex, rightIndex - leftIndex));

    leftIndex = rightIndex + 3;
    rightIndex = data.indexOf(",", leftIndex) - 1;
    d_Device_port = data.mid(leftIndex, rightIndex - leftIndex).toInt();

    leftIndex = rightIndex + 3;
    rightIndex = data.indexOf(",", leftIndex) - 1;
    protocol = data.mid(leftIndex, rightIndex - leftIndex);

    leftIndex = rightIndex + 3;
    rightIndex = data.indexOf("\"", leftIndex);
    length = data.mid(leftIndex, rightIndex - leftIndex).toInt();
}
