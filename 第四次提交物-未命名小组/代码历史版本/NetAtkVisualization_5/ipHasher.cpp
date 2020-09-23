#include "ipHasher.h"

IPHasher::IPHasher()
{
    hashMap = new bool*[180];
    for(int i = 0; i < 180; ++i)
    {
        hashMap[i] = new bool[360];
        memset(hashMap[i], 0, 360 * sizeof(bool));
    }
}

IPHasher::~IPHasher()
{
    for(int i = 0; i < 180; ++i)
    {
        delete hashMap[i];
    }
    delete hashMap;
}

void IPHasher::resetHashMap()
{
    for(int i = 0; i < 180; ++i)
    {
        memset(hashMap[i], 0, 360 * sizeof(bool));
    }
}

Tuple<int, int> IPHasher::hash(unsigned char *ip)
{
    int x = (ip[0] * 48 + ip[1] * 65 + ip[2] / 16 * 97) % 360;
    int y = (ip[2] % 16 * 32 + ip[3] * 95) % 180;
    for(int i = 0; i < 180; ++i)
    {
        for(int j = 0; j < 360; ++j)
        {
            if(!hashMap[(y + i) % 180][(x + j) % 360])
            {
                hashMap[(y + i) % 180][(x + j) % 360] = 1;
                return Tuple<int, int>((y + i) % 180, (x + j) % 360);
            }
        }
    }
    return Tuple<int, int>(x, y);
}
