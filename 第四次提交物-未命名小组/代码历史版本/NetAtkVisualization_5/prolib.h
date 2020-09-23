#ifndef PROLIB_H
#define PROLIB_H

#include <QString>

//int pow_int(int base, unsigned int index);
//int String_to_char(char* tarStr, unsigned int length);
//unsigned char* String_to_IP(char* tarStr);

#define template_V template<typename ValueType>

template<typename ValueType1, typename ValueType2>
class Tuple
{
public:
    ValueType1 value1;
    ValueType2 value2;

public:
    Tuple(ValueType1 _value1, ValueType2 _value2);
};

template<typename ValueType1, typename ValueType2>
Tuple<ValueType1, ValueType2>::Tuple(ValueType1 _value1, ValueType2 _value2) :
    value1(_value1),
    value2(_value2)
{

}

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

template_V
inline bool notIn(ValueType n, ValueType left, ValueType right)
{
    return n < left || n > right;
}

template_V
void copyArray(ValueType* newArray, ValueType* srcArray, int length)
{
    for(int i = 0; i < length; ++i)
    {
        newArray[i] = srcArray[i];
    }
}

template_V
bool cmpArray(ValueType* array1, ValueType* array2, int length)
{
    for(int i = 0; i < length; ++i)
    {
        if(array1[i] != array2[i])
        {
            return false;
        }
    }
    return true;
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
