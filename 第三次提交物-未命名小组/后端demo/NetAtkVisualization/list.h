#ifndef LIST_H
#define LIST_H

#include "node.h"

#define List_V List<ValueType>

template_V
class List
{
public:
    Node_V* head;
    Node_V* tail;

public:
    List();

    Signal addNode(ValueType value, bool checkExist = false);
    void deleteNode(Node_V* tarNode);
    bool existNode(ValueType value);
};

template_V
List_V::List()
{
    head = new Node_V();
    tail = new Node_V();
    head ->right = tail;
    tail ->left = head;
}

template_V
Signal List<ValueType>::addNode(ValueType value, bool checkExist)
{
    if(checkExist && existNode(value))
    {
        return Signal_existed;
    }
    else
    {
        Node_V* newNode = new Node_V(value);
        Node_V* preNode = tail ->left;
        preNode ->right = newNode;
        newNode ->left = preNode;
        newNode ->right = tail;
        tail ->left = newNode;
        return Signal_normal;
    }
}

template_V
void List_V::deleteNode(Node<ValueType> *tarNode)
{
    Node_V* preNode = tarNode ->left;
    Node_V* lastNode = tarNode ->right;
    preNode ->right = lastNode;
    lastNode ->left = preNode;
    delete tarNode;
}

template_V
bool List_V::existNode(ValueType value)
{
    return head ->rightExist(value);
}

#endif // LIST_H
