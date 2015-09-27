/*****************************************************
	^> File Name: list.cpp
	^> Author: AoEiuV020
	^> Mail: 490674483@qq.com
	^> Created Time: 2015/09/27 - 18:16:39
****************************************************/
#include <iostream>
template <typename T>
class List
{
private:
    struct Node;
    Node *head,*tail;
    int theSize;
    void init();
public:
    List();
    int size()const;
    bool empty()const;
    T &front();
    const T &front()const;
    T &back();
    const T &back()const;
    void push_front(const T&);
    void push_back(const T&);
    bool pop_front();
    bool pop_back();
    bool insert(int,const T&);
    bool erase(int);
    bool erase(int,int);
    void clear();
    ~List();
};
template <typename T>
struct List<T>::Node
{
    T data;
    Node *prev;
    Node *next;
};
template <typename T>
void List<T>::init()
{
    head=new Node();
    tail=new Node();
    head->prev=nullptr;
    head->next=tail;
    tail->prev=head;
    tail->next=nullptr;
    theSize=0;
}
template <typename T>
List<T>::List()
{
    init();
}
template <typename T>
List<T>::~List()
{
    Node *node;
    node=head;
    while(head->next!=tail)
    {
        head=head->next;
        delete node;
    }
    delete head;
	delete tail;
}
template <typename T>
int List<T>::size()const
{
    return theSize;
}
template <typename T>
bool List<T>::empty()const
{
    return theSize==0;
}
template <typename T>
T &List<T>::front()
{
    return head->data;
}
template <typename T>
const T &List<T>::front()const
{
    return head->next->data;
}
template <typename T>
T &List<T>::back()
{
    return tail->prev->data;
}
template <typename T>
const T &List<T>::back()const
{
    return tail->data;
}
template <typename T>
void List<T>::push_front(const T &obj)
{
    Node *node;
    node=new Node();
    head->data=obj;
    head->prev=node;
    node->prev=nullptr;
    node->next=head;
    head=node;
}
template <typename T>
void List<T>::push_back(const T &obj)
{
    Node *node;
    node=new Node();
    tail->data=obj;
    tail->next=node;
    node->next=nullptr;
    node->prev=tail;
    tail=node;
}
template <typename T>
bool List<T>::pop_front()
{
    if(head->next==tail)
    {
        return false;
    }
    Node *node;
    node=head;
    head=head->next;
    head->prev=nullptr;
    delete node;
    return true;
}
template <typename T>
bool List<T>::pop_back()
{
    if(head->next==tail)
    {
        return false;
    }
    Node *node;
    node=tail;
    tail=tail->prev;
    tail->next=nullptr;
    delete node;
    return true;
}
template <typename T>
bool List<T>::insert(const int index,const T &obj)
{
    Node *p,*n;//prev,next,
    p=head;
    n=p->next;
    for(int i=0;i<index;++i)
    {
        p=n;
        n=p->next;
    }
    Node *node;
    node=new Node();
    node->data=obj;
    p->next=node;
    node->next=n;
    node->prev=p;
    n->prev=node;
	return true;
}
using namespace std;
int main()
{
    List<int> li;
    int n=20;
    for(int i=0; i<n; ++i)
    {
        li.push_front(i);
    }
    for(int i=0; i<n; ++i)
    {
        cout<<li.back()<<endl;
        li.pop_back();
    }
    return 0;
}

