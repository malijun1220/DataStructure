/*���ݽṹ��Ŀ�������Ա�A��B��Ԫ��ֵΪ���ͣ��ҵ������򣬱�д����ʵ�����й��ܣ�
		�Բ���˳��ṹ����ʽ�ṹ2�ִ洢�ṹ��Ҫ����A�Ŀռ��Ϲ���һ�������Ա�C��
		��Ԫ��ΪA��BԪ�صĲ������ұ�C�е�Ԫ��ֵ�������򣨻�����ͬ��*/
/* ��ʽ�ṹ 10/19/2019 ������*/
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
	cout << "�� 0 ����: ";
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
		//Ԫ����ȣ�ִ����һѭ�� 
		if(flag){
			h=h0;//hָ����һ��λ��Ԫ�� 
			continue;
		}
		//��B��ǰԪ��С��A����ִ��������� 
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
	cout<<"����A,B�������ݶ����������"<<endl;
	cout<<"����A,";
	CreateList(LA);
	InitList(LB);
	cout<<"����B,";
	CreateList(LB);
	Union_A_B(LA,LB);
	p=LA->next;
	cout<<"�ϲ���LA���:";
	while(p){
		cout<<p->elem<<" ";
		p=p->next;
	}
	return 0;
}
