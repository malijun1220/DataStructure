/* ���ʵ�֣���һ���Ժ���-�ֵ������ʾ�����������i�������Ԫ�ء�  2019/11/30 ������ */

//��i����ָ�����ֵܣ��ص����ҵ���i��,��Ҳ�Ǻ���Ķ�����ȴ��ĵط�-----------ջʵ��

//**********ͨ�������ֵܱ�ʾ����������ͨ����(��n�ຢ��),�����Ա��һ�ö�����*********

// �ṹ��-------����ָ����---������---�ֵ�ָ����------

//����ָΪ��һ��---------����ָ��Ķ���ͬһ��

#include<iostream>
using namespace std;
#include<cstdlib>
#define STACK_INIT_SIZE 100 //��ʼ���� 
#define STACKINCREMENT 20 //���� 
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
		Q.rear=Q.front;//ָ���		
	}
	free(P);	
} 
void GetHead(LinkQueue Q,CSTree& t){
	if(Q.front=Q.rear){
		cout<<"�ն���";
		exit(0);
	}
	else{
		QueuePtr p=Q.front->next;
		t=p->elem;
	}
}
//�����������������������һ�����Ⱥ��ӣ����ֵ�---------�ȸ����� ----------�ݹ� 
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
//�����i�������ֵ�
void Print_Gen_CSTree(CSTree T) {//һ��һ���ı������ 
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
	cout<<"����һ��һ����ʽ�Ĳ�����:"<<endl; 
	while(p->nextsibling){     ///////////Ҫ�Ƚ� 
		p=p->nextsibling;
		EnQueue(Q,p);
	}//root���ֵܣ����Ȱ�root���ֵܽ��� 
	EnQueue(Q,change); 
	while(Q.front!=Q.rear){
		DeQueue(Q,p);
		if(Q.front==Q.rear)//Ϊ������������ֻ�� @ �� ���    ����������ѭ�� 
			break;
		if(p->data==change->data){
			EnQueue(Q,change);
			cout<<endl;
			continue;
		}
		cout<<p->data<<" ";
		if(p->firstchild){
			p=p->firstchild;  //�Ƚ�����  Ȼ������������ֵ�  �����ӵ������ֵ�  ������ @ ˵���������Լ���ӡ���  @ �������� ��ʾ��һ���ı�� 
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
	change->data='@';  //������� 
	EnQueue(Q,p); 
	while(p->nextsibling){
		p=p->nextsibling;
		EnQueue(Q,p);
	}//root���ֵܣ����Ȱ�root���ֵܽ��� 
	EnQueue(Q,change);  //�����������ֵܶ���ȥ��  �������������� 
	while(Q.front!=Q.rear){
		DeQueue(Q,p);
		if(Q.front==Q.rear)//Ϊ������������ֻ�� @ �� ��� 
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
	cout <<endl<< "�ڼ��������ӡ(i)";
	cin >> i;
	PrintCSTree(T, i);
	return 0;
}
//  ABC##DE#G##F##H##
//  ABDH##I##EJ###CFK##L##GM###
