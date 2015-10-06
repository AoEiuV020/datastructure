#include <iostream>
template < typename T > class List
{
  private:
	int theSize;
	void init();
	void copy(const List<T>&);
  protected:
	class Node;
	Node *head, *tail;
	bool insert(Node *,Node *);
  public:
	List();
	List(const List<T> &);
	List<T> &operator=(const List<T> &);
	~List();
	int size() const;
	bool empty() const;
	T & front();
	const T & front() const;
	T & back();
	const T & back() const;
	void push_front(const T &);
	void push_back(const T &);
	bool pop_front();
	bool pop_back();
	bool insert(const int&, const T &);
	bool erase(const int&);
	bool erase(const int&,const int&);
	void clear();
	void reverse();
	int remove(const T &);
};

template < typename T > class List <T >::Node
{
	public:
	T data;
	Node *prev;
	Node *next;
};
template < typename T > void List < T >::init()
{
	head = new Node();
	tail = new Node();
	head->prev = nullptr;
	head->next = tail;
	tail->prev = head;
	tail->next = nullptr;
	theSize = 0;
}
template < typename T > void List < T >::copy(const List<T> &list)
{
	Node *node;
	node=list.head->next;
	while(node!=list.tail)
	{
		push_back(node->data);
		node=node->next;
	}
}

template < typename T > List < T >::List()
{
	init();
}
template < typename T > List < T >::List(const List<T> &list)
{
	init();
	copy(list);
}
template < typename T > List<T> & List < T >::operator=(const List &list)
{
	clear();
	copy(list);
}

template < typename T > List < T >::~List()
{
	Node *node;
	node = head;
	while (head->next != tail)
	{
		head = head->next;
		delete node;
	}
	delete head;
	delete tail;
}

template < typename T > int List < T >::size() const
{
	return theSize;
}

template < typename T > bool List < T >::empty() const
{
	return theSize == 0;
}

template < typename T > T & List < T >::front()
{
	return head->next->data;
}

template < typename T > const T & List < T >::front() const
{
	return head->next->data;
}

template < typename T > T & List < T >::back()
{
	return tail->prev->data;
}

template < typename T > const T & List < T >::back() const
{
	return tail->prev->data;
}

template < typename T > void List < T >::push_front(const T & obj)
{
	Node *node;
	node = new Node();
	head->data = obj;
	head->prev = node;
	node->prev = nullptr;
	node->next = head;
	head = node;
	++theSize;
}

template < typename T > void List < T >::push_back(const T & obj)
{
	Node *node;
	node = new Node();
	tail->data = obj;
	tail->next = node;
	node->next = nullptr;
	node->prev = tail;
	tail = node;
	++theSize;
}

template < typename T > bool List < T >::pop_front()
{
	if (head->next == tail)
	{
		return false;
	}
	Node *node;
	node = head;
	head = head->next;
	head->prev = nullptr;
	delete node;
	--theSize;
	return true;
}

template < typename T > bool List < T >::pop_back()
{
	if (head->next == tail)
	{
		return false;
	}
	Node *node;
	node = tail;
	tail = tail->prev;
	tail->next = nullptr;
	delete node;
	--theSize;
	return true;
}

template < typename T > bool List < T >::insert(Node * node,Node *pos)
{
	node->prev=pos;
	node->next=pos->next;
	pos->next=node;
	node->next->prev=node;
	++theSize;
	return true;
}
template < typename T > bool List < T >::insert(const int &index, const T & obj)
{
	if (index < 0 || index > theSize)
	{
		return false;
	}
	Node *p, *n;				// prev,next,
	p = head;
	n = p->next;
	for (int i = 0; i < index; ++i)
	{
		p = n;
		n = p->next;
	}
	Node *node;
	node = new Node();
	node->data = obj;
	p->next = node;
	node->next = n;
	node->prev = p;
	n->prev = node;
	++theSize;
	return true;
}

template < typename T > bool List < T >::erase(const int &index)
{
	if (index < 0 || index > theSize-1)
	{
		return false;
	}
	Node *node;
	node=head->next;
	for (int i = 0; i < index; ++i)
	{
		node=node->next;
	}
	node->prev->next=node->next;
	node->next->prev=node->prev;
	delete node;
	--theSize;
	return true;
}

template < typename T > bool List < T >::erase(const int &index,const int &num)
{
	if (index < 0 || index > theSize-1)
	{
		return false;
	}
	Node *node;
	node=head->next;
	for (int i = 0; i < index; ++i)
	{
		node=node->next;
	}
	Node *flag;
	flag=node->prev;
	for (int i = 0; i < num; ++i)
	{
		node=node->next;
		delete node->prev;
	}
	flag->next=node;
	node->prev=flag;
	theSize-=num;
	return true;
}
template < typename T > void List < T >::clear()
{
	while(head->next!=tail)
	{
		head->next=head->next->next;
		delete head->next->prev;
	}
	tail->prev=head;
	theSize=0;
}
template < typename T > void List < T >::reverse()
{
	Node *node;
	node=head;
	while(node!=tail)
	{
		node=node->next;
		node->prev->next=node->prev->prev;
		node->prev->prev=node;
	}
	tail->next=tail->prev;
	tail->prev=nullptr;
	tail=head;
	head=node;
}
template < typename T > int List < T >::remove(const T &key)
{
	int count=0;
	Node *node;
	node=head->next;
	while(node!=tail)
	{
		if(key==node->data)
		{
			node->prev->next=node->next;
			node->next->prev->next=node->next;
			node=node->next;
			delete node->prev;
			++count;
		}
		else
		{
			node=node->next;
		}
	}
	return count;
}
template < typename T >
class Polynomial:public List<int>
{
	private:
		class Term;
		Polynomial &operator+=(const Term &);
	public:
		Polynomial();
		Polynomial(const T &,const int&);
		Polynomial &operator+=(const Polynomial &);
		Polynomial operator+(const Polynomial &);
		void output(std::ostream &)const;
		void input(std::istream &);
};
template < typename T >
class Polynomial<T>::Term:public Node
{
	public:
		Term(const Term &);
		Term(const T &,const int &);
		T coef;			//coefficient...
};
template < typename T >
Polynomial<T>::Term::Term(const Term&term)
{
	coef=term.coef;
	data=term.data;
	prev=next=nullptr;
}
template < typename T >
Polynomial<T>::Term::Term(const T &c,const int &d)
{
	coef=c;
	data=d;
}
// */
template < typename T >
Polynomial<T> &Polynomial<T>::operator+=(const Term &term)
{
	Node *node;
	for(node=head->next;(node!=tail)&&(node->data>term.data);node=node->next){/*nothing...*/}
	if((node==tail)||(node->data<term.data))
	{
		insert(static_cast<Node*>(new Term(term)),(node->prev));
	}
	else
	{
		static_cast<Term*>(node)->coef+=term.coef;
	}
	return (*this);
}
template < typename T >
Polynomial<T>::Polynomial()
{

}
template < typename T >
Polynomial<T>::Polynomial(const T &c,const int &d):Polynomial()
{
	operator+=(Term(c,d));
}
template < typename T >
Polynomial<T> &Polynomial<T>::operator+=(const Polynomial &poly)
{
	Node *node;
	for(node=poly.head->next;node!=poly.tail;node=node->next)
	{
		operator+=(*static_cast<Term*>(node));

	}
	return (*this);
}
template < typename T >
Polynomial<T> Polynomial<T>::operator+(const Polynomial &poly)
{
	Polynomial<T> tmp;
	tmp+=(*this);
	tmp+=(poly);
	return tmp;
}
template < typename T >
void Polynomial<T>::input(std::istream &in)
{
	T coef;
	int data;
	in>>coef>>data;
	while(in.good())
	{
		operator+=(Polynomial(coef,data));
		in>>coef>>data;
	}
	in.clear();
}
template < typename T >
void Polynomial<T>::output(std::ostream &out)const
{
	Node *node;
	if(empty())
	{
		out<<0;
		return;
	}
	node=head->next;
	out<<static_cast<Term*>(node)->coef<<"x^"<<node->data;
	for(node=node->next;node!=tail;node=node->next)
	{
		out<<"+"<<static_cast<Term*>(node)->coef<<"x^"<<node->data;
	}
}

template < typename T >
std::istream &operator>>(std::istream &in,Polynomial<T> &poly)
{
	poly.input(in);
	return in;
}
template < typename T >
std::ostream &operator<<(std::ostream &out,const Polynomial<T> &poly)
{
	poly.output(out);
	return out;
}

using namespace std;
int main()
{	
	Polynomial<double> a(1.9,2),b(3.8,6),c,d;
	cin>>c>>d;
	cout<<a<<endl;
	cout<<b<<endl;
	cout<<c<<endl;
	cout<<d<<endl;
	cout<<a+b<<endl;
	cout<<a+b+c<<endl;
	cout<<a+b+c+d<<endl;
	return 0;
}
