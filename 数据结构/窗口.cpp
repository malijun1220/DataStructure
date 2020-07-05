/*窗口点击抽象题   连式结构 马丽钧  10/26/2019*/
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
	int number;//记录图层编号 
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
	head->next=NULL; //要有 
	int i=0;
	cout<<"      x1 "<<"y1 "<<"x2 "<<"y2 "<<endl;
	while (i++<n) {
		cout<<"第"<<i<<"层:";//第 1 层也就是最底层在链表的最后一位，最顶层在链表第一位 
		p = (LNodeN*)malloc(sizeof(LNodeN));
		cin>>p->leftx>>p->lefty>>p->rightx>>p->righty;
		p->number=i;//层数编号 
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
		cout<<"第"<<i<<"次点:";
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
	int M,N;//N为窗口层数，M为鼠标点击次数 
	cout<<"窗口数N:";
	cin>>N;
	cout<<"鼠标点击次数M:";
	cin>>M;
	cout<<"现在输入窗口坐标(左下:(x1,y1),右上:(x2,y2)):"<<endl;
	CreateList_N(Nq,N); 
	cout<<"现在输入鼠标点击区域(x,y):"<<endl;
	CreateList_M(Mq,M);
	cout<<"结果:"<<endl;
	Windows(Nq,Mq);
}
