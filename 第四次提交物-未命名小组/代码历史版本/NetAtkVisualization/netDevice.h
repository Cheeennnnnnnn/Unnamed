#ifndef NETDEVICE_H
#define NETDEVICE_H

#include "list.h"
#include "siglib.h"

#define List_us List<unsigned short>

class NetDevice
{
public:
    unsigned char IP[4];
    List_us* portList;

public:
    NetDevice();
    NetDevice(unsigned char _IP_1, unsigned char _IP_2, unsigned char _IP_3, unsigned char _IP_4);

    Signal addPort(unsigned short port);
};

#endif // NETDEVICE_H
