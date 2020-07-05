/*数据结构  第三题 顺序结构 10/12/2019 马丽钧  
输入正整数n、m（m<n），设有n个人坐成一圈，从第1个人开始循环报数，报到m的人出列，然后再从下一个人开始报数，
报到m的人又出列，如此重复，直到所有的人都出列为止。
要求用链式结构和顺序结构实现，按出列的先后顺序输出每个人的信息*/


#include<iostream>
#include<stdlib.h>
using namespace std;
#define LIST_INIT_SIZE 100//初始分配空间
#define LISTINCREMENT 10//分配增量
typedef struct List_Sq
{
	int* elem;  //储存空间基址
	int length;  //当前长度
	int listsize; //当前分配的储存容量
}Sqlist;
void InitList(Sqlist& L) {
	L.elem = (int*)malloc(LIST_INIT_SIZE * sizeof(int));
	if (!L.elem) {
		cout << "fail";
		exit(0);
	}
	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
}
void CreatList(Sqlist& L)
{
	int i;
	cout << "以 0 结束" << endl;
	for (i = 0; i < L.listsize; i++) {
		cin >> L.elem[i];
		L.length++;
		if (L.elem[i] == 00) {
			L.length--;
			break;
		}
		if (i >= L.listsize - 1) {
			int* newbase;
			int Length = L.length + LISTINCREMENT;
			newbase = (int*)realloc(L.elem, Length * sizeof(int));
			if (!newbase) {
				cout << "space increase fail";
				exit(0);
			}
			L.elem = newbase;
			L.listsize = Length;
			cout << "space increase succeed" << endl;
		}

	}
	cout << "你一共输入了 "<<L.length <<" 人"<< endl;
}
void Listout(Sqlist &L,int n) {
	int Listlength, order = 0, true_order=0,i = 0;
	Listlength = L.length;
	while (true) {
		order++;
		if (order % Listlength == 0) //顺序表的最后一个数字，此时order&Listlength==0，此时若-1没有指向 
			if (L.elem[Listlength - 1] == 0)
				continue;
		if (L.elem[order % Listlength-1]==0)
			continue;
		true_order++;
		if (true_order % n == 0) {
			i++;
			if (order % Listlength == 0) {
				cout << "第" << i << "个 " << L.elem[Listlength-1 ] << "出列" << endl; //顺序表最后一个数据 
				L.elem[ Listlength - 1] = 0;
			}
			else
			{
				cout << "第" << i << "个 " << L.elem[order % Listlength - 1] << "出列" << endl;
				L.elem[order % Listlength - 1] = 0;
			}
		}
		if (i == Listlength)
			break;
	}

}
int main()
{
	Sqlist L;
	int n;
	InitList(L);
	CreatList(L);
	cout << "输入你想出局的报数数字:";
	cin >> n;
	Listout(L,n);
	return 0;
}
