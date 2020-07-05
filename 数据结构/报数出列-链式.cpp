/*数据结构  第三题 顺序结构 10/12/2019 马丽钧  
输入正整数n、m（m<n），设有n个人坐成一圈，从第1个人开始循环报数，报到m的人出列，然后再从下一个人开始报数，
报到m的人又出列，如此重复，直到所有的人都出列为止。
要求用链式结构和顺序结构实现，按出列的先后顺序输出每个人的信息*/
#include<iostream>
#include<stdlib.h>
using namespace std;
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
typedef struct LNode
{
	int data;  //储存空间基址
	struct LNode* next;
}LNode, * LinkList;	
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
	end = p = head;
	head->next = NULL;
	bool flag = true;
	cout << "以 0 结束" << endl;
	while (flag) {
		p = (LNode*)malloc(sizeof(LNode));
		cin >> (p->data);
		if (p->data == 00)
		{
			break;
		}
		end->next = p;
		end = p;
	}
	end->next = NULL;
}
void Listout(LinkList &L,int n){
	int Listlength, order = 0,i = 0;
	LinkList head,q,p;
	head=q=L;
	//循环链表 
	while(q->next){
		p=q->next;
		q=p;
		Listlength++;
	}
	q->next=head->next;  
	q=q->next;//尾指针指向首元素地址
	
	while(true){
		if(q->data==0){
			q=q->next;
			continue;
		}
		order++;
		if(order%n==0){
			i++;
			cout << "第" << i << "个 " << q->data << "出列" << endl;	
			q->data=0;
			q=q->next;
		}
		else
			q=q->next;
		if (i == Listlength)
			break;
	}
} 
int main()
{
	LinkList L;
	int n;
	InitList(L);
	CreateList(L);
	cout << "输入你想出局的报数数字:";
	cin >> n;
	Listout(L,n);
	return 0;
}
