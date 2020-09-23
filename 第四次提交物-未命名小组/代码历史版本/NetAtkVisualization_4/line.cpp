#include "line.h"

line::line(unsigned char *_sIP, unsigned char *_dIP) :
    s_Device_IP(_sIP),
    d_Device_IP(_dIP),
    times(1)
{

}

bool line::operator ==(CsvData data)
{
    return s_Device_IP[0] == data.s_Device_IP[0] && s_Device_IP[1] == data.s_Device_IP[1] && s_Device_IP[2] == data.s_Device_IP[2] &&
           s_Device_IP[3] == data.s_Device_IP[3] && d_Device_IP[0] == data.d_Device_IP[0] && d_Device_IP[1] == data.d_Device_IP[1] &&
           d_Device_IP[2] == data.d_Device_IP[2] && d_Device_IP[3] == data.d_Device_IP[3];
}
