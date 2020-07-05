/*���װ������ ��ע���:�������е�����������1 �� n �� 2000, ai < bi < ai+1��ci < di < ci+1,
�������е�i(1 �� i �� n)�У�1 �� ai, bi, ci, di �� 1000000��
(�����ai+1��ָ��һ��a  �� a0 a1 ...) 
..........10/20/2019..... ������*/	

#include<iostream>
using namespace std; 
#include<cstdlib>
typedef struct LNode
{
	int begin;
	int end;  
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
		cin >> p->begin>>p->end;
		end->next = p;
		end = p;
		if (n==++i){
			break;
		}
	}
	end->next = NULL;
}
void TalkTime(LinkList LH,LinkList LW,int& time,int n){
	LinkList ph,pw;
	ph=LH->next;
	pw=LW->next;
	int i=1;
	while(i<=n){
		if(ph->begin<=pw->begin){
			//û��ʱ���ཻ 
			if(ph->end<=pw->begin){
				i++;
				continue;
			}
			else{
				//LWʱ�������LHʱ���� 
				if(ph->end>=pw->end){
					time+=pw->end-pw->begin;
				}
				//LHʱ���LWʱ������ཻ 
				else{
					time+=ph->end-pw->begin;
				}
			}
			
		}
		else{
			//û��ʱ���ཻ
			if(ph->begin>=pw->end){
				i++;
				continue;
			}
			else{
				//LHʱ���LWʱ������ཻ 
				if(ph->end>=pw->end){
					time+=pw->end-ph->begin;
				}
				//LHʱ�������LWʱ���� 
				else{
					time+=ph->end-ph->begin;
				}
				
			}
		}
		i++;
		ph=ph->next;
		pw=pw->next; 
	}
}
int main()
{
	LinkList LH,LW,p,q;
	int n,time;
	cout<<"Ҫ��:��һ��ʱ��εĽ�βҪС����һ��ʱ��εĿ�ͷ"<<endl; 
	cout<<"�������뼸��ʱ���(1<=n<=2000):";
	cin>>n;
	InitList(LH);
	cout<<"����ʱ���(1<ai,bi,ci,di<1000000)" <<endl;
	cout<<"��ʼ����LH (ai & bi):"<<endl;
	CreateList(LH,n);
	InitList(LW);
	cout<<"��ʼ����LW (ci & di):"<<endl;
	CreateList(LW,n);
	time=0;
	TalkTime(LH,LW,time,n);
	cout<<"����ʱ��:"<<time<<endl;
	return 0; 
}
