/*****************************************************
	^> File Name: graph.cpp
	^> Author: AoEiuV020
	^> Mail: 490674483@qq.com
	^> Created Time: 2015/12/06 - 19:42:00
****************************************************/

//VC6.0下编译

#include<iostream.h>
const int INFTY=2147483640;
enum ResultCode{Underflow,Duplicate,Failure,Success,NotPresent};
template <class T>
class Graph    //抽象类
{
public:
	virtual ResultCode Insert(int u,int v,T&w)=0;
	virtual ResultCode Remove(int u,int v)=0;
	virtual bool Exist(int u,int v)const=0;
protected:
	int n,e;
};
template<class T>         //循环队列类
class SeqQueue
{	
public:
	SeqQueue(int mSize);
	~SeqQueue(){delete []q;}
	bool IsEmpty() const{return front==rear;}
	bool IsFull() const{return (rear+1)%maxSize==front;}
	bool Front(T &x)const;
	bool EnQueue(T x);
	bool DeQueue();
	void Clear(){front=rear=0;}
private:
	int front,rear;
	int maxSize;
	T *q;
};
template<class T>
SeqQueue<T>::SeqQueue(int mSize)   //构造函数
{
	maxSize=mSize;
	q=new T[maxSize];
	front=rear=0;
}
template<class T>
bool SeqQueue<T>::Front(T &x)const    //取队头元素
{
	if(IsEmpty())
	{
		return false;
	}
	x=q[(front+1)%maxSize];
	return true;
}
template<class T>
bool SeqQueue<T>::EnQueue(T x)    //在队尾插入x
{
	if(IsFull())
	{
		cout<<"Full"<<endl;
		return false;
	}
	q[rear=(rear+1)%maxSize]=x;
	return true;
}
template<class T>
bool SeqQueue<T>::DeQueue()   //删除队头元素
{
	if(IsEmpty())
	{
		cout<<"Underflow"<<endl;
		return false;
	}
	front=(front+1)%maxSize;
	return true;
}
template <class T>
class MGraph:public Graph<T>    //邻接矩阵类
{
public:
	MGraph(int mSize,const T& noedg);
	~MGraph();
	ResultCode Insert(int u,int v,T&w);
    ResultCode Remove(int u,int v);
	bool Exist(int u,int v)const;
	void DFS();
	void BFS();
protected:
	T **a;
	T noEdge;
	void DFS(int v,bool *visited);
	void BFS(int v,bool *visited);
};
template <class T>
MGraph<T>::MGraph(int mSize,const T&noedg)  //构造函数
{
	n=mSize;
	e=0;
	noEdge=noedg;
	a=new T*[n];
	for(int i=0;i<n;i++)
	{
		a[i]=new T[n];
		for(int j=0;j<n;j++)
			a[i][j]=noEdge;
		a[i][i]=0;
	}
}
template <class T>
MGraph<T>::~MGraph()   //析构函数
{
	for(int i=0;i<n;i++)
		delete []a[i];
	delete []a;
}
template <class T>
ResultCode MGraph<T>::Insert(int u,int v,T&w)    //插入函数
{
	if(u<0||v<0||u>n-1||v>n-1||u==v)
		return Failure;
	if(a[u][v]!=noEdge)
		return Duplicate;
	a[u][v]=w;
	e++;
	return Success;
}
template <class T>
ResultCode MGraph<T>::Remove(int u,int v)    //删除函数
{
	if(u<0||v<0||u>n-1||v>n-1||u==v)
		return Failure;
	if(a[u][v]==noEdge)
		return NotPresent;
	a[u][v]=noEdge;
	e--;
	return Success;
}
template<class T>
bool MGraph<T>::Exist(int u,int v)const    //判断边是否存在
{
	if(u<0||v<0||u>n-1||v>n-1||u==v||a[u][v]==noEdge)
		return false;
	return true;
}
template <class T>
void MGraph<T>::DFS()   //深度遍历
{
	bool *visited=new bool[n];
	for (int i=0;i<n;i++)
		visited[i]=false;
	for(i=0;i<n;i++)
		if(!visited[i])
			DFS(i,visited);
	delete[]visited;
}
template <class T>
void MGraph<T>::DFS(int v,bool *visited)
{
	visited[v]=true;
	cout<<" "<<v;
	for(int i=0;i<n;i++)
		if(a[v][i]!=noEdge&&a[v][i]!=0&&!visited[i])
			DFS(i,visited);
}
template <class T>
void MGraph<T>::BFS()   //广度遍历
{
	bool *visited=new bool[n];
	for (int i=0;i<n;i++)
		visited[i]=false;
	for(i=0;i<n;i++)
		if(!visited[i])
			BFS(i,visited);
	delete[]visited;
}
template <class T>
void MGraph<T>::BFS(int v,bool *visited)
{
	SeqQueue<int> q(n);
	visited[v]=true;
	cout<<" "<<v;
	q.EnQueue(v);
	while(!q.IsEmpty())
	{
		q.Front(v);
		q.DeQueue();
	    for(int i=0;i<n;i++)
		    if(a[v][i]!=noEdge&&a[v][i]!=0&&!visited[i])
			{
			    visited[i]=true;
			    cout<<" "<<i;
			   q.EnQueue(i);
			}
	}
}
template<class T>   //结点类
class ENode
{
public:
	ENode() {nextArc=NULL;}
	ENode(int vertex,T weight,ENode *next)
	{
		adjVex=vertex;
		w=weight;
		nextArc=next;
	}
	int adjVex;
	T w;
	ENode * nextArc;
};
template <class T>
class LGraph:public Graph<T>   //邻接表类
{
public:
	LGraph(int mSize);
	~LGraph();
	ResultCode Insert(int u,int v,T&w);
    ResultCode Remove(int u,int v);
	bool Exist(int u,int v)const;
protected:
	ENode<T> **a;
};
template <class T>
LGraph<T>::LGraph(int mSize)   //构造函数
{
	n=mSize;
	e=0;
	a=new ENode<T> *[n];
	for(int i=0;i<n;i++)
		a[i]=NULL;
}
template <class T>
LGraph<T>::~LGraph()   //析构
{
	ENode<T> *p,*q;
	for(int i=0;i<n;i++)
	{
		p=a[i];
		q=p;
		while(p)
		{
			p=p->nextArc;
			delete q;
			q=p;
		}
	}
	delete []a;
}
template <class T>
bool LGraph<T>::Exist(int u,int v)const   //判断边是否存在
{
	if(u<0||v<0||u>n-1||v>n-1||u==v)
		return false;
    ENode<T>*p=a[u];
	while(p&&p->adjVex!=v)
		p=p->nextArc;
	if(!p)
		return false;
	else return true;
}
template <class T>
ResultCode LGraph<T>::Insert(int u,int v,T&w)   //插入
{
	if(u<0||v<0||u>n-1||v>n-1||u==v)
		return Failure;
	if(Exist(u,v))
		return Duplicate;
	ENode<T>*p=new ENode<T>(v,w,a[u]);
	a[u]=p;
	e++;
	return Success;
}
template <class T>
ResultCode LGraph<T>::Remove(int u,int v)   //删除
{
	if(u<0||v<0||u>n-1||v>n-1||u==v)
		return Failure;
	ENode<T> *p=a[u],*q;
	q=NULL;
	while(p&&p->adjVex!=v)
	{
		q=p;
		p=p->nextArc;
	}
	if(!p)
		return NotPresent;
	if(q)
		q->nextArc=p->nextArc;
	else
		a[u]=p->nextArc;
	delete p;
	e--;
	return Success;
}
int main()      //主函数
{
	int n,g;
	cout<<"请输入元素的个数: ";
	cin>>n;
	MGraph<int>A(n,INFTY);
	LGraph<int>B(n);
	cout<<"请输入边的条数: ";
	cin>>g;
	int *a=new int[g];
	int *b=new int[g];
	int *w=new int[g];
	for(int i=0;i<g;i++)
	{
		cout<<"请输入边及权值: ";
		cin>>a[i]>>b[i]>>w[i];
		A.Insert(a[i],b[i],w[i]);
		B.Insert(a[i],b[i],w[i]);
	}
	cout<<"该图的深度优先遍历为:"<<endl;
	A.DFS();
	cout<<endl;
	cout<<"该图的广度优先遍历为:"<<endl;
	A.BFS();
	cout<<endl;
	cout<<"请输入要搜索的边: ";
	int c,d;
	cin>>c>>d;
	if(A.Exist(c,d))
		cout<<"邻接矩阵中该边存在!"<<endl;
	else 
		cout<<"邻接矩阵中该边不存在!"<<endl;
	if(B.Exist(c,d))
		cout<<"邻接表中该边存在!"<<endl;
	else 
		cout<<"邻接表中该边不存在!"<<endl;
	cout<<"请输入要删除的边: ";
	int e,f;
	cin>>e>>f;
	if(A.Remove(e,f)==Success)
		cout<<"邻接矩阵中删除该边成功!"<<endl;
	else if(A.Remove(e,f)==NotPresent)
		cout<<"邻接矩阵中该边不存在!"<<endl;
	else
		cout<<"输入错误!"<<endl;
	if(B.Remove(e,f)==Success)
		cout<<"邻接表中删除该边成功!"<<endl;
	else if(B.Remove(e,f)==NotPresent)
		cout<<"邻接表中该边不存在!"<<endl;
	else
		cout<<"邻接表中输入错误!"<<endl;
	cout<<"删除该边后该图的深度优先遍历为:"<<endl;
	A.DFS();
	cout<<endl;
	cout<<"删除该边后该图的广度优先遍历为:"<<endl;
	A.BFS();
	cout<<endl;
	return 0;
}



