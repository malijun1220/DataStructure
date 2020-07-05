/*数据结构 习题集 P18 2.21T  10.12 顺序结构转置  马丽钧  */

#include<stdlib.h>
#include<iostream>
using namespace std;
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
typedef struct List_Sq {
	int *elem;
	int length;//当前长度
	int listsize;//总长度
}Sqlist;
void InitList(Sqlist &L) {
	L.elem = (int*)malloc(LIST_INIT_SIZE * sizeof(int));
	if (!L.elem) {
		cout << "fail";
		exit(0);
	}
	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
}
void IncreaseSpace(Sqlist &L) {
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
void CreatList(Sqlist& L) {
	int i;
	cout << "以 0 结束" << endl;
	for (i = 0; i < L.listsize; i++) {
		cin >> L.elem[i];
		L.length++;
		if (L.elem[i] == 00) {
			L.length--;
			break;
		}
		if (i >= L.listsize - 1)
			IncreaseSpace(L);

	}
}
void Putdata(Sqlist& L) {
	for (int i = 0; i < L.length; i++) {
		cout << L.elem[i]<<" ";
	}
}
void Inversiondata(Sqlist L) {
	int elem_exch;
	int midlen, length;
	if (L.length % 2 == 0) {
		midlen = L.length / 2;
		length = L.length;
		for (int i = 0; i < midlen; i++,length--) {
			elem_exch = L.elem[i];
			L.elem[i] = L.elem[length-1];
			L.elem[length-1] = elem_exch;
		}
	}
	else if (L.length % 2 == 1) {
		midlen = (L.length - 1) / 2;
		length = L.length;
		for (int i = 0; i < midlen; i++,length--) {
			elem_exch = L.elem[i];
			L.elem[i] = L.elem[length - 1];
			L.elem[length - 1] = elem_exch;
		}
	}
	cout << "exchange succeed" << endl;
}
int main()
{
	Sqlist L;
	InitList(L);
	CreatList(L);
	Inversiondata(L);
	Putdata(L);
	return 0;
}
