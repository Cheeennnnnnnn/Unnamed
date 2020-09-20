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
    protocol(""),
    length(0),
    times(0)
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

    times = 1;
}

bool CsvData::operator ==(CsvData data)
{
    return s_Device_IP[0] == data.s_Device_IP[0] && s_Device_IP[1] == data.s_Device_IP[1] && s_Device_IP[2] == data.s_Device_IP[2] &&
           s_Device_IP[3] == data.s_Device_IP[3] && d_Device_IP[0] == data.d_Device_IP[0] && d_Device_IP[1] == data.d_Device_IP[1] &&
           d_Device_IP[2] == data.d_Device_IP[2] && d_Device_IP[3] == data.d_Device_IP[3] && s_Device_port == data.s_Device_port &&
           d_Device_port == data.d_Device_port && protocol == data.protocol && length == data.length;
}
