#include "prolib.h"

//int pow_int(int base, unsigned int index)
//{
//    int result = 1;
//    for(unsigned int i = 0; i < index; ++i)
//    {
//        result = result * base;
//    }
//    return result;
//}

//int String_to_char(char *tarStr, unsigned int length)
//{
//    int result = 0;
//    for(unsigned int i = 0; i < length; ++i)
//    {
//        result += (tarStr[i] - '0') * pow_int(10, length - i - 1);
//    }
//    return result;
//}

Time::Time(int time)
{
    ms = time % 1000;
    time = time / 1000;
    s = time % 60;
    time = time / 60;
    m = time % 60;
    h = time / 60;
}


unsigned char* QString_to_IP(QString tarStr)
{
    unsigned char* IP = new unsigned char[4];
    int index = 0, lastIndex = 0;
    for(int i = 0; i < 4; ++i)
    {
        index = tarStr.indexOf('.', lastIndex);
        int IPLength = index == -1 ? -1 : index - lastIndex;
        if(index == -1)
        {

        }
        int tempIP = tarStr.mid(lastIndex, IPLength).toInt();
        if(tempIP >= 0 && tempIP <= 255)
        {
            IP[i] = (unsigned char)tempIP;
        }
        else
        {
            return nullptr;
        }
        lastIndex = index + 1;
    }
    return IP;
}
