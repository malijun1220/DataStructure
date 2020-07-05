/*习题册 3.20 假设以二维数组g(1..m,1..n)，g[i,j]表示该区域中点(i,j)所具有颜色，其值为从0到k的整数。
编写算法置换点(i0,j0)所在区域的颜色。约定和(i0,j0)同色的上下左右的邻接点为同色区域的点。
即改变(i0,j0)同色区域的颜色*/
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
	cout<<"输入每个点g[i,j]的颜色:";
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
	cout<<"所创建二维数组的行，列(m,n):";
	cin>>m>>n;
	InitLsit(L,m*n);
	cout<<"每个点颜色取值范围1~k(输入k):";
	int k;
	cin>>k;
	CreateList(L,m,n);
	FindSameColor(L);
}
