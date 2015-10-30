/*****************************************************
	^> File Name: binarytree.cpp
	^> Author: AoEiuV020
	^> Mail: 490674483@qq.com
	^> Created Time: 2015/10/23 - 10:19:25
****************************************************/
#include <iostream>
#include <string>
#include <cstdio>
template<class T>
class BTNode
{
	public:
		T element;
		BTNode<T> *leftChild,*rightChild;
		BTNode(const T&x,BTNode<T> *l=NULL,BTNode<T> *r=NULL);
		BTNode(const BTNode<T> *btn);
};
template<class T>
BTNode<T>::BTNode(const T&x,BTNode<T> *l,BTNode<T> *r)
{
	element=x;
	leftChild=l;
	rightChild=r;
}
template<class T>
BTNode<T>::BTNode(const BTNode<T> *btn)
{
	element=btn->element;
	leftChild=btn->leftChild?new BTNode<T>(btn->leftChild):NULL;
	rightChild=btn->rightChild?new BTNode<T>(btn->rightChild):NULL;
}

template<class T>
class BinaryTree
{
	protected:
	BTNode<T> *root;
	public:
	BinaryTree();
	bool IsEmpty();
	void MakeTree(const T &element,BinaryTree<T> *left=NULL,BinaryTree<T> *right=NULL);
	void Clear(BTNode<T> *bt);
	int Height(BTNode<T> *bt=NULL);
	int Leaf(BTNode<T> *bt=NULL);
	BinaryTree<T> &operator=(BinaryTree<T> &bt);
	void Swap(BTNode<T> *bt=NULL);
	void PreOrder(BTNode<T> *btn,std::ostream &out,std::string separate="");
	void InOrder(BTNode<T> *btn,std::ostream &out,std::string separate="");
	void PostOrder(BTNode<T> *btn,std::ostream &out,std::string separate="");
	~BinaryTree();
	BTNode<T> *Root();
};
template<class T>
BinaryTree<T>::BinaryTree()
{
	root=NULL;
}
template<class T>
bool BinaryTree<T>::IsEmpty()
{
	return root==NULL;
}
template<class T>
BTNode<T> *BinaryTree<T>::Root()
{
	return root;
}
template<class T>
void BinaryTree<T>::MakeTree(const T &element,BinaryTree<T> *left,BinaryTree<T> *right)
{
	root=new BTNode<T>(element,left?left->root:NULL,right?right->root:NULL);
	left?(left->root=NULL):0;
	right?(right->root=NULL):0;

}
template<class T>
void BinaryTree<T>::Clear(BTNode<T> *bt)
{
	if(!bt) { return; }
	if(bt->leftChild) { Clear(bt->leftChild); }
	if(bt->rightChild) { Clear(bt->rightChild); }
	delete root;
	root=NULL;
}
template<class T>
int BinaryTree<T>::Height(BTNode<T> *bt)
{
	int height,leftHeight,rightHeight;
	if(!bt) { return 0; }
	leftHeight=bt->leftChild?Height(bt->leftChild):0;
	rightHeight=bt->rightChild?Height(bt->rightChild):0;
	height=leftHeight>rightHeight?leftHeight:rightHeight;
	return height+1;
}
template<class T>
int BinaryTree<T>::Leaf(BTNode<T> *bt)
{
	int leaf,leftLeaf,rightLeaf;
	if(!bt) { return 0; }
	leftLeaf=bt->leftChild?Leaf(bt->leftChild):0;
	rightLeaf=bt->rightChild?Leaf(bt->rightChild):0;
	leaf=leftLeaf+rightLeaf;
	return leaf==0?1:leaf;
}
template<class T>
BinaryTree<T> &BinaryTree<T>::operator=(BinaryTree<T> &bt)
{
	Clear(root);
	root=new BTNode<T>(bt.Root());
	return *this;
}
template<class T>
void BinaryTree<T>::Swap(BTNode<T> *bt)
{
	BTNode<T> *t;
	if(!bt){return;}
	if(bt->leftChild){Swap(bt->leftChild);}
	if(bt->rightChild){Swap(bt->rightChild);}
	t=bt->leftChild;
	bt->leftChild=bt->rightChild;
	bt->rightChild=t;
}
template<class T>
void BinaryTree<T>::PreOrder(BTNode<T> *btn,std::ostream &out,std::string separate)
{
	if(!btn){return;}
	out<<(btn->element)<<separate;
	PreOrder(btn->leftChild,out,separate);
	PreOrder(btn->rightChild,out,separate);
}
template<class T>
void BinaryTree<T>::InOrder(BTNode<T> *btn,std::ostream &out,std::string separate)
{
	if(!btn){return;}
	InOrder(btn->leftChild,out,separate);
	out<<(btn->element)<<separate;
	InOrder(btn->rightChild,out,separate);
}
template<class T>
void BinaryTree<T>::PostOrder(BTNode<T> *btn,std::ostream &out,std::string separate)
{
	if(!btn){return;}
	PostOrder(btn->leftChild,out,separate);
	PostOrder(btn->rightChild,out,separate);
	out<<(btn->element)<<separate;
}
template<class T>
BinaryTree<T>::~BinaryTree()
{
	Clear(root);
}
using namespace std;
int main(int argc, char **argv)
{
	BinaryTree<char> bt,a,b,c,t;
	a.MakeTree('a');
	b.MakeTree('b',&a);
	a.MakeTree('c');
	c.MakeTree('d',&a,&b);
	a.MakeTree('e');
	b.MakeTree('f',NULL,&a);
	bt.MakeTree('s',&c,&b);
	t=bt;
	printf("%d\n",bt.Root()->element);
	printf("%d\n",bt.Height(bt.Root()));
	printf("%d\n",bt.Leaf(bt.Root()));
	bt.PreOrder(bt.Root(),cout," ");
	cout<<endl;
	bt.InOrder(bt.Root(),cout," ");
	cout<<endl;
	bt.PostOrder(bt.Root(),cout," ");
	cout<<endl;
	bt.Clear(bt.Root());
	bt.Clear(bt.Root());
	bt.MakeTree('s');
	printf("%d\n",bt.Root()->element);
	printf("%d\n",bt.Height(bt.Root()));
	printf("%d\n",bt.Leaf(bt.Root()));
	bt.PreOrder(bt.Root(),cout," ");
	bt=t;
	printf("%d\n",bt.Root()->element);
	printf("%d\n",bt.Height(bt.Root()));
	printf("%d\n",bt.Leaf(bt.Root()));
	bt.PreOrder(bt.Root(),cout," ");
	bt.Swap(bt.Root());
	printf("%d\n",bt.Root()->element);
	printf("%d\n",bt.Height(bt.Root()));
	printf("%d\n",bt.Leaf(bt.Root()));
	bt.PreOrder(bt.Root(),cout," ");
	cout<<endl;
	bt.InOrder(bt.Root(),cout," ");
	cout<<endl;
	bt.PostOrder(bt.Root(),cout," ");
	cout<<endl;
	return 0;
}
