w/*数据结构题目：设线性表A、B，元素值为整型，且递增有序，编写程序，实现下列功能：
		对采用顺序结构和链式结构2种存储结构，要求在A的空间上构成一个新线性表C，
		其元素为A和B元素的并集，且表C中的元素值递增有序（互不相同）
		*/
/* 顺序结构 	------本题不允许开辟C空间，而是在A基础上增添空间。   10/19/2019 马丽钧*/
#include<iostream>
using namespace std;
#include<stdlib.h>
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 100 
typedef struct List{
	int *elem;//有序递增
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
	cout << "以 0 结束" << endl;
	for (i = 0; i < L.listsize; i++) {
		cin >> L.elem[i];
		L.length++;
		if (L.elem[i] == 0) {
			L.length--;
			break;
		}
		if (i >= L.listsize - 1) {
			int* newbase;
			int Length = L.length + LISTINCREMENT;//不替换则会溢出
			newbase = (int*)realloc(L.elem, Length * sizeof(int));//原来的基础上重新分配空间，L.elem是原来的首地址
			if (!newbase) {
				cout << "space increase fail";
				exit(0);
			}
			L.elem = newbase;//在原来的基础上增加，首地址没有变
			L.listsize = Length;
			cout << "space increase succeed" << endl;
		}

	}
	cout <<"输入长度: "<<L.length << endl;
}
void Union_A_B(Sqlist& L_A,Sqlist L_B){
	Sqlist p,q;
	int length_C;
	length_C=L_A.length+L_B.length;
	//判断在最糟糕情况下 A的空间是否够全部存下A B所有数据 
	if(L_A.listsize<length_C){
		int* newbase;
		newbase = (int*)realloc(L_A.elem, length_C * sizeof(int));//原来的基础上重新分配空间，L.elem是原来的首地址
		if (!newbase) {
			cout << "space increase fail";
			exit(0);
		}
		L_A.elem = newbase;//在原来的基础上增加，首地址没有变
		L_A.listsize = length_C;
		cout << "space increase succeed" << endl;		
	}
	int i=0,length_A=L_A.length;//表示A 
	int j=0;//表示B
	bool flag;
	while(j<L_B.length){
		flag=false;
		if(L_A.elem[i]<=L_B.elem[j]){
			while(L_A.elem[i]<=L_B.elem[j]&&i<length_A){
				if(L_A.elem[i]==L_B.elem[j]){
					flag=true;
					break;
				}
				i++;
			}
			if(!flag){
				for(i;i<length_A;length_A--){
				L_A.elem[length_A]=L_A.elem[length_A-1];
				}
				L_A.elem[i]=L_B.elem[j];
			}
		}
		else{
			for(i;i<length_A;length_A--){
				L_A.elem[length_A]=L_A.elem[length_A-1];
			}
			L_A.elem[i]=L_B.elem[j];
		}
		if(flag){
			j++;
			continue;
		}
		length_A=L_A.length;
		length_A++;
		L_A.length=length_A;
		j++;
		
	}	
}
int main(){
	Sqlist L_A;
	Sqlist L_B;
	InitList(L_A);
	cout<<"输入A,B表中数据都呈有序递增"<<endl; 
	cout<<"输入A:";
	CreateList(L_A);
	InitList(L_B);
	cout<<"输入B:";
	CreateList(L_B);
	Union_A_B(L_A,L_B);
	cout<<"合并后:";
	for(int i=0;i<L_A.length;i++){
		cout<<L_A.elem[i]<<" ";
	}
	return 0;
}
