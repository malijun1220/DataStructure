/*买菜装车问题 ，注意点:对于所有的评测用例，1 ≤ n ≤ 2000, ai < bi < ai+1，ci < di < ci+1,
对于所有的i(1 ≤ i ≤ n)有，1 ≤ ai, bi, ci, di ≤ 1000000。
(这里的ai+1是指下一个a  即 a0 a1 ...) 
..........10/20/2019..... 马丽钧*/	

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
			//没有时间相交 
			if(ph->end<=pw->begin){
				i++;
				continue;
			}
			else{
				//LW时间包含在LH时间内 
				if(ph->end>=pw->end){
					time+=pw->end-pw->begin;
				}
				//LH时间和LW时间存在相交 
				else{
					time+=ph->end-pw->begin;
				}
			}
			
		}
		else{
			//没有时间相交
			if(ph->begin>=pw->end){
				i++;
				continue;
			}
			else{
				//LH时间和LW时间存在相交 
				if(ph->end>=pw->end){
					time+=pw->end-ph->begin;
				}
				//LH时间包含在LW时间内 
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
	cout<<"要求:上一个时间段的结尾要小于下一个时间段的开头"<<endl; 
	cout<<"你想输入几个时间段(1<=n<=2000):";
	cin>>n;
	InitList(LH);
	cout<<"输入时间段(1<ai,bi,ci,di<1000000)" <<endl;
	cout<<"开始输入LH (ai & bi):"<<endl;
	CreateList(LH,n);
	InitList(LW);
	cout<<"开始输入LW (ci & di):"<<endl;
	CreateList(LW,n);
	time=0;
	TalkTime(LH,LW,time,n);
	cout<<"聊天时间:"<<time<<endl;
	return 0; 
}
