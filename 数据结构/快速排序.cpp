/*实现快速排序算法    2019/12/12 马丽钧*/
//快速排序是对冒泡排序的一种改进
//通过一趟排序将待排记录分割成独立的两部分，其中一部分记录的关键字均比另一部分记录的关键字小 

//一趟排序结果 pivotkey处于左右两边数表的排好序后的中间位置，开始默认pivotkey为首元素 

//用栈的方法，每次进栈两个数据没栈两个数据，分别是pivotkey前面部分头和尾的位置，后一部分头和尾的位置 

#include<iostream>
using namespace std;
#include<cstdlib>
#define LIST_INIT_SIZE 100//初始分配空间
#define LISTINCREMENT 50//分配增量
#define STACK_INIT_SIZE 100 //初始分配 
#define STACKINCREMENT 20 
typedef struct Sqlist{
	int* data;
	int length;
	int listsize;
}Sqlist;
/*-----------------------------------------------------------------*/
typedef struct Stack{
	int *top;
	int *base;
	int stacksize;//当前可使用的最大容量 
} Stack;
void InitStack(Stack& S){
	S.base=(int *)malloc(STACK_INIT_SIZE*sizeof(int));
	if(!S.base){
		cout<<"fail";
		exit(0);
	}
	S.top=S.base;//目前栈无数据
	S.stacksize=STACK_INIT_SIZE; 	
} 
void GetTop(Stack S,int& e){
	if(S.top==S.base){
		cout<<"栈为空";
		exit(0);
	}
	else
		e=*(S.top-1);
}
void Push(Stack& S,int e){
	//if(true)则说并栈顶已经在已开辟的最后一个空间外 
	if(S.top-S.base>S.stacksize){
		int length=STACK_INIT_SIZE+STACKINCREMENT;
		S.base=(int *)realloc(S.base,length*sizeof(int));
		if(!S.base){
			cout<<"增添失败";
			exit(0);
		}
		S.top=S.base+S.stacksize;//设置栈顶 
		S.stacksize+=STACKINCREMENT;
	}
	*S.top++=e;//先等于，再++  <=> S.top=e;S.top++; 
}
void Pop(Stack& S,int &e){
	if(S.top==S.base){
		cout<<"空栈";
		exit(0);
	} 
	e=*--S.top;//因为top总指向当前栈顶元素的下一位置 
}
/*-----------------------------------------------------------------------*/
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
void PrintList(Sqlist& L){
	int i;
	for(i=0;i<L.length;i++){
		cout<<L.data[i]<<" ";
	}
}
void Partition(Sqlist& L,int low,int high){
	int pivotkey;
		Stack S;
	InitStack(S);
	int low1,high1,start,end,mid;
	Push(S,low);//先进low 
	Push(S,high);
	while(S.top!=S.base){
		Pop(S,high1);
		Pop(S,low1);
		start=low1; end=high1;
		pivotkey=L.data[low1];
		while(low1<high1){
			while(low1<high1&&pivotkey<=L.data[high1]){
				high1--;
			}
			L.data[low1]=L.data[high1];
			while(low1<high1&&pivotkey>=L.data[low1]){
				low1++;
			}
			L.data[high1]=L.data[low1];
		}
		L.data[low1]=pivotkey;
		mid=low1 ;
		if(start!=mid-1&&start<(mid-1)){
			Push(S,start);
			Push(S,mid-1);
		}
		if(mid+1!=end&&(mid+1)<end){
			Push(S,mid+1);
			Push(S,end);
		}
		cout<<"一趟快排结果: "; 
		PrintList(L);
		cout<<endl;	
	}
	
}

int main()
{
	Sqlist L;
	InitList(L);
	CreateList(L);
	int low,high;
	low=0;
	high=L.length-1;
	Partition(L,low,high);
	cout<<endl<<"排序结束后: ";
	PrintList(L);
	return 0;
}
//测试数据： 
 //49 38 65 97 76 13 27 49 0
 //12 6 8 4 56 78 6 5 32 1 5 6 48 0
