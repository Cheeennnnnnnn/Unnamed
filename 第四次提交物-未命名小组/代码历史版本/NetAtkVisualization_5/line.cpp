#include "line.h"

Line::Line()
{

}

Line::Line(unsigned char *_sIP, unsigned char *_dIP) :
    s_Device_IP(new unsigned char[4]),
    d_Device_IP(new unsigned char[4]),
    times(1)
{
    copyArray(s_Device_IP, _sIP, 4);
    copyArray(d_Device_IP, _dIP, 4);
}
