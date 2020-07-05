/*首先输入正整数n，接着输入n个正整数，如果其中存在一个数，比该数大的个数等于比该数小的个数，则输出该数，如果不存在则输出-1。
  ————顺序栈 将所有重复的数据去掉，不相同的数据入栈，计算个数，若为偶，则无中间数；若为奇，则有 
  马丽钧   10/25/2019*/
#include<iostream>
using namespace std;
#include<cstdlib>
typedef struct Stack{
	int *top;
	int *base;
	int stacksize;//当前可使用的最大容量 
} Stack;
void InitStack(Stack& S, int n){
	S.base=(int *)malloc(n*sizeof(int));
	if(!S.base){
		exit(0);
	}
	S.top=S.base;//目前栈无数据
	S.stacksize=n; 	
} 
void Push(Stack& S,int e){
	*S.top++=e; 
}
//栈顶元素出栈，并用e返回 
void Pop(Stack& S,int &e){
	if(S.top==S.base){
		cout<<"空栈";
		exit(0);
	} 
	e=*--S.top;//因为top总指向当前栈顶元素的下一位置 
}
void CreateStack(Stack& Q,int n){
	for(int i=0;i<n;i++){
		cin>>*Q.top++;
	}
}
bool SearchData(Stack& Q,Stack& Q1,int& middata){
	int i=0,e;
	bool flag=true;
	int length;
	while(Q.base!=Q.top){
		Pop(Q,e);
		length=Q1.top-Q1.base;
		while(i++<length){
			if(e==*(Q1.base+i))
				flag=false;
		}
		if(flag){
			Push(Q1,e);
		}
		flag=true;
		i=0;
	}
	length=Q1.top-Q1.base;
	//不重复个数为偶数个，则没有此中间数 
	if(length%2==0){
		return false;
	}
	else{
		int arr[length],t;
		i=0;
		while(Q1.base!=Q1.top){
		arr[i++]=*(--Q1.top);//将栈内元素取出 
		}
		//排序，中间数即为所求 
		for(i=0;i<length-1;i++){
			for(int j=i+1;j<length;j++){
				if(arr[i]>arr[j]){
					t=arr[i];
					arr[i]=arr[j];
					arr[j]=t;
				}
			}
		}
		middata=arr[(length-1)/2];
		return true;
	}
	
	 
} 
int main()
{
	Stack Q,Q1;//Q存放输入数据，Q1存放不重复数据 
	int n,middata;
	cout<<"你想输入N个数据:";
	cin>>n;
	InitStack(Q,n);
	CreateStack(Q,n);
	InitStack(Q1,n);
	if(SearchData(Q,Q1,middata)){
		cout<<"存在该数为:"<<middata;
	}
	else
		cout<<"-1";
}
