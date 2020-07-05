/*实现交换(冒泡)、选择、归并等简单排序算法  2019/12/12 马丽钧*/
//写插入排序************************ 
#include<iostream>
using namespace std;
#include<cstdlib>
#include<cmath>
#define LIST_INIT_SIZE 100//初始分配空间
#define LISTINCREMENT 50//分配增量
typedef struct Sqlist{
	int *data;
	int length;  //当前长度
	int listsize;
}Sqlist;
void InitList(Sqlist& L){
	L.data = (int*)malloc(LIST_INIT_SIZE * sizeof(int));
	if (!L.data) {
		cout << "fail";
		exit(0);
	}
	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
} 
void CreateList(Sqlist& L){
	int i;
	cout << "以 0 结束:";
	for (i = 0; i < L.listsize; i++) {
		cin >> L.data[i];
		L.length++;
		if (L.data[i] == 0) {
			L.length--;
			break;
		}
		if (i >= L.listsize - 1) {
			int* newbase;
			int Length = L.length + LISTINCREMENT;//不替换则会溢出
			newbase = (int*)realloc(L.data, Length * sizeof(int));//原来的基础上重新分配空间，L.elem是原来的首地址
			if (!newbase) {
				cout << "space increase fail";
				exit(0);
			}
			L.data = newbase;//在原来的基础上增加，首地址没有变
			L.listsize = Length;
			cout << "space increase succeed" << endl;
		}

	}
	cout <<"输入长度: "<<L.length << endl;
}
void BubbleSort(Sqlist& L){
	if(L.length<2){
		exit(0);
	}
	cout<<"交换排序:";
	int i,j,t;	
	for(i=0;i<L.length-1 ;i++){
		for(j=0;j<L.length-i-1;j++){
			if(L.data[j]>L.data[j+1]){
				t=L.data[j];
				L.data[j]=L.data[j+1];
				L.data[j+1]=t;	
			}
		}
	}
	
}
void SelectionSort(Sqlist& L){
	if(L.length<2){
		exit(0);
	}
	cout<<"选择排序:";
	int i,j,t;
	for(i=0;i<L.length-1;i++){
		for(j=i+1;j<L.length;j++){
			if(L.data[i]>L.data[j]){
				t=L.data[i];
				L.data[i]=L.data[j];
				L.data[j]=t;
			}
		}
	}
}
void PrintList(Sqlist L){
	int i;
	for(i=0;i<L.length;i++){
		cout<<L.data[i]<<" ";
	}
}
void InsertList(Sqlist& L,int beg_locat,int width){
	int i,j,t;
	for(i=beg_locat;i<beg_locat+width-1;i++){//选择排序 
		for(j=i+1;j<beg_locat+width;j++){
			if(L.data[i]>L.data[j]){
				t=L.data[i];
				L.data[i]=L.data[j];
				L.data[j]=t;
			}
		}
	}	
}
void MergingSort(Sqlist& L){
	if(L.length<2)
		exit(0);
	cout<<"并归排序过程如下:"<<endl;
	int i,j;
	int arrwidth=2,n;//第一趟并归为两个数据一组 49 38 65 97 76 13 27
	bool flag=true;
	while(flag){
		if((L.length/arrwidth)*arrwidth<L.length)
			n=L.length/arrwidth+1;//总数据有奇数个时候 
		else n=L.length/arrwidth;
		for(j=0;j<n;j++){
			if(j==0&&L.length<(j+1)*arrwidth){//用来处理最后一个并归 
				InsertList(L,j*arrwidth,L.length);
				flag=false;	
			}
			else{//处理末尾长度不足的数据 
				if((j+1)*arrwidth>L.length)
					InsertList(L,j*arrwidth,L.length-j*arrwidth);//用来处理中间并归过程中末尾数据不足宽度的情况 
				else
					InsertList(L,j*arrwidth,arrwidth);//非末尾情况 
			}
		}
		PrintList(L);
		cout<<endl;
		arrwidth*=2;
	}	
}
int main()
{
	Sqlist L;
	InitList(L);
	CreateList(L);
//	BubbleSort(L);
//	SelectionSort(L);
	MergingSort(L);
//	PrintList(L);
	return 0;//49 38 65 97 76 13 2749 38 65 97 76 13 27
}
//测试数据  49 38 65 97 76 13 27 
