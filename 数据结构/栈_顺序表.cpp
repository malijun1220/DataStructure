/* ջ�ĳ���������˳��ṹ     10/23/2019  ������*/ 
#include<iostream>
using namespace std;
#include<cstdlib>
#define STACK_INIT_SIZE 100 //��ʼ���� 
#define STACKINCREMENT 20 //���� 
typedef struct Stack{
	int *top;
	int *base;
	int stacksize;//��ǰ��ʹ�õ�������� 
} Stack;
void InitStack(Stack& S){
	S.base=(int *)malloc(STACK_INIT_SIZE*sizeof(int));
	if(!S.base){
		cout<<"fail";
		exit(0);
	}
	S.top=S.base;//Ŀǰջ������
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
//̽�� 
bool StackEmpty(Stack S){
	if(S.top!=S.base)
		return true;
	else
		return false;
	
}
int StackLength(Stack S){
	return (S.top-S.base);
}
//����ջ��Ԫ�� 
void GetTop(Stack S,int& e){
	if(S.top==S.base){
		cout<<"ջΪ��";
		exit(0);
	}
	else
		e=*(S.top-1);
}
//����eΪջ��Ԫ�� 
void Push(Stack& S,int e){
	//if(true)��˵��ջ���Ѿ����ѿ��ٵ����һ���ռ��� 
	if(S.top-S.base>S.stacksize){
		int length=STACK_INIT_SIZE+STACKINCREMENT;
		S.base=(int *)realloc(S.base,length*sizeof(int));
		if(!S.base){
			cout<<"����ʧ��";
			exit(0);
		}
		S.top=S.base+S.stacksize;//����ջ�� 
		S.stacksize+=STACKINCREMENT;
	}
	*S.top++=e;//�ȵ��ڣ���++  <=> S.top=e;S.top++; 
}
//ջ��Ԫ�س�ջ������e���� 
void Pop(Stack& S,int &e){
	if(S.top==S.base){
		cout<<"��ջ";
		exit(0);
	} 
	e=*--S.top;//��Ϊtop��ָ��ǰջ��Ԫ�ص���һλ�� 
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
