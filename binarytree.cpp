/*****************************************************
	^> File Name: binarytree.cpp
	^> Author: AoEiuV020
	^> Mail: 490674483@qq.com
	^> Created Time: 2015/10/23 - 10:19:25
****************************************************/
#include <iostream>
#include <cstdio>
template<class T>
class BTNode
{
	public:
		T element;
		unsigned weight;
		BTNode<T> *leftChild,*rightChild,*parent;
		BTNode(const unsigned &w=1,BTNode<T> *l=NULL,BTNode<T> *r=NULL,BTNode<T> *p=NULL);
		BTNode(const T&x,const unsigned &w=1,BTNode<T> *l=NULL,BTNode<T> *r=NULL,BTNode<T> *p=NULL);
};
template<class T>
BTNode<T>::BTNode(const unsigned &w,BTNode<T> *l,BTNode<T> *r,BTNode<T> *p)
{
	weight=w;
	leftChild=l;
	rightChild=r;
	parent=p;
}

template<class T>
BTNode<T>::BTNode(const T&x,const unsigned &w,BTNode<T> *l,BTNode<T> *r,BTNode<T> *p)
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
	protected:
	BTNode<T> *root;
	public:
	BinaryTree();
	void setLeftChild(const BinaryTree<T> &left,const T &element,const unsigned &weight=1);
	void setRightChild(const BinaryTree<T> &right,const T &element,const unsigned &weight=1);
	~BinaryTree();
	T &Root();
};
template<class T>
BinaryTree<T>::BinaryTree()
{
	root=new BTNode<T>;
}
template<class T>
void BinaryTree<T>::setLeftChild(const BinaryTree<T> &left,const T &element,const unsigned &weight=1)
{
	if(root->leftChild)
	{
		delete root->leftChild;
	}
	root->leftChild=new BTNode<T>;
	root->leftChild->element=element;
	root->leftChild->weight=weight
}
template<class T>
void BinaryTree<T>::setRightChild(const BinaryTree<T> &right,const T &element,const unsigned &weight=1)
{
	if(root->rightChild)
	{
		delete root->rightChild;
	}
	root->rightChild=new BTNode<T>;
	root->rightChild->element=element;
	root->rightChild->weight=weight
}
template<class T>
BinaryTree<T>::~BinaryTree()
{
	delete root;
}
template<class T>
T &BinaryTree<T>::Root()
{
	return root->element;
}
using namespace std;
int main(int argc, char **argv)
{
	BinaryTree<char> bt;
	//printf("%p,%p,%p;\n",bt.Root(),bt.Root()->leftChild,bt.Root()->rightChild);
	printf("%d\n",bt.Root());
	return 0;
}
