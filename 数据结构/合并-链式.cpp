/*数据结构题目：设线性表A、B，元素值为整型，且递增有序，编写程序，实现下列功能：
		对采用顺序结构和链式结构2种存储结构，要求在A的空间上构成一个新线性表C，
		其元素为A和B元素的并集，且表C中的元素值递增有序（互不相同）*/
/* 链式结构 10/19/2019 马丽钧*/
#include<iostream>
using namespace std;
#include<cstdlib>
typedef struct List{
	int elem;
	struct List* next;
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
	end = p = head;
	head->next = NULL;
	bool flag = true;
	cout << "以 0 结束: ";
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
void Union_A_B(LinkList& LA,LinkList LB){
	LinkList qa,pa,h0,h;
	qa=LA;
	pa=LA->next;
	h0=h=LB->next;
	bool flag;
	while(h){
		flag=false;
		h0=h0->next;
		if(h->elem>=pa->elem){
			while(h->elem>=pa->elem){
				qa=pa;
				if(h->elem==pa->elem){
					flag=true;
					break;
				}
				if(pa->next==NULL){
					break;
				}
				pa=pa->next;
			}
		}
		//元素相等，执行下一循环 
		if(flag){
			h=h0;//h指向下一个位置元素 
			continue;
		}
		//若B当前元素小于A，则执行以下语句 
		h->next=qa->next;
		qa->next=h;
		pa=h;
		h=h0;
	}	
}

int main()
{
	LinkList LA,LB,p;
	InitList(LA);
	cout<<"输入A,B表中数据都呈有序递增"<<endl;
	cout<<"输入A,";
	CreateList(LA);
	InitList(LB);
	cout<<"输入B,";
	CreateList(LB);
	Union_A_B(LA,LB);
	p=LA->next;
	cout<<"合并后LA输出:";
	while(p){
		cout<<p->elem<<" ";
		p=p->next;
	}
	return 0;
}
