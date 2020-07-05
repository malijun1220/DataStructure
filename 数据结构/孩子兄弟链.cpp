/* 编程实现，对一棵以孩子-兄弟链表表示的树，输出第i层的所有元素。  2019/11/30 马丽钧 */

//第i层是指所有兄弟，重点在找到第i层,这也是和真的二叉树却别的地方-----------栈实现

//**********通过孩子兄弟表示法，所有普通的树(有n多孩子),都可以变成一棵二叉树*********

// 结构：-------孩子指针域---数据域---兄弟指针域------

//向左指为下一层---------向右指向的都是同一层

#include<iostream>
using namespace std;
#include<cstdlib>
#define STACK_INIT_SIZE 100 //初始分配 
#define STACKINCREMENT 20 //增量 
typedef char ElemType;
typedef struct CSNode {
	ElemType data;
	struct CSNode *firstchild,*nextsibling 	;
}CSNode,*CSTree;
typedef struct QNode{
	CSTree elem;
	struct QNode *next;
}QNode,*QueuePtr;
typedef struct{
	QueuePtr front;
	QueuePtr rear; 
}LinkQueue;
void InitQueue(LinkQueue &Q){
	Q.front=(QNode*)malloc(sizeof(QNode));
	if(!Q.front)
		exit(0);
	Q.front->next=NULL;
	Q.rear=Q.front;
}
void EnQueue(LinkQueue& Q,CSTree T){
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
void DeQueue(LinkQueue &Q,CSTree& t){
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
void GetHead(LinkQueue Q,CSTree& t){
	if(Q.front=Q.rear){
		cout<<"空队列";
		exit(0);
	}
	else{
		QueuePtr p=Q.front->next;
		t=p->elem;
	}
}
//创建方法与二叉数建立方法一样；先孩子，后兄弟---------先根创建 ----------递归 
void CreateCSTree(CSTree& T) {
	ElemType ch;
	cin >> ch;
	if (ch == '#') T = NULL;
	else {
		if (!(T = (CSNode*)malloc(sizeof(CSNode)))) {
			exit(0);
		}
		T->data = ch;
		CreateCSTree(T->firstchild);
		CreateCSTree(T->nextsibling);
	}
}
//输出第i层所有兄弟
void Print_Gen_CSTree(CSTree T) {//一代一代的遍历完成 
	if (!T) {
		exit(0);
	} 
	LinkQueue Q;
	InitQueue(Q);
	CSTree p,s,change;
	p=T;
	change=	(CSNode*)malloc(sizeof(CSNode));
	change->data='@';
	EnQueue(Q,p);
	cout<<"按照一代一代方式的层次输出:"<<endl; 
	while(p->nextsibling){     ///////////要先进 
		p=p->nextsibling;
		EnQueue(Q,p);
	}//root有兄弟，则先把root的兄弟进队 
	EnQueue(Q,change); 
	while(Q.front!=Q.rear){
		DeQueue(Q,p);
		if(Q.front==Q.rear)//为了最后队列里面只有 @ 的 情况    否则会出现死循环 
			break;
		if(p->data==change->data){
			EnQueue(Q,change);
			cout<<endl;
			continue;
		}
		cout<<p->data<<" ";
		if(p->firstchild){
			p=p->firstchild;  //先进孩子  然后如果孩子有兄弟  进孩子的所有兄弟  等遇到 @ 说明本代人以及打印完毕  @ 继续进列 表示又一代的标记 
			EnQueue(Q,p);
			while(p->nextsibling){
				p=p->nextsibling;
				EnQueue(Q,p);
			}
		}
	}
}
void PrintCSTree(CSTree T,int i){
	if (!T) {
		exit(0);
	} 
	int count=1;
	LinkQueue Q;
	InitQueue(Q);
	CSTree p,change;
	p=T;
	change=	(CSNode*)malloc(sizeof(CSNode));
	change->data='@';  //隔代标记 
	EnQueue(Q,p); 
	while(p->nextsibling){
		p=p->nextsibling;
		EnQueue(Q,p);
	}//root有兄弟，则先把root的兄弟进队 
	EnQueue(Q,change);  //本代的所有兄弟都进去了  所以输入隔代标记 
	while(Q.front!=Q.rear){
		DeQueue(Q,p);
		if(Q.front==Q.rear)//为了最后队列里面只有 @ 的 情况 
			break;
		if(p->data==change->data){
			EnQueue(Q,change);
			count++;
			continue;
		}
		if(i==count)
			cout<<p->data<<" ";
		if(p->firstchild){
			p=p->firstchild;
			EnQueue(Q,p);
			while(p->nextsibling){
				p=p->nextsibling;
				EnQueue(Q,p);
			}
		}
	}
}
int main()
{
	CSTree T;
	CreateCSTree(T);
	Print_Gen_CSTree(T); 
	int i;
	cout <<endl<< "第几层你想打印(i)";
	cin >> i;
	PrintCSTree(T, i);
	return 0;
}
//  ABC##DE#G##F##H##
//  ABDH##I##EJ###CFK##L##GM###
