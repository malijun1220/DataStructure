/*数据结构 第二章  线性表(1.顺序(动态))  
2019-9-16 马丽钧*/

#include<iostream>
#include<cstdlib>
using namespace std;
#define LIST_INIT_SIZE 10//初始分配空间
#define LISTINCREMENT 10//分配增量
typedef struct ADTList
{
	int* elem;  //储存空间基址
	int length;  //当前长度
	int listsize; //当前分配的储存容量
}Sqlist;
// 构造一个空的线性链表
void InitList(Sqlist& L){
	L.elem = (int*)malloc(LIST_INIT_SIZE * sizeof(int));
	if (!L.elem) {
		cout << "fail";
		exit(0);
	}
	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
}
//销毁线性表L
void DestoryList(Sqlist& L) {
	if (L.elem)
		free(L.elem);//顺序表是不需要free的，链表才需要 
	L.elem = NULL;  //后面的当做没有
	L.length = 0;
	L.listsize = 0;
	}
//重置L为空表
void ClearList(Sqlist& L) {
	L.length = 0;
}
//若为L为空表，则返回true
bool ListEmpty(Sqlist L) {
	if (L.length == 0)
		return true;
	else
		return false;
}
//若为L为空表，则返回true
int ListLength(Sqlist &L) {
	return L.length;
}
//用e返回L中第i个数据元素的值
void GetElem(Sqlist L, int i, int& e) {
	if (L.length == 0 || i<1 || i>L.length){
		cout<<"获取失败"<<endl;
		exit(0); 
	}
	e =*(L.elem + i - 1); //L.elem首地址

}
//返回L中第1个与e满足关系compare（）的数据元素的位序，若不存在则返回值为0
void LocatElem(Sqlist L, int e) {
	int i = 1;
	int* p;
	p = L.elem;
	bool compare(int, int);
	while (i <= L.length && !compare(*p++, e)) //指针做函数参数，不满足继续，满足结束
		++i;
	if (i <= L.length)
		cout << i;
	else 
		cout<<"无匹配值"<<endl;

}
//若cur_e是L的数据元素，且不是第一个，则用pre_e返回他的前驱，否则操作失败。pre_e无定义
bool PriorElem(Sqlist L, int cur_e, int & pre_e) {
	int i = 2;
	int* p = L.elem + 1;  //第二个元素的地址  
	while (i <= L.length && *p != cur_e)  //值不相等
	{
		p++;
		i++;
	}
	if (i > L.length)
		return false;
	else {
		pre_e = *(--p);   //前驱值
	}
	return true;
}
//若cur_e是L的数据元素，且不是最后一个，则用next_e返回他的后续
bool NextElem(Sqlist L, int cur_e, int& next_e) {
	int i = 1;
	int* p = L.elem;
	while (i <= L.length && *p!= cur_e) {
		i++;
		p++;
	}
	if (i == L.length)
		return false;
	else {
	
		next_e = *++p;
	}
	return  true;
}
//在L中的第i个位置之前插入新的数据元素e，L的长度加 1
bool ListInsert(Sqlist &L, int i, int e) {
	if (i<1 || i>L.length+1) 
		return false;
	if (L.length >= L.listsize) {
		int* newbase;
		int length = L.listsize + LISTINCREMENT;//不替换则会溢出
		newbase = (int*)realloc(L.elem,(length) * sizeof(int)); //原来的基础上重新分配空间，L.elem是原来的首地址
		if (!newbase)
			return false;
		L.elem = newbase;  //在原来的基础上增加，首地址没有变
		L.listsize += LISTINCREMENT;
	}
	int *q,*p;
	q = L.elem + i - 1;
	for (p = L.elem + L.length - 1; p >= q; --p)//最后面的开始挪 
		* (p + 1) = *p;
	*q = e;
	++L.length;
	return true;
}
//删除L的第i个元素，并用e返回其值，L的长度减1
bool ListDelete(Sqlist& L,int i, int& e) {
	if (i<1 || i>L.length)
		return false;
	int* p, * q;
	p = L.elem + i - 1;
	e = *p;
	q = L.elem + L.length - 1;//当前长度的最后一个元素的地址   加*才是元素
	for (++p; p <= q; ++p)
		* (p - 1) = *p;
	--L.length;
	return true;

}
//一次对L的每个数据元素调用visit（），一旦失败，则操作失败
void ListTraverse(Sqlist L) {
	int* p;
	int i;
	p = L.elem;
	bool visit(int);
	for (i = 1; i <= L.length; i++) {
		if (!visit(*p++))
			break;
	}
	cout << "ok";
}
//创建链表，一个一个的输入进去
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
			L.elem = newbase;//在原来的基础上增加，首地址没有变  之前的数据也没有变 因为顺序表空间是连续的 
			L.listsize = Length;
			cout << "space increase succeed" << endl;
		}

	}
	cout <<"输入长度: "<<L.length << endl;
}
bool compare(int, int) {
	return true;
}
bool  visit(int) {
	return true;
}
int main()
{
	
}
