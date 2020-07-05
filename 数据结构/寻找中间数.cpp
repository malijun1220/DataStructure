/*��������������n����������n����������������д���һ�������ȸ�����ĸ������ڱȸ���С�ĸ������������������������������-1��
  ��������˳��ջ �������ظ�������ȥ��������ͬ��������ջ�������������Ϊż�������м�������Ϊ�棬���� 
  ������   10/25/2019*/
#include<iostream>
using namespace std;
#include<cstdlib>
typedef struct Stack{
	int *top;
	int *base;
	int stacksize;//��ǰ��ʹ�õ�������� 
} Stack;
void InitStack(Stack& S, int n){
	S.base=(int *)malloc(n*sizeof(int));
	if(!S.base){
		exit(0);
	}
	S.top=S.base;//Ŀǰջ������
	S.stacksize=n; 	
} 
void Push(Stack& S,int e){
	*S.top++=e; 
}
//ջ��Ԫ�س�ջ������e���� 
void Pop(Stack& S,int &e){
	if(S.top==S.base){
		cout<<"��ջ";
		exit(0);
	} 
	e=*--S.top;//��Ϊtop��ָ��ǰջ��Ԫ�ص���һλ�� 
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
	//���ظ�����Ϊż��������û�д��м��� 
	if(length%2==0){
		return false;
	}
	else{
		int arr[length],t;
		i=0;
		while(Q1.base!=Q1.top){
		arr[i++]=*(--Q1.top);//��ջ��Ԫ��ȡ�� 
		}
		//�����м�����Ϊ���� 
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
	Stack Q,Q1;//Q����������ݣ�Q1��Ų��ظ����� 
	int n,middata;
	cout<<"��������N������:";
	cin>>n;
	InitStack(Q,n);
	CreateStack(Q,n);
	InitStack(Q1,n);
	if(SearchData(Q,Q1,middata)){
		cout<<"���ڸ���Ϊ:"<<middata;
	}
	else
		cout<<"-1";
}
