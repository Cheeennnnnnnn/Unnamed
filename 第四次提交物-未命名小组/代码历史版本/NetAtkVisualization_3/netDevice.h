#ifndef NETDEVICE_H
#define NETDEVICE_H

#include "list.h"
#include "siglib.h"

#define List_us List<unsigned short>

class NetDevice
{
public:
    unsigned char IP[4];
//    List_us* portList;

    int sendTimes, receiveTimes;

public:
//    NetDevice();
    NetDevice(unsigned char _IP_1 = 0, unsigned char _IP_2 = 0, unsigned char _IP_3 = 0, unsigned char _IP_4 = 0);
    NetDevice(unsigned char* _IP);

    bool operator ==(NetDevice device);

//    Signal addPort(unsigned short port);
};

#endif // NETDEVICE_H
