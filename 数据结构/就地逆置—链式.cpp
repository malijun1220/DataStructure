/*���ݽṹϰ�⼯ 18-2.21 ��ʽ�ṹת�� 12/10/2019 ������*/

#include<iostream>
#include<stdlib.h>
using namespace std;
typedef struct List_L {
	int data;
	struct List_L* next;
}LNode,*LinkList;
void InitList(LinkList& L) {
	L = (LNode*)malloc(sizeof(LNode));
	if (!L) {
		cout << "fail";
		exit(0);
	}
	L->next = NULL;
}
void CreatList(LinkList& L) {
	LinkList head, end, p;
	head = L;
	end = p = head;
	head->next = NULL;
	bool flag = true;
	cout << "�� 0 ����" << endl;
	while (flag) {
		p = (LNode*)malloc(sizeof(LNode));
		cin >> (p->data);
		if (p->data == 0)
		{
			break;
		}
		end->next = p;
		end = p;
	}
	end->next = NULL;
}
void Inversiondata(LinkList &L) {
	LinkList p,q;
	p = L->next;//����ַ�����µ�
	L->next=NULL;//���巨
	while (p) {
		q = p->next;
		p->next = L->next;
		L->next = p;
		p = q;
	}
}
void PutList(LinkList& L) {
	LinkList p = L->next;
	while (p) {
		cout << p->data<<" ";
		p = p->next;
	}
}
int main()
{
	LinkList L;
	InitList(L);
	CreatList(L);
	Inversiondata(L);
	PutList(L);
}
