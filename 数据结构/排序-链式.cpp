/*ѡ������ʵ�����Ա����������   ��ʽ�ṹ 10/19/2019  ������*/
#include<iostream>
using namespace std;
#include<stdlib.h>
typedef struct LNode
{
	int elem;  //����ռ��ַ
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
		exit(0);//���ֻ��һ��Ԫ�أ����� 
	LinkList p;//ԭ 
	LinkList m,L1,q,head,L0,h;//h�������ٿռ䣬������Ԫ�� 
	p=L->next;
	InitList(L1);//���ٿռ� 
	q=head=L1;
	while(p){
		if(head->next==NULL){
			h = (LNode*)malloc(sizeof(LNode));
			h->elem=p->elem;
			q->next=h;
			q=h;
			q->next=NULL;//qָ���һ��Ԫ�� 
			p=p->next;
			continue;
		}
		//����q��ָ���һ��Ԫ�� 
		if(p->elem>q->elem){
			m=q;
			while(p->elem>q->elem && q->next!=NULL){
				m=q;
				q=q->next;//mָ��q��ǰһ��Ԫ�� 
			}
			h = (LNode*)malloc(sizeof(LNode));
			h->elem=p->elem;
			//�����ߵ��������Ԫ�ط������ 
			if(q->next==NULL&&p->elem>q->elem){
				h->next=q->next;
				q->next=h;
			}
			//��Ԫ�ز��������м� 
			else{
				h->next=m->next;
				m->next=h;	
			}
		}
		else{
			h = (LNode*)malloc(sizeof(LNode));
			h->elem=p->elem;//��ֵ 
			h->next=head->next;
			head->next=h;
		}
		q=head->next;//q�ٴ�ָ���һλԪ�� 
		p=p->next;
		
	}
	//��ԭ����L�ͷ� 
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
	cout<<"��������: "; 
	q=L->next;
	while(q){
		cout<<q->elem<<" ";
		q=q->next;
	}
	return 0;	
}
