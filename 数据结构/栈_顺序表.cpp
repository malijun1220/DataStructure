/* 栈的抽象函数表——顺序结构     10/23/2019  马丽钧*/ 
#include<iostream>
using namespace std;
#include<cstdlib>
#define STACK_INIT_SIZE 100 //初始分配 
#define STACKINCREMENT 20 //增量 
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
void DestroyStack(Stack& S){
	S.base=NULL; 
	S.base=S.top;
	S.stacksize=0;
}
void ClearStack(Stack& S){
	S.base=S.top;
	S.stacksize=0;
}
//探空 
bool StackEmpty(Stack S){
	if(S.top!=S.base)
		return true;
	else
		return false;
	
}
int StackLength(Stack S){
	return (S.top-S.base);
}
//返回栈顶元素 
void GetTop(Stack S,int& e){
	if(S.top==S.base){
		cout<<"栈为空";
		exit(0);
	}
	else
		e=*(S.top-1);
}
//插入e为栈顶元素 
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
//栈顶元素出栈，并用e返回 
void Pop(Stack& S,int &e){
	if(S.top==S.base){
		cout<<"空栈";
		exit(0);
	} 
	e=*--S.top;//因为top总指向当前栈顶元素的下一位置 
}
void StackTraverse(Stack S){
	for(int i=0;i<S.top-S.base;i++){
		cout<<*(S.base+i)<<" ";
	}
}
int main(){
	Stack S;
	InitStack(S) ;
	return 0;
}
