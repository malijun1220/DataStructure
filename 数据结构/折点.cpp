/*��Ŀ������������������һ��ʮ��������n��������n����������������������֮���֪�Ƿ�Ϊ�������½���
������ת�½������½�ת����Ϊ�۵㣬���۵�����������������һ�����ֵ���������������С����Ϊ�۵㡣*/
/*10/20/2019 ������ */
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
	cout<<"�������뼸������:";
	cin>>n;
	cout<<"��ʼ����:";
	CreateList(L,n);
	int total=0;
	PointList(L,total);
	cout<<"���۵���:"<<total;
	return 0; 
}
