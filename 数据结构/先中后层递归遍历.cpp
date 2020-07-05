/*递归实现先中后序遍历，层次遍历*/
#include<iostream>
using namespace std;
#include<cstdlib>
#define STACK_INIT_SIZE 100 //初始分配 
#define STACKINCREMENT 20 //增量 
//树 链式 
typedef struct BiTNode{
	char data;
	struct BiTNode *lchild;
	struct BiTNode *rchild;
}BiTNode,*BiTree;
//链式队列 
typedef struct QNode{
	BiTree elem;
	struct QNode *next;
}QNode,*QueuePtr;
typedef struct{
	QueuePtr front;
	QueuePtr rear; 
}LinkQueue;
//顺序栈
typedef struct Stack{
	BiTree* top;
	BiTree* base;
	int stacksize; 
}Stack;
/*------------------------------------------------树*/
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
	if(ch=='#') T=NULL; //即相当于左/右子树为空 
	else{
		if(!(T=(BiTNode*)malloc(sizeof(BiTNode)))){
			exit(0);
		}
		T->data=ch;
		CreateBiTree(T->lchild);//创建左子树 
		CreateBiTree(T->rchild);//创建右子树 
	}
}
/*---------------------------------------------队列*/
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
		Q.rear=Q.front;//指向空		
	}
	free(P);	
} 
/*-----------------------------------------*/
void LevelOrderTraverse(BiTree T){
	if(!T)
		exit(0);
	LinkQueue Q;//队列 
	InitQueue(Q);
	EnQueue(Q,T);//插入 
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
		return 0;//退出当前的递归返回上一层而不是整个递归结束 
	cout<<T->data<<" "; //先序遍历则cout在最上层    先根 
	PreOrderTraverse(T->lchild);  //先序遍历左子树 
	PreOrderTraverse(T->rchild);//先序遍历右子树 
} 
int InOrderTraverse(BiTree T){
	if(!T)
		return 0; 
	 InOrderTraverse(T->lchild);
	 cout<<T->data<<" "; //中序遍历则cout在中间 
	 InOrderTraverse(T->rchild);
} 
int PostOrderTraverse(BiTree T){
	if(!T)
		return 0;
	PostOrderTraverse(T->lchild);
	PostOrderTraverse(T->rchild);
	cout<<T->data<<" ";  //后序遍历则cout在最下边 
} 
int main(){
	BiTree T;
	cout<<"创建树(输入#表示NULL):";
	CreateBiTree(T);
	cout<<"先序遍历:";
	PreOrderTraverse(T);
	cout<<endl;
	cout<<"中序遍历:";
	InOrderTraverse(T);
	cout<<endl;
	cout<<"后序遍历:";
	PostOrderTraverse(T);
	cout<<endl;
	cout<<"层次遍历:";
	LevelOrderTraverse(T);
	return 0;
}
/* 测试用例：ABDH##I##E##CF##GJ#K###
先序次遍历:A B D H I E C F G J K
中序次遍历:H D I B E A F C J K G
后序次遍历:H I D E B F K J G C A
层次次遍历:A B C D E F G H I J K */
