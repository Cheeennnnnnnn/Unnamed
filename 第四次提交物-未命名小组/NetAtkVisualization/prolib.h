#ifndef PROLIB_H
#define PROLIB_H

#include <QString>

//int pow_int(int base, unsigned int index);
//int String_to_char(char* tarStr, unsigned int length);
//unsigned char* String_to_IP(char* tarStr);

class Time
{
public:
    int h;
    int m;
    int s;
    int ms;

public:
    Time(int time);
};

unsigned char* QString_to_IP(QString tarStr);

inline QString IP_to_QString(unsigned char* tarIP)
{
    return QString::number(tarIP[0]) + "." + QString::number(tarIP[1]) + "." + QString::number(tarIP[2]) + "." + QString::number(tarIP[3]);
}

template<typename ValueType>
inline bool notIn(ValueType n, ValueType left, ValueType right)
{
    return n < left || n > right;
}

//inline char* QString_to_String(QString oriQString)   //QString转字符串
//{
//    char* string = nullptr;
//    QByteArray byteArray = oriQString.toLatin1();
//    string = (char *)malloc(byteArray.length() + 1);
//    memset(string, 0, byteArray.length());
//    memcpy(string, byteArray.data(), byteArray.length());
//    string[byteArray.length()] = '\0';
//    return string;
//}


#endif // PROLIB_H
