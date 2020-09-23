#ifndef IPHASH_H
#define IPHASH_H

#include <string.h>
#include "prolib.h"

class IPHasher
{
public:
    bool** hashMap;

public:
    IPHasher();
    ~IPHasher();

    void resetHashMap();
    Tuple<int, int> hash(unsigned char* ip);
};

#endif // IPHASH_H
