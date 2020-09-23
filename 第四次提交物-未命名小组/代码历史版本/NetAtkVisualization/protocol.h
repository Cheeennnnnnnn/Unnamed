#ifndef PROTOCOL_H
#define PROTOCOL_H

/*
    网络协议
*/

enum Protocol
{
    OTHER,
    TCP,
    UDP,
    LLMNR,
    NBNS,
    DNS,
    CLDAP,
    DCERPC,
    EPM
};

#endif // PROTOCOL_H
