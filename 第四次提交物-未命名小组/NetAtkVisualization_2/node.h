#ifndef NODE_H
#define NODE_H

#include "siglib.h"

#define template_V template<typename ValueType>
#define Node_V Node<ValueType>

template_V
class Node
{
public:
    ValueType value;
    Node* left;
    Node* right;
public:
    Node();
    Node(ValueType _value);

    void leftInsert(Node_V* target);
    void rightInsert(Node_V* target);
//    bool leftExist(ValueType tarValue);
//    bool rightExist(ValueType tarValue);
    Signal leftDelete(bool completely = false);
    Signal rightDelete(bool completely = false);
};

template_V
Node_V::Node()
{
    left = nullptr;
    right = nullptr;
}

template_V
Node_V::Node(ValueType _value) :
    value(_value)
{
    left = nullptr;
    right = nullptr;
}

template_V
void Node_V::leftInsert(Node<ValueType> *target)
{
    Node_V* temp = left;
    left = target;
    target ->left = temp;
}

template_V
void Node_V::rightInsert(Node<ValueType> *target)
{
    Node_V* temp = right;
    right = target;
    target ->right = temp;
}

//template_V
//bool Node_V::leftExist(ValueType tarValue)
//{
//    if(left == nullptr)
//    {
//        return false;
//    }
//    else
//    {
//        return (left ->leftExist(tarValue) || left ->rightExist(tarValue));
//    }
//}

//template_V
//bool Node_V::rightExist(ValueType tarValue)
//{
//    if(right == nullptr)
//    {
//        return false;
//    }
//    else
//    {
//        return (right ->rightExist(tarValue) || right ->leftExist(tarValue));
//    }
//}

template_V
Signal Node_V::leftDelete(bool completely)
{
    if(left == nullptr)
    {
        return Signal_unchange;
    }
    else if(completely)
    {
        left ->leftDelete(true);
        left ->rightDelete(true);
        delete left;
        left = nullptr;
        return Signal_normal;
    }
    else
    {
        Signal signal = left ->rightDelete(true) == Signal_unchange ? Signal_normal : Signal_over_delete;
        Node_V* temp = left;
        left = left ->left;
        delete temp;
        return signal;
    }
}

template_V
Signal Node_V::rightDelete(bool completely)
{
    if(right == nullptr)
    {
        return Signal_unchange;
    }
    else if(completely)
    {
        right ->leftDelete(true);
        right ->rightDelete(true);
        delete right;
        right = nullptr;
        return Signal_normal;
    }
    else
    {
        Signal signal = right ->leftDelete(true) == Signal_unchange ? Signal_normal : Signal_over_delete;
        Node_V* temp = right;
        right = right ->right;
        delete temp;
        return signal;
    }
}

#endif // NODE_H
