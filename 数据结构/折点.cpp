/*题目：问题描述：先输入一个十进制整数n，再输入n个正整数，求它们相邻数之差可知是否为上升或下降，
由上升转下降或由下降转上升为折点，求折点数。问题分析：如果一个点的值比左右两个都大或都小，则为折点。*/
/*10/20/2019 马丽钧 */
#include<iostream>
using namespace std; 
#include<cstdlib>
typedef struct LNode
{
	int elem;  
	struct LNode* next;
}LNode, *LinkList;	
void InitList(LinkList& L) {
	L = (LNode*)malloc(sizeof(LNode));
	if (!L) {
		cout << "fail";
		exit(0);
	}
	L->next = NULL;
}
void CreateList(LinkList &L,int n) {
	LinkList head, end, p;
	head = L;
	end = p = head;
	head->next = NULL;
	bool flag = true;
	int i=0;
	while (flag) {
		p = (LNode*)malloc(sizeof(LNode));
		cin >> (p->elem);
		end->next = p;
		end = p;
		if (n==++i){
			break;
		}
	}
	end->next = NULL;
}
void PointList(LinkList &L,int &n){
	LinkList r,m,l;
	r=L->next;
	m=r->next;
	l=m->next;
	if(l==NULL){
		n=0;
		exit(0); 
	}
	while(l){
		if((r->elem< m->elem&&m->elem > l->elem)||(r->elem > m->elem&&m->elem < l->elem)){
			n++;
		}
		r=m;
		m=l;
		l=l->next;	
	}	 
}
int main()
{
	LinkList L;
	int n;
	InitList(L);
	cout<<"你想输入几个数据:";
	cin>>n;
	cout<<"开始输入:";
	CreateList(L,n);
	int total=0;
	PointList(L,total);
	cout<<"总折点数:"<<total;
	return 0; 
}
