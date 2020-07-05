/*���ڵ��������   ��ʽ�ṹ ������  10/26/2019*/
#include<iostream>
using namespace std;
#include<cstdlib>
typedef struct LNode_M
{
	int x;
	int y;  
	struct LNode_M* next;
}LNodeM, *LinkListM;	
typedef struct LNode_N
{
	int leftx;
	int lefty;
	int rightx;
	int righty; 
	int number;//��¼ͼ���� 
	struct LNode_N* next;
}LNodeN, *LinkListN;
void InitList_N(LinkListN& Nq) {
	Nq = (LNodeN*)malloc(sizeof(LNodeN));
	if (!Nq) {
		cout << "fail";
		exit(0);
	}
	Nq->next = NULL;
}
void InitList_M(LinkListM& Mq) {
	Mq = (LNodeM*)malloc(sizeof(LNodeM));
	if (!Mq) {
		cout << "fail";
		exit(0);
	}
	Mq->next = NULL;
}
void CreateList_N(LinkListN &Nq,int n) {
	LinkListN head, end, p;
	head = Nq;
	head->next=NULL; //Ҫ�� 
	int i=0;
	cout<<"      x1 "<<"y1 "<<"x2 "<<"y2 "<<endl;
	while (i++<n) {
		cout<<"��"<<i<<"��:";//�� 1 ��Ҳ������ײ�����������һλ������������һλ 
		p = (LNodeN*)malloc(sizeof(LNodeN));
		cin>>p->leftx>>p->lefty>>p->rightx>>p->righty;
		p->number=i;//������� 
		p->next=head->next;
		head->next=p;
	}
}
void CreateList_M(LinkListM & Mq,int n) {
	LinkListM head, end, p;
	head = Mq;
	end = head;
	int i=0;
	cout<<"        x "<<"y "<<endl;
	while (i++<n) {
		cout<<"��"<<i<<"�ε�:";
		p = (LNodeM*)malloc(sizeof(LNodeM));
		cin>> p->x>>p->y;
		end->next = p;
		end = p;
	}
	end->next=NULL;
}
void Windows(LinkListN &Nq,LinkListM &Mq){
	LinkListN nq=Nq->next,np;
	LinkListM mq=Mq->next;
	bool flag=false;
	while(mq){
		while(nq)
		{
			if(mq->x >= nq->leftx && mq->y >= nq->lefty && mq->x <= nq->rightx && mq->y <= nq->righty){
				flag=true;
				break;
			}
			np=nq;
			nq=nq->next;
		}
	
		if(flag){
			cout<<nq->number<<endl;
			if(Nq->next->number!=nq->number){
				np->next=nq->next;
				nq->next=Nq->next;
				Nq->next=nq;
			}
			
		}
		else if(!flag){
			cout<<"IGNORED"<<endl;
		}
		flag=false;
		mq=mq->next;
	} 
}
int main()
{
	LinkListM Mq;
	LinkListN Nq;
	int M,N;//NΪ���ڲ�����MΪ��������� 
	cout<<"������N:";
	cin>>N;
	cout<<"���������M:";
	cin>>M;
	cout<<"�������봰������(����:(x1,y1),����:(x2,y2)):"<<endl;
	CreateList_N(Nq,N); 
	cout<<"�����������������(x,y):"<<endl;
	CreateList_M(Mq,M);
	cout<<"���:"<<endl;
	Windows(Nq,Mq);
}
