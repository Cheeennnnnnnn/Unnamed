#ifndef POINTERWITHNO_H
#define POINTERWITHNO_H

#include "node.h"

#define template_V template<typename ValueType>
#define PointerWithNo_V PointerWithNo<ValueType>

template_V
class PointerWithNo
{
public:
    Node_V* pointer;
    int no;

public:
    PointerWithNo(Node_V* _pointer, int _no);
};

template_V
PointerWithNo_V::PointerWithNo(Node_V *_pointer, int _no) :
    pointer(_pointer),
    no(_no)
{

}

#endif // POINTERWITHNO_H
