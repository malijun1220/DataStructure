/*选择排序法实现线性表的排序问题   链式结构 10/19/2019  马丽钧*/
#include<iostream>
using namespace std;
#include<stdlib.h>
typedef struct LNode
{
	int elem;  //储存空间基址
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
void CreateList(LinkList L) {
	LinkList head, end, p;
	head = L;
	head->next = NULL;
	end = p = head;
	bool flag = true;
	cout << "over when enter 0" << endl;
	while (flag) {
		p = (LNode*)malloc(sizeof(LNode));
		cin >> (p->elem);
		if (p->elem == 0)
		{
			break;
		}
		end->next = p;
		end = p;
	}
	end->next = NULL;
}
void SortList(LinkList &L){
	if(L->next->next==NULL)
		exit(0);//如果只有一个元素，结束 
	LinkList p;//原 
	LinkList m,L1,q,head,L0,h;//h用来开辟空间，储存新元素 
	p=L->next;
	InitList(L1);//开辟空间 
	q=head=L1;
	while(p){
		if(head->next==NULL){
			h = (LNode*)malloc(sizeof(LNode));
			h->elem=p->elem;
			q->next=h;
			q=h;
			q->next=NULL;//q指向第一个元素 
			p=p->next;
			continue;
		}
		//以下q都指向第一个元素 
		if(p->elem>q->elem){
			m=q;
			while(p->elem>q->elem && q->next!=NULL){
				m=q;
				q=q->next;//m指向q的前一个元素 
			}
			h = (LNode*)malloc(sizeof(LNode));
			h->elem=p->elem;
			//新链走到了最后，新元素放在最后 
			if(q->next==NULL&&p->elem>q->elem){
				h->next=q->next;
				q->next=h;
			}
			//新元素插在链表中间 
			else{
				h->next=m->next;
				m->next=h;	
			}
		}
		else{
			h = (LNode*)malloc(sizeof(LNode));
			h->elem=p->elem;//赋值 
			h->next=head->next;
			head->next=h;
		}
		q=head->next;//q再次指向第一位元素 
		p=p->next;
		
	}
	//将原来的L释放 
	LinkList L2=L->next,L3;
	while(L2){
		L3=L2->next;
		free(L2);
		L2=L3;
	}	
	L=L1;
}
int main()
{
	LinkList L,q;
	InitList(L);
	CreateList(L);
	SortList(L);
	int i=0;
	cout<<"排序后输出: "; 
	q=L->next;
	while(q){
		cout<<q->elem<<" ";
		q=q->next;
	}
	return 0;	
}
