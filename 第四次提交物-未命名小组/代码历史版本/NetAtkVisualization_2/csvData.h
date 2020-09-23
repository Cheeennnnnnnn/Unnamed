#ifndef CSVDATA_H
#define CSVDATA_H

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

    int times;

public:
    CsvData();
    CsvData(QString data);

    bool operator ==(CsvData data);
};

#endif // CSVDATA_H
