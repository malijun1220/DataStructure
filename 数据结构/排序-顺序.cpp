/*选择排序法实现线性表的排序问题   顺序结构 10/19/2019  马丽钧*/
#include<iostream>
using namespace std;
#include<stdlib.h>
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10 
typedef struct Lsit{
	int *elem;
	int length;
	int listsize;
}Sqlist;
void InitList(Sqlist& L){
	L.elem = (int*)malloc(LIST_INIT_SIZE * sizeof(int));
	if (!L.elem) {
		cout << "fail";
		exit(0);
	}
	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
}
void CreateList(Sqlist& L){
	int i;
	cout << "over when enter 0" << endl;
	for (i = 0; i < L.listsize; i++) {
		cin >> L.elem[i];
		L.length++;
		if (L.elem[i] == 0) {
			L.length--;
			break;
		}
		if (i >= L.listsize - 1) {
			int* newbase;
			int Length = L.length + LISTINCREMENT;
			newbase = (int*)realloc(L.elem, Length * sizeof(int));//原来的基础上重新分配空间，L.elem是原来的首地址
			if (!newbase) {
				cout << "need to increase space but fail";
				exit(0);
			}
			L.elem = newbase;//在原来的基础上增加，首地址没有变
			L.listsize = Length;
			cout << "need to increase space and succeed" << endl;
		}

	}
	cout <<"输入长度: "<<L.length << endl;
}
void SortList(Sqlist &L){
	int i,j;
	int t;
	for(i=0;i<L.length-1;i++){
		for(j=i+1;j<L.length;j++){
			if(L.elem[i]>L.elem[j]){
				t=L.elem[i];
				L.elem[i]=L.elem[j];
				L.elem[j]=t;	
			}
		}
	}
} 
int main()
{
	Sqlist L;
	InitList(L);
	CreateList(L);
	SortList(L);
	cout<<"排序后输出: "; 
	for(int i=0;i<L.length;i++){
		cout<<L.elem[i]<<" ";
	}
	return 0;
}
 
