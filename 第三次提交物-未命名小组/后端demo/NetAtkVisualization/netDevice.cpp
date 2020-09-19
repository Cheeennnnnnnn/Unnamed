#include "netDevice.h"

NetDevice::NetDevice()
{

}

NetDevice::NetDevice(unsigned char _IP_1, unsigned char _IP_2, unsigned char _IP_3, unsigned char _IP_4) :
    IP{_IP_1, _IP_2, _IP_3, _IP_4},
    portList(new List_us)
{

}

Signal NetDevice::addPort(unsigned short port)
{
    if(portList ->existNode(port))
    {
        return Signal_existed;
    }
    else
    {
        portList ->addNode(port);
        return Signal_normal;
    }
}

