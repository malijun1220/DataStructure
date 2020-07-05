/*数据结构 第二章 线性表的链式表示
2019-10-4 马丽钧
*/
#include<iostream>
using namespace std;
#include<cstdlib>
typedef struct LNode
{
	int data;  //储存空间基址
	struct LNode* next;
}LNode, *LinkList;	
void InitList(LinkList& L) {
	L = (LNode*)malloc(sizeof(LNode));
	if (!L) {
		cout << "fail";
		exit(0);
	}
	L->next = NULL;
	cout << "succeed" << endl;
}
void DestoryList(LinkList& L) {
	LinkList p;
	while (L->next) {
		p = L->next;
		free(L);
		L= p;
	}
}
void ClearList(LinkList& L) {
	LinkList p,q;
	p = L->next;
	while (p) {
		q = p->next;
		free(p);
		p = q;
	}
	L->next = NULL;
}
bool ListEmpty(LinkList L) {
	if (L->next)
		return  false;
	else
		return true;
}
int ListLength(LinkList L) {
	int i = 0;
	LinkList p;
	p = L->next;
	while (p) {
		i++;
		p = p->next;
	}
	return i;
}
bool GetElem(LinkList L, int i, int& e) {
	int j = 1;
	LinkList p;
	p = L->next;//指向第一个节点
	while (p && j < i) {
		p = p->next;
		j++;
	}
	if (!p || j > i)
		return false;
	e = p->data;
	return true;
}
int LocatElem(LinkList L, int e) {
	int i = 0;
	LinkList p;
	p = L->next;
	bool compare(int, int);
	while (p) {
		i++;
		p = p->next;
	}
	return 0;
}
bool PriorElem(LinkList L, int cur_e, int& pre_e) {
	LinkList q, p;
	p = L->next;
	while (p->next) {
		q = p->next;
		if (q->data == cur_e) {
			pre_e = p->data;
			return true;
		}
		p = q;
	}
	return false;
}
bool NextElem(LinkList L, int cur_e, int& next_e){
	LinkList p;
	p = L->next;
	while (p->next) {
		if (p->data == cur_e) {
			next_e = p->next->data;
			return true;
		}
		p = p->next;
	}
	return false;
}
bool ListInsert(LinkList &L, int i, int e) {
	LinkList p,s;
	p = L;   //头结点是没有东西的，所以下边是j<i-1;如果p=L->next，则j<i;
	int j = 0;
	while (p && j < i-1){
		p = p->next;
		j++;
	}
	if (!p ||j > i - 1)
		return false;
	s = (LNode*)malloc(sizeof(LNode));
	s->data = e;
	s->next = p->next;
	p->next = s;
	return true;
}
bool ListDelete(LinkList& L, int i, int& e) {
	int j = 0;
	LinkList p,q;
	p = L;//如果p->next是空的，就没法删除
	while (p->next && j < i - 1) {
		p = p->next;
		j++;
	}
	if (!(p->next) || j > i - 1)
		return false;
	q = p->next;
	p->next = q->next;
	e = q->data;
	free(q);
	return true;
}
void ListTraverse(LinkList L) {
	LinkList p;
	p = L->next;

	while (p) {

		p = p->next;
	}
}
void CreateList(LinkList &L) {
	LinkList head, end, p;
	head = L;
	end =  head;
	head->next = NULL;
	bool flag = true;
	cout << "以 0 结束" << endl;
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
int main()
{
	LinkLisrt L;
	InitList(L);
	CreateList(L);
} 
