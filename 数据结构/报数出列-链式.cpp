/*���ݽṹ  ������ ˳��ṹ 10/12/2019 ������  
����������n��m��m<n��������n��������һȦ���ӵ�1���˿�ʼѭ������������m���˳��У�Ȼ���ٴ���һ���˿�ʼ������
����m�����ֳ��У�����ظ���ֱ�����е��˶�����Ϊֹ��
Ҫ������ʽ�ṹ��˳��ṹʵ�֣������е��Ⱥ�˳�����ÿ���˵���Ϣ*/
#include<iostream>
#include<stdlib.h>
using namespace std;
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
typedef struct LNode
{
	int data;  //����ռ��ַ
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
	cout << "�� 0 ����" << endl;
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
	//ѭ������ 
	while(q->next){
		p=q->next;
		q=p;
		Listlength++;
	}
	q->next=head->next;  
	q=q->next;//βָ��ָ����Ԫ�ص�ַ
	
	while(true){
		if(q->data==0){
			q=q->next;
			continue;
		}
		order++;
		if(order%n==0){
			i++;
			cout << "��" << i << "�� " << q->data << "����" << endl;	
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
	cout << "����������ֵı�������:";
	cin >> n;
	Listout(L,n);
	return 0;
}
