/*，统计输出其中的相邻数对（差值为1的数对） 马丽钧  11/2/2019*/
//还差后边数字重复怎么去掉 
#include<iostream>
using namespace std;
#include<cstdlib>
typedef struct LNode{
	int *elem;
	int length;
	int listsize;
}Sqlist;
void InitList(Sqlist& L,int n){
	L.elem = (int*)malloc(n * sizeof(int));
	if (!L.elem) {
		cout << "fail";
		exit(0);
	}
	L.length = 0;
	L.listsize = n;
}
void CreateList(Sqlist& L){
	int i;
	for (i = 0; i < L.listsize; i++) {
		cin >> L.elem[i];
		L.length++;
	}
}
void Cout_Print_Data(Sqlist L){
	int max;
	max=L.elem[0];
	int i=1;
	while(i<L.length){
		if(max<L.elem[i])
			max=L.elem[i];
		i++;		
	}
	Sqlist P;
	//一个萝卜一个坑，相邻有坑即是相邻数组 
	P.elem = (int*)malloc((max+1)* sizeof(int));
	P.length = L.length;
	P.listsize = max;
	int t;
	for(i=0;i<L.length;i++){
		t=L.elem[i];
		P.elem[t]=1;
	}
	for(i=1;i<=max;i++){
		if(P.elem[i]!=1){
			P.elem[i]=0;
		}
	}
	int count=0;
	//L.elem[0]不算，故作0  
	for(i=1;i<max;i++){
		if(P.elem[i]&&P.elem[i+1]){
			count++;
		} 
	} 
	cout<<"一共有 "<<count<<" 个相邻数对"; 
} 
int main()
{
	Sqlist L;
	int n;
	cout<<"输入数据总数(n):";
	cin>>n;
	InitList(L,n);
	CreateList(L);
	Cout_Print_Data(L);
	return 0;
}
