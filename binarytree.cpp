/*****************************************************
	^> File Name: binarytree.cpp
	^> Author: AoEiuV020
	^> Mail: 490674483@qq.com
	^> Created Time: 2015/10/23 - 10:19:25
****************************************************/
#include <iostream>
template<class T>
class BTNode
{
	public:
		T element;
		unsigned weight;
		BTNode<T> *leftChild,*rightChild,*parent;
		BTNode(const T&x,const unsigned &w=0,BTNode<T> *l=NULL,BTNode<T> *r=NULL);
};
template<class T>
BTNode(const T&x,const unsigned &w=0,BTNode<T> *l=NULL,BTNode<T> *r=NULL,BTNode<T> *p);
{
	element=x;
	weight=w;
	leftChild=l;
	rightChild=r;
	parent=p;
}

template<class T>
class BinaryTree
{
};
using namespace std;
int main(int argc, char **argv)
{

	return 0;
}
