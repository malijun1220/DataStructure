/*ʵ�ֶ��������������򡢺���������÷ǵݹ鷽����ʵ�ֲ�α����� ��α���ֻ�зǵݹ鷽���� 2019/11/16 ������ */
//����ö���  ���к�����ջʵ�֣��ҷ����й��� 
#include<iostream>
using namespace std;
#include<cstdlib>
#include<string.h>
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
	BiTree* top;  //������Ƕ���ָ�� 
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
/*---------------------------------------------ջ*/
void InitStack(Stack& S){
	S.base=(BiTree*)malloc(STACK_INIT_SIZE*sizeof(BiTree)); 
	if(!S.base)
		exit(0);
	S.top=S.base;
	S.stacksize=STACK_INIT_SIZE;
} 
//����tΪջ��Ԫ��
void Push(Stack& S,BiTree t){
	if(S.top-S.base>S.stacksize){
		int length=STACK_INIT_SIZE+STACKINCREMENT;
		S.base=(BiTree *)realloc(S.base,length*sizeof(BiTree));
		if(!S.base)
			exit(0);
		S.top=S.base+S.stacksize;//����ջ�� 
		S.stacksize+=STACKINCREMENT;
	}
	*S.top++=t;
}
//ջ��Ԫ�س�ջ������t���� 
void Pop(Stack& S,BiTree &t){
	if(S.top==S.base)
		exit(0);
	t=*--S.top;//��Ϊtop��ָ��ǰջ��Ԫ�ص���һλ�� 
}
//����ջ��Ԫ�� 
int GetTop(Stack S,BiTree& t){
	if(S.top==S.base){
		cout<<"****";
		exit(0);
	}
	else
		t=*(S.top-1);
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
//�������С����������������˼����ջ�ķ�ʽ��� 
void PreOrderTraverse(BiTree T){
	if(!T)
		exit(0);
	Stack S;
	InitStack(S);
	BiTree t;
	Push(S,T);
	while(S.top!=S.base){
		Pop(S,t);
		cout<<t->data<<" "; 
		if(t->rchild)
			Push(S,t->rchild);
		if(t->lchild)
			Push(S,t->lchild);
	} 
} 
//�������С����Ӹ���ʼ�ȱ�������������Ȼ����ջ������ջԪ����û�������������У����ظ���ǰ���� 
int InOrderTraverse(BiTree T){	
	if(!T)
		exit(0);
	Stack S;
	InitStack(S);
	BiTree t;
	Push(S,T);
	while(S.top!=S.base){
		while(GetTop(S,t)&&t)
			//if(t->lchild) 
			Push(S,t->lchild);//������������������ջ���ǿ�ָ�� 
			// else break;   ������Һ���Ҳ������  �����Ͳ����˿�ָ����     2020/1/6 
		Pop(S,t);//��ָ���ջ
		if(S.top!=S.base){
			Pop(S,t); //ջ��Ԫ����ջ����� 
			cout<<t->data<<" "; 
			Push(S,t->rchild);//����ǿգ�����һ��ѭ���Ͳ������������������Ǽ�����ջ(�Լ�д��ʱ�������һ����ջ��֪�����д) ,�˳����ǿ�ָ�� 
		}
	} 
}
//�������С��������������������е��㷨���ƣ�ֻ�ǽ�ջ����˳���෴��ͬʱ��������ջ��
//�ڶ���ջ���Դ�ų�ջ�ĵ�һ��ջ��ջ�������ڽ��ڶ���ջ����������Ϊ�������� 
void PostOrderTraverse(BiTree T){
	if(!T)
		exit(0);
	Stack S,S1;
	InitStack(S);
	InitStack(S1);
	BiTree t;
	Push(S,T);
	while(S.top!=S.base){
		Pop(S,t);
		Push(S1,t);
		if(t->lchild)
			Push(S,t->lchild);
		if(t->rchild)
			Push(S,t->rchild);
	} 
	while(S1.base!=S1.top){
		Pop(S1,t);
		cout<<t->data<<" ";	
	} 
}
//������� 
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

void InsertChild(BiTree &T,char name){
	cout<<T->data<<endl;
	if(T->data==name){
		BiTree p;
		cout<<"���뺢������:";
		CreateBiTree(p);
		//�Ҳ���� 
		if(T->lchild){
			Stack S;
			InitStack(S);
			BiTree t;
			Push(S,T->lchild);
			while(S.top!=S.base){
				Pop(S,t);
				if(t->rchild)
					Push(S,t->rchild);
				else
					break;
			} 
			t->rchild=p;
		}
		else
			T->lchild=p;
		return ;
		
	} 
	else{
		if(T->lchild)
			InsertChild(T->lchild,name);
		if(T->rchild)
			InsertChild(T->rchild,name);
	}
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
	cout<<"����Ҫ���뺢�ӵĸ���";
	char name;
	cin>>name;
	InsertChild(T,name);
	cout<<"�������:";
	PreOrderTraverse(T);
	return 0;
}
/* ����������ABDH##I##E##CF##GJ#K###
����α���:A B D H I E C F G J K
����α���:H D I B E A F C J K G
����α���:H I D E B F K J G C A
��δα���:A B C D E F G H I J K */
