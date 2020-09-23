#include "netDevice.h"

//NetDevice::NetDevice()
//{
//    sendTimes = 0;
//    receiveTimes = 0;
//}

NetDevice::NetDevice(unsigned char _IP_1, unsigned char _IP_2, unsigned char _IP_3, unsigned char _IP_4) :
    IP{_IP_1, _IP_2, _IP_3, _IP_4}/*,
    portList(new List_us)*/
{
    sendTimes = 0;
    receiveTimes = 0;
}

NetDevice::NetDevice(unsigned char *_IP) :
    IP{_IP[0], _IP[1], _IP[2], _IP[3]}/*,
    portList(new List_us)*/
{
    sendTimes = 0;
    receiveTimes = 0;
}

bool NetDevice::operator ==(NetDevice device)
{
    return IP[0] == device.IP[0] && IP[1] == device.IP[1] && IP[2] == device.IP[2] && IP[3] == device.IP[3];
}

bool NetDevice::operator ==(unsigned char *ip)
{
    return IP[0] == ip[0] && IP[1] == ip[1] && IP[2] == ip[2] && IP[3] == ip[3];
}

//Signal NetDevice::addPort(unsigned short port)
//{
//    if(portList ->indexOfNode(port) != nullptr)
//    {
//        return Signal_existed;
//    }
//    else
//    {
//        portList ->addNode(port);
//        return Signal_normal;
//    }
//}

