/*ϰ��� 3.20 �����Զ�ά����g(1..m,1..n)��g[i,j]��ʾ�������е�(i,j)��������ɫ����ֵΪ��0��k��������
��д�㷨�û���(i0,j0)�����������ɫ��Լ����(i0,j0)ͬɫ���������ҵ��ڽӵ�Ϊͬɫ����ĵ㡣
���ı�(i0,j0)ͬɫ�������ɫ*/
#include<iostream>
using namespace std;
#include<cstdlib>
typedef struct LNode{
	int *data;
	int length;
	int listsize;
}Sqlist;
void InitList(Sqist& L,int n){
	L.data=(int*)malloc(n*sizeof(int));
	if(!L){
		cout<<"fail";
		exit(0);
	}
	L.length=0;
	L.listsize=n;
} 
void CreateList(Sqlist& L,int m,int n){
	cout<<"����ÿ����g[i,j]����ɫ:";
	for(int i=0;i<m*n;i++){
		cin>>L.data[i];
	}
}
void FindSameColor(Sqlist& L){
	
}
int main()
{
	Sqlist L;
	int m,n;
	cout<<"��������ά������У���(m,n):";
	cin>>m>>n;
	InitLsit(L,m*n);
	cout<<"ÿ������ɫȡֵ��Χ1~k(����k):";
	int k;
	cin>>k;
	CreateList(L,m,n);
	FindSameColor(L);
}
