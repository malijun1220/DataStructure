/*队列的抽象链表  10/23/2019 马丽钧*/
#include<iostream>
using namespace std;
#include<cstdlib>
typedef struct QNode{
	int elem;
	struct QNode *next;
}QNode,*QueuePtr;
typedef struct{
	QueuePtr front;//队头指针 
	QueuePtr rear;//队尾指针 
}LinkQueue;
void InitQueue(LinkQueue& Q){
	Q.front=Q.rear=(QNode*)malloc(sizeof(QNode)); //这里不要写成LinkQueue; 
	if(!Q.front){
		cout<<"fail";
		exit(0);
	}
	Q.front->next=NULL;
	Q.rear->next=NULL;
} 
void DestoryQueue(LinkQueue& Q){
	while(Q.front){
		Q.rear=Q.front->next;
		free(Q.front);
		Q.front=Q.rear;
	} 
}
//清空 
void ClearEmpty(LinkQueue Q){
	Q.front=Q.rear; 
}
//探空 
bool QueueEmpty(LinkQueue Q){
	if(Q.front==Q.rear)
		return false;
	else
		return true;	
} 
//返回链表长度 
int QueueLength(LinkQueue Q){
	QueuePtr L;
	L=Q.front->next;
	int i=0;
	while(L!=Q.rear){
		i++;
		L=L->next;
	}
	return i;
}
//返回队头元素 
void GetHead(LinkQueue Q,int &e){
	if(Q.front=Q.rear){
		cout<<"空队列";
		exit(0);
	}
	else{
		QueuePtr p=Q.front->next;
		e=p->elem;
	}
}
//插入元素e作为Q队尾元素 
void EnQueue(LinkQueue& Q,int e){
	QueuePtr p;
	p=(QNode*)malloc(sizeof(QNode));
	if(!p){
		cout<<"fail";
		exit(0); 
	}
	p->elem=e;
	p->next=NULL;
	Q.rear->next=p;
	Q.rear=p;
}
//删除Q的队头元素, 并free 
void DeQueue(LinkQueue& Q,int &e){
	if(Q.front==Q.rear){
		cout<<"空队列";
		exit(0); 
	}
	QueuePtr p=Q.front->next;
	e=p->elem;
	Q.front->next=p->next;
	if(Q.rear==p)
		Q.rear=Q.front;  //空队列 
	free(p);	
}
//用来打印输出也可以 
void QueueTraverse(LinkQueue Q){
	QueuePtr p;
	p=Q.front->next;
	while(p!=Q.rear){
		cout<<p->elem<<" ";
		p=p->next;
	} 
}
int main(){
	LinkQueue Q;
	return 0;
}


