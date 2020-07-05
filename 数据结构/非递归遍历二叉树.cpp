/*实现二叉树的先序、中序、后序遍历，用非递归方法；实现层次遍历。 层次遍历只有非递归方法。 2019/11/16 马丽钧 */
//层次用队列  先中后序都用栈实现，且方法有关联 
#include<iostream>
using namespace std;
#include<cstdlib>
#include<string.h>
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
	BiTree* top;  //这里就是二重指针 
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
/*---------------------------------------------栈*/
void InitStack(Stack& S){
	S.base=(BiTree*)malloc(STACK_INIT_SIZE*sizeof(BiTree)); 
	if(!S.base)
		exit(0);
	S.top=S.base;
	S.stacksize=STACK_INIT_SIZE;
} 
//插入t为栈顶元素
void Push(Stack& S,BiTree t){
	if(S.top-S.base>S.stacksize){
		int length=STACK_INIT_SIZE+STACKINCREMENT;
		S.base=(BiTree *)realloc(S.base,length*sizeof(BiTree));
		if(!S.base)
			exit(0);
		S.top=S.base+S.stacksize;//设置栈顶 
		S.stacksize+=STACKINCREMENT;
	}
	*S.top++=t;
}
//栈顶元素出栈，并用t返回 
void Pop(Stack& S,BiTree &t){
	if(S.top==S.base)
		exit(0);
	t=*--S.top;//因为top总指向当前栈顶元素的下一位置 
}
//返回栈顶元素 
int GetTop(Stack S,BiTree& t){
	if(S.top==S.base){
		cout<<"****";
		exit(0);
	}
	else
		t=*(S.top-1);
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
//先序排列——根据先序遍历的思想用栈的方式完成 
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
//中序排列——从根开始先遍历完左子树，然后退栈，看退栈元素有没有右子树，若有；在重复先前操作 
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
			Push(S,t->lchild);//走完左子树，最后进入栈的是空指针 
			// else break;   下面近右孩子也是这样  这样就不用退空指针了     2020/1/6 
		Pop(S,t);//空指针出栈
		if(S.top!=S.base){
			Pop(S,t); //栈顶元素退栈并输出 
			cout<<t->data<<" "; 
			Push(S,t->rchild);//如果是空，则下一个循环就不用再走左子树，而是继续退栈(自己写的时候就是这一步退栈不知道如何写) ,退出的是空指针 
		}
	} 
}
//后续排列——后续排列与先序排列的算法相似，只是进栈的子顺序相反，同时建立两个栈，
//第二个栈用以存放出栈的第一个栈出栈的数，在将第二个栈逐个输出，即为后序排列 
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
//层次排列 
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

void InsertChild(BiTree &T,char name){
	cout<<T->data<<endl;
	if(T->data==name){
		BiTree p;
		cout<<"输入孩子名字:";
		CreateBiTree(p);
		//找插入点 
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
	cout<<"输入要插入孩子的父亲";
	char name;
	cin>>name;
	InsertChild(T,name);
	cout<<"先序遍历:";
	PreOrderTraverse(T);
	return 0;
}
/* 测试用例：ABDH##I##E##CF##GJ#K###
先序次遍历:A B D H I E C F G J K
中序次遍历:H D I B E A F C J K G
后序次遍历:H I D E B F K J G C A
层次次遍历:A B C D E F G H I J K */
