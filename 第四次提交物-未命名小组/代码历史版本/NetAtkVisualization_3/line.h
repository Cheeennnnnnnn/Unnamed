#ifndef LINE_H
#define LINE_H

#include "csvData.h"

class line
{
public:
    unsigned char* s_Device_IP;
    unsigned char* d_Device_IP;

    int times;

public:
    line(unsigned char* _sIP, unsigned char* _dIP);

    bool operator ==(CsvData data);
};

#endif // LINE_H
