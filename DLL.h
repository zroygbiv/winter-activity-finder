#ifndef DLL_H
#define DLL_H

#include <memory>
#include "activity.h"

using namespace std;

//////////////////////////////////////NODE CLASS
template<class T>
class Node
{
public:

    Node();
    explicit Node(const T & src_data);
    Node(const Node<T> & src_node);
    ~Node();
    Node<T> & operator=(const Node<T> & rhs);

    template<class U>
    friend ostream & operator<<(ostream & out, Node<U> & rhs);

    Node<T> * get_next();
    Node<T> * get_prev();
    T get_data();
    void set_next(Node<T> *&);
    void set_prev(Node<T> *&);

private:
    T data;
    Node<T> * next;
    Node<T> * prev;
};

//////////////////////////////////////DLL CLASS
template <class T>
class DLL
{
public:
    DLL();
    DLL(const DLL<T> & src);
    ~DLL();

    template<class U>
    friend ostream & operator<<(ostream & out, Node<U> & rhs);

    Node<T> * get_head();
    void push(const T &);
    void append(const T &);
    void copy(const DLL<T> * src);
    void display();

private:
    Node<T> * head;
    Node<T> * tail;

    void display(Node<T> *);
    Node<T> * copy(Node<T> *, Node<T> *);
    void destroy(Node<T> *);

};

#include <iostream>

using namespace std;

/////////////////////////////////////////NODE CLASS

//Default Constructor
template<class T>
Node<T>::Node(): next(nullptr), prev(nullptr) {}

//Constructor
template<class T>
Node<T>::Node(const T & src_data): data(src_data), next(nullptr), prev(nullptr)
{}

//Copy Constructor
template<class T>
Node<T>::Node(const Node<T> & src_node)
{
    data = src_node.data;
    next = src_node.next;
    prev = src_node.prev;
}

//Destructor
template<class T>
Node<T>::~Node<T>()
{
    delete data;
}

//Assignment Operator
template<class T>
Node<T> & Node<T>::operator=(const Node<T> & rhs)
{
    if (this == &rhs) return *this;

    next = rhs.next;
    prev = rhs.prev;
    data = rhs.data;

    return *this;
}

//Insertion Stream Operator
template<class T>
ostream & operator<<(ostream & out, Node<T> & rhs)
{
    out << rhs;
    return out;
}

//Getter Functions
template<class T>
Node<T> * Node<T>::get_next()
{
    return next;
}

template<class T>
Node<T> * Node<T>::get_prev()
{
    return prev;
}

template<class T>
T Node<T>::get_data()
{
    return data;
}

//Setter Functions
template<class T>
void Node<T>::set_next(Node<T> *& new_next)
{
    next = new_next;
}

template<class T>
void Node<T>::set_prev(Node<T> *& new_prev)
{
    prev = new_prev;
}

/////////////////////////////////////////DLL CLASS

//Constructor
template<class T>
DLL<T>::DLL():head(nullptr), tail(nullptr) {}

//Copy Constructor
template<class T>
DLL<T>::DLL(const DLL<T> & src)
{
    if (!src.head) return;
    copy(src);
}

//Destructor
template<class T>
DLL<T>::~DLL()
{
    destroy(head);
}

//Destroy list
template<class T>
void DLL<T>::destroy(Node<T> * head)
{
    if (!head) return;

    Node<T> * temp = head;
    head = head->get_next();
    delete temp;
    destroy(head);
}

//Getter function
template<class T>
Node<T> * DLL<T>::get_head()
{
    return head;
}

//Push New Node
template<class T>
void DLL<T>::push(const T & new_data)
{
    auto * new_node = new Node<T>(new_data);

    if (!head)
    {
        head = new_node;
        tail = head;
    }
    else
    {
        new_node->set_next(head);
        head->set_prev(new_node);
        head = new_node;
    }
}

//Append New Node
template<class T>
void DLL<T>::append(const T & new_data)
{
    auto * new_node = new Node<T>(new_data);

    if (!head)
    {
        head = new_node;
        tail = head;
    }
    else
    {
        tail->set_next(new_node);
        new_node->set_prev(tail);
        tail = new_node;
    }
}

//Copy List Wrapper
template<class T>
void DLL<T>::copy(const DLL<T> * src)
{
    if (!src->head) return;

    head = copy(src->head, head);
}

//Copy List
template<class T>
Node<T> * DLL<T>::copy(Node<T> * src_head, Node<T> * prev)
{
    if (src_head)
    {
        auto * new_node = new Node<T>(src_head->get_data());
        new_node->set_prev(prev);
        Node<T> * temp = copy(src_head->get_next(), new_node);
        new_node->set_next(temp);
        return new_node;
    }

    return nullptr;
}

//Display Wrapper
template<class T>
void DLL<T>::display()
{
    if (!head) return;

    display(head);
}

//Display List
template<class T>
void DLL<T>::display(Node<T> * head)
{
    if (!head) return;

    cout << head->get_data() << endl;
    head = head->get_next();
    display(head);
}

#endif