#ifndef CSVDATA_H
#define CSVDATA_H

#include "protocol.h"
#include "prolib.h"

class CsvData
{    
public:
    int timeStamp;
    unsigned char* s_Device_IP;
    unsigned short s_Device_port;
    unsigned char* d_Device_IP;
    unsigned short d_Device_port;
    QString protocol;
    unsigned short length;

public:
    CsvData();
    CsvData(QString data);
};

#endif // CSVDATA_H
