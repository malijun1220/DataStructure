/*�ݹ�ʵ�����к����������α���*/
#include<iostream>
using namespace std;
#include<cstdlib>
#define STACK_INIT_SIZE 100 //��ʼ���� 
#define STACKINCREMENT 20 //���� 
//�� ��ʽ 
typedef struct BiTNode{
	char data;
	struct BiTNode *lchild;
	struct BiTNode *rchild;
}BiTNode,*BiTree;
//��ʽ���� 
typedef struct QNode{
	BiTree elem;
	struct QNode *next;
}QNode,*QueuePtr;
typedef struct{
	QueuePtr front;
	QueuePtr rear; 
}LinkQueue;
//˳��ջ
typedef struct Stack{
	BiTree* top;
	BiTree* base;
	int stacksize; 
}Stack;
/*------------------------------------------------��*/
void InitBiTree(BiTree &T){
	T=(BiTNode*)malloc(sizeof(BiTNode));
	if(!T){
		cout<<"fail";
		exit(0);
	}
	T->data=' ';
	T->lchild=NULL;
	T->rchild=NULL;
} 
void CreateBiTree(BiTree& T ){
	char ch;
	cin>>ch;
	if(ch=='#') T=NULL; //���൱����/������Ϊ�� 
	else{
		if(!(T=(BiTNode*)malloc(sizeof(BiTNode)))){
			exit(0);
		}
		T->data=ch;
		CreateBiTree(T->lchild);//���������� 
		CreateBiTree(T->rchild);//���������� 
	}
}
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
/*-----------------------------------------*/
void LevelOrderTraverse(BiTree T){
	if(!T)
		exit(0);
	LinkQueue Q;//���� 
	InitQueue(Q);
	EnQueue(Q,T);//���� 
	BiTree t;
	while(Q.front!=Q.rear){
		DeQueue(Q,t);
		cout<<t->data<<" ";
		if(t->lchild)
			EnQueue(Q,t->lchild);
		if(t->rchild)
			EnQueue(Q,t->rchild);
	}
}
int PreOrderTraverse(BiTree T){
	if(!T)
		return 0;//�˳���ǰ�ĵݹ鷵����һ������������ݹ���� 
	cout<<T->data<<" "; //���������cout�����ϲ�    �ȸ� 
	PreOrderTraverse(T->lchild);  //������������� 
	PreOrderTraverse(T->rchild);//������������� 
} 
int InOrderTraverse(BiTree T){
	if(!T)
		return 0; 
	 InOrderTraverse(T->lchild);
	 cout<<T->data<<" "; //���������cout���м� 
	 InOrderTraverse(T->rchild);
} 
int PostOrderTraverse(BiTree T){
	if(!T)
		return 0;
	PostOrderTraverse(T->lchild);
	PostOrderTraverse(T->rchild);
	cout<<T->data<<" ";  //���������cout�����±� 
} 
int main(){
	BiTree T;
	cout<<"������(����#��ʾNULL):";
	CreateBiTree(T);
	cout<<"�������:";
	PreOrderTraverse(T);
	cout<<endl;
	cout<<"�������:";
	InOrderTraverse(T);
	cout<<endl;
	cout<<"�������:";
	PostOrderTraverse(T);
	cout<<endl;
	cout<<"��α���:";
	LevelOrderTraverse(T);
	return 0;
}
/* ����������ABDH##I##E##CF##GJ#K###
����α���:A B D H I E C F G J K
����α���:H D I B E A F C J K G
����α���:H I D E B F K J G C A
��δα���:A B C D E F G H I J K */
