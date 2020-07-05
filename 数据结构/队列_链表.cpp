/*���еĳ�������  10/23/2019 ������*/
#include<iostream>
using namespace std;
#include<cstdlib>
typedef struct QNode{
	int elem;
	struct QNode *next;
}QNode,*QueuePtr;
typedef struct{
	QueuePtr front;//��ͷָ�� 
	QueuePtr rear;//��βָ�� 
}LinkQueue;
void InitQueue(LinkQueue& Q){
	Q.front=Q.rear=(QNode*)malloc(sizeof(QNode)); //���ﲻҪд��LinkQueue; 
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
//��� 
void ClearEmpty(LinkQueue Q){
	Q.front=Q.rear; 
}
//̽�� 
bool QueueEmpty(LinkQueue Q){
	if(Q.front==Q.rear)
		return false;
	else
		return true;	
} 
//���������� 
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
//���ض�ͷԪ�� 
void GetHead(LinkQueue Q,int &e){
	if(Q.front=Q.rear){
		cout<<"�ն���";
		exit(0);
	}
	else{
		QueuePtr p=Q.front->next;
		e=p->elem;
	}
}
//����Ԫ��e��ΪQ��βԪ�� 
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
//ɾ��Q�Ķ�ͷԪ��, ��free 
void DeQueue(LinkQueue& Q,int &e){
	if(Q.front==Q.rear){
		cout<<"�ն���";
		exit(0); 
	}
	QueuePtr p=Q.front->next;
	e=p->elem;
	Q.front->next=p->next;
	if(Q.rear==p)
		Q.rear=Q.front;  //�ն��� 
	free(p);	
}
//������ӡ���Ҳ���� 
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


