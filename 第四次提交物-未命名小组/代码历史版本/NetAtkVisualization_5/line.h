#ifndef LINE_H
#define LINE_H

#include "prolib.h"

class Line
{
public:
    unsigned char* s_Device_IP;
    unsigned char* d_Device_IP;

    int times;

public:
    Line();
    Line(unsigned char* _sIP, unsigned char* _dIP);

};

#endif // LINE_H
