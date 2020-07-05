/*���ʵ�֣��жϸ����Ķ������Ƿ�����ȫ�������� 2019/11/17 ������*/
//˼�룺�ò�α������� 
#include<iostream>
using namespace std;
#include<cstdlib>
#define STACK_INIT_SIZE 100 //��ʼ���� 
#define STACKINCREMENT 20
typedef struct BiTNode{
	int data;
	struct BiTNode* lchild;
	struct BiTNode* rchild; 
}BiTNode,*BiTree;
typedef struct Queue{
	BiTree elem;
	struct Queue* next;
}QNode,*QueuePtr;
typedef struct{
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;
/*---------------------------------------------����*/
void InitQueue(LinkQueue &Q){
	Q.front=(QNode*)malloc(sizeof(QNode));
	if(!Q.front)
		exit(0);
	Q.front->next=NULL;
	Q.rear=Q.front;
}
void EnQueue(LinkQueue& Q,BiTree T){
	QueuePtr P;
	P=(QNode*)malloc(sizeof(QNode));
	if(!P){
		exit(0);
	}
	P->elem=T;
	P->next=NULL;
	Q.rear->next=P;
	Q.rear=P;
}
void DeQueue(LinkQueue &Q,BiTree& t){
	if(Q.front==Q.rear)
		exit(0);
	QueuePtr P;
	P=Q.front->next;	
	t=P->elem;
	Q.front->next=P->next;
	if(Q.rear==P){
		Q.rear=Q.front;//ָ���		
	}
	free(P);	
} 
/*--------------------------------------------------*/
void InitBiTree(BiTree &T){
	T=(BiTNode*)malloc(sizeof(BiTNode));
	if(!T){
		cout<<"fail";
		exit(0);
	}
	T->lchild=NULL;
	T->rchild=NULL;
} 
void CreateBiTree(BiTree& T ){
	int n;
	cin>>n;
	if(n==0) T=NULL; //���൱����/������Ϊ�� 
	else{
		if(!(T=(BiTNode*)malloc(sizeof(BiTNode)))){
			exit(0);
		}
		T->data=n;
		CreateBiTree(T->lchild);//���������� 
		CreateBiTree(T->rchild);//���������� 
	}
}
void LevelOrderTraverse_Judeg(BiTree T){
	if(!T)
		exit(0);
	LinkQueue Q;
	InitQueue(Q);
	EnQueue(Q,T);
	BiTree t;
	bool flag=true;
	while(Q.front!=Q.rear&&flag){
		DeQueue(Q,t);
		if(t->lchild){
			if(t->lchild->data==2*(t->data)){
				EnQueue(Q,t->lchild);
			}
			else
				flag=false;
		}
		if(t->rchild){
			if(t->rchild->data==2*(t->data)+1){
				EnQueue(Q,t->rchild);
			}
			else
				flag=false;
		}
	}
	if(!flag)
		cout<<"��������ȫ������"<<endl;
	else
		cout<<"����Ϊ��ȫ������"<<endl; 
}
int main()
{
	BiTree T;
	cout<<"������(����0��ʾNULL)):";
	CreateBiTree(T);
	LevelOrderTraverse_Judeg(T);
	return 0;
}

//����������1 2 4 0 0 5 6 0 0 7 0 0 3 0 0(��)  1 2 4 8 0 0 9 0 0 5 10 0 0 11 0 0 3 6 12 0 0 0 7 0 0(��) 


