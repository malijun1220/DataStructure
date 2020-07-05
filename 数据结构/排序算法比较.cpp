//ֱ�Ӳ�������ϣ������ð�����򡢿�������ѡ�����򡢶����򣬹鲢���򡢻�������
#include<iostream>
using namespace std;
#include<algorithm>  //sort 
#include<cstdlib>
#include<fstream>
#include<time.h>
#include<windows.h>
#include<math.h> 
#define STACK_INIT_SIZE 50000 //��ʼ���� 
#define LIST_INIT_SIZE 50000
#define N  50000
typedef struct Stack{
	int *top;
	int *base;
	int stacksize;//��ǰ��ʹ�õ�������� 
} Stack;
//�������� 
typedef struct Sqlist{
	int* elem;
}Sqlist;
typedef struct QNode{
	int elem;
	struct QNode *next;
}QNode,*QueuePtr;
typedef struct{
	QueuePtr front;//��ͷָ�� 
	QueuePtr rear;//��βָ�� 
}LinkQueue;
char filename[10][20]={{"datasample1.txt"},{"datasample2.txt"},{"datasample3.txt"},
					{"datasample4.txt"},{"datasample5.txt"},{"datasample6.txt"},
					{"datasample7.txt"},{"datasample8.txt"},{"datasample9.txt"},
					{"datasample10.txt"}};
int a[50001];
ifstream file_i;
ofstream file_o;
	
SYSTEMTIME time_begin,time_end;//��ȡϵͳʱ�� 

void InsertSort(int i);
void ShellSort(int i);  //�����������зֱ����ֱ�Ӳ��뷨 
void BubbleSort(int i);//Ҳ�н��� 
void QuickSort(int i);
void SelectSort(int i);
void HeapSort(int i);//�� 
void MergeSort(int i);//���� 
void RadixSort(int i);//�������� 
bool compare(int a,int b);
void InitStack(Stack& S);
void Push(Stack& S,int e);
void Pop(Stack& S,int &e);
void HeapAdjust(int a[],int n,int k);
void InsertList(int a[],int beg_locat,int width);
void InitQueue(LinkQueue& Q);
void EnQueue(LinkQueue& Q,int e);
void DeQueue(LinkQueue& Q,int &e);
void InitList(Sqlist& L);
int main(){
	int i,j;
	for(i=0;i<10;i++){
		srand( (unsigned)time( NULL ) );//��ʼ�������  ʱ����������� 
		file_o.open(filename[i],ios::out);	
		if(i==0){
			for(j=0;j<N;j++)             
				a[j]=rand();	
			sort(a,a+N);
			for(j=0;j<N;j++)             
				file_o<<a[j]<<" ";	
		}
		else if(i==1){
			for(j=0;j<N;j++)
				a[j]=rand();
			sort(a,a+N,compare);
			for(j=0;j<N;j++)
				file_o<<a[j]<<" ";		
		}
		else if(i==2||i==3||i==4||i==5||i==6||i==7||i==8||i==9){
			for(j=0;j<N;j++)
				file_o<<rand()<<" ";	
		}
		file_o.close();
		cout<<"***************����"<<i+1<<"*****************"<<endl;
		InsertSort(i);//
 		ShellSort(i);//
 		BubbleSort(i);//
		QuickSort(i);//
		SelectSort(i);//
		HeapSort(i);//�� 
		MergeSort(i);//���� 
		RadixSort(i);//�������� 
	}
	system("pause");
	return 0;
}

bool compare(int a, int b){
	return a>b; //���� 
}

void InsertSort(int f){
	int i,j,t;         
	file_i.open(filename[f],ios::in) ;
	for(i=0;i<N;i++){
		file_i>>a[i];
	}
	cout<<"ֱ�Ӳ��뷨:"<<endl; 
	GetLocalTime(& time_begin);
	cout<<"��ʼ:"<<time_begin.wMinute<<"��"<<time_begin.wSecond<<"��"<<time_begin.wMilliseconds<<"����"<<endl;
	for(i=1;i<N;i++){
		if(a[i]<a[i-1]){  //0~i-1 �Ѿ������� ����ֻ��Ҫ��i-1��� �����i1�� �Ͳ���Ҫ�Ƚ�ǰ�� 
			t=a[i];//�ڱ�
			for(j=i;j>0&&t<a[j-1];j--)
				a[j]=a[j-1];
			a[j]=t;	
		}
	}
	GetLocalTime(& time_end);
	cout<<"����:"<<time_end.wMinute<<"��"<<time_end.wSecond<<"��"<<time_end.wMilliseconds<<"����"<<endl;
	if(time_end.wMinute<time_begin.wMinute)
		time_end.wMinute+=60;
	if(time_end.wSecond<time_begin.wSecond){
		time_end.wSecond+=60;
		time_end.wMinute--;
	}
	if(time_end.wMilliseconds<time_begin.wMilliseconds){
		time_end.wMilliseconds+=1000;
		time_end.wSecond--;
	}
	cout<<"��ʱ:"<<time_end.wMinute-time_begin.wMinute<<"��"<<time_end.wSecond-time_begin.wSecond<<"��"<<time_end.wMilliseconds-time_begin.wMilliseconds<<"����"<<endl; 
//	for(i=0;i<N;i++)
	//	cout<<a[i]<<" ";
	cout<<endl;
	file_i.close();
}

void ShellSort(int f){
	int i,j,k,t,dk[3]={5,3,1};   //���      
	file_i.open(filename[f],ios::in) ;
	for(i=0;i<N;i++){
		file_i>>a[i];
	}
	cout<<"ϣ������:"<<endl;
	GetLocalTime(& time_begin); 
	cout<<"��ʼ:"<<time_begin.wMinute<<"��"<<time_begin.wSecond<<"��"<<time_begin.wMilliseconds<<"����"<<endl;
	for(k=0;k<3;k++){
		for(i=dk[k];i<N;i++){
			if(a[i]<a[i-dk[k]]){  
				t=a[i];//�ڱ�
				for(j=i-dk[k];j>0 && t<a[j-dk[k]];j-=dk[k])
						a[j]=a[j-1];
				a[j]=t;	
			}	
		}
	}
	GetLocalTime(& time_end);
	cout<<"����:"<<time_end.wMinute<<"��"<<time_end.wSecond<<"��"<<time_end.wMilliseconds<<"����"<<endl;
	if(time_end.wMinute<time_begin.wMinute)
		time_end.wMinute+=60;
	if(time_end.wSecond<time_begin.wSecond){
		time_end.wSecond+=60;
		time_end.wMinute--;
	}
	if(time_end.wMilliseconds<time_begin.wMilliseconds){
		time_end.wMilliseconds+=1000;
		time_end.wSecond--;
	}
	cout<<"��ʱ:"<<time_end.wMinute-time_begin.wMinute<<"��"<<time_end.wSecond-time_begin.wSecond<<"��"<<time_end.wMilliseconds-time_begin.wMilliseconds<<"����"<<endl; 
//	for(i=0;i<N;i++)
//		cout<<a[i]<<" ";
	cout<<endl;
	file_i.close();
}

void BubbleSort(int f){
	int i,j,t;         
	file_i.open(filename[f],ios::in) ;
	for(i=0;i<N;i++){
		file_i>>a[i];
	}
	cout<<"ð������:"<<endl;
	GetLocalTime(& time_begin); 
	cout<<"��ʼ:"<<time_begin.wMinute<<"��"<<time_begin.wSecond<<"��"<<time_begin.wMilliseconds<<"����"<<endl;
	for(i=0;i<N-1;i++){
		for(j=0;j<N-i-1;j++){
			if(a[j]>a[j+1]){
				t=a[j];
				a[j]=a[j-1];
				a[j-1]=t;
			}
		}
	} 
	GetLocalTime(& time_end);
	cout<<"����:"<<time_end.wMinute<<"��"<<time_end.wSecond<<"��"<<time_end.wMilliseconds<<"����"<<endl;
	if(time_end.wMinute<time_begin.wMinute)
		time_end.wMinute+=60;
	if(time_end.wSecond<time_begin.wSecond){
		time_end.wSecond+=60;
		time_end.wMinute--;
	}
	if(time_end.wMilliseconds<time_begin.wMilliseconds){
		time_end.wMilliseconds+=1000;
		time_end.wSecond--;
	}
	cout<<"��ʱ:"<<time_end.wMinute-time_begin.wMinute<<"��"<<time_end.wSecond-time_begin.wSecond<<"��"<<time_end.wMilliseconds-time_begin.wMilliseconds<<"����"<<endl; 
//	for(i=0;i<N;i++)
//		cout<<a[i]<<" ";
	cout<<endl;
	file_i.close();
}

void QuickSort(int f){
	int i,j,t,pivotkey,low,high,start,end,mid; 
	Stack S;  
	InitStack(S);  
	Push(S,0);//�Ƚ�low 
	Push(S,N-1);   
	file_i.open(filename[f],ios::in) ;
	for(i=0;i<N;i++){
		file_i>>a[i];
	}
	pivotkey=a[0];
	GetLocalTime(& time_begin);
	cout<<"��������:"<<endl; 
	cout<<"��ʼ:"<<time_begin.wMinute<<"��"<<time_begin.wSecond<<"��"<<time_begin.wMilliseconds<<"����"<<endl;
	while(S.top!=S.base){      //ÿ����һ�� �ҵ�һ���м�� low==high  ���������зֳ����� Ȼ���ٶ�ÿ��ʹ�ÿ���  ֪�����������м�λ�õ��� 
		Pop(S,high);
		Pop(S,low);
		start=low; end=high;
		pivotkey=a[low];
		while(low<high){
			while(low<high&&pivotkey<=a[high]){
				high--;
			}
			a[low]=a[high];
			while(low<high&&pivotkey>=a[low]){
				low++;
			}
			a[high]=a[low];
		}
		a[low]=pivotkey;
		mid=low ;
		if(start!=mid-1&&start<(mid-1)){
			Push(S,start);
			Push(S,mid-1);
		}
		if(mid+1!=end&&(mid+1)<end){
			Push(S,mid+1);
			Push(S,end);
		}
	}
	GetLocalTime(& time_end);
	cout<<"����:"<<time_end.wMinute<<"��"<<time_end.wSecond<<"��"<<time_end.wMilliseconds<<"����"<<endl;
	if(time_end.wMinute<time_begin.wMinute)
		time_end.wMinute+=60;
	if(time_end.wSecond<time_begin.wSecond){
		time_end.wSecond+=60;
		time_end.wMinute--;
	}
	if(time_end.wMilliseconds<time_begin.wMilliseconds){
		time_end.wMilliseconds+=1000;
		time_end.wSecond--;
	}
	cout<<"��ʱ:"<<time_end.wMinute-time_begin.wMinute<<"��"<<time_end.wSecond-time_begin.wSecond<<"��"<<time_end.wMilliseconds-time_begin.wMilliseconds<<"����"<<endl; 
//	for(i=0;i<N;i++)
//		cout<<a[i]<<" ";
	cout<<endl;
	file_i.close();
}

void SelectSort(int f){
	int i,j,t;         
	file_i.open(filename[f],ios::in) ;
	for(i=0;i<N;i++){
		file_i>>a[i];
	}
	GetLocalTime(& time_begin);
	cout<<"ѡ������:"<<endl; 
	cout<<"��ʼ:"<<time_begin.wMinute<<"��"<<time_begin.wSecond<<"��"<<time_begin.wMilliseconds<<"����"<<endl;
	for(i=0;i<N-1;i++){
		for(j=i+1;j<N;j++){
			if(a[i]>a[j]){
				t=a[i];
				a[i]=a[j];
				a[j]=t;
			}
		}
	}
	GetLocalTime(& time_end);
	cout<<"����:"<<time_end.wMinute<<"��"<<time_end.wSecond<<"��"<<time_end.wMilliseconds<<"����"<<endl;
	if(time_end.wMinute<time_begin.wMinute)
		time_end.wMinute+=60;
	if(time_end.wSecond<time_begin.wSecond){
		time_end.wSecond+=60;
		time_end.wMinute--;
	}
	if(time_end.wMilliseconds<time_begin.wMilliseconds){
		time_end.wMilliseconds+=1000;
		time_end.wSecond--;
	}
	cout<<"��ʱ:"<<time_end.wMinute-time_begin.wMinute<<"��"<<time_end.wSecond-time_begin.wSecond<<"��"<<time_end.wMilliseconds-time_begin.wMilliseconds<<"����"<<endl; 
//	for(i=0;i<N;i++)
//		cout<<a[i]<<" ";
	cout<<endl;
	file_i.close();
}

void HeapSort(int f){
	int i,j,t;         
	file_i.open(filename[f],ios::in) ;
	for(i=1;i<=N;i++){
		file_i>>a[i];
	}
	GetLocalTime(& time_begin);
	cout<<"������:"<<endl; 
	cout<<"��ʼ:"<<time_begin.wMinute<<"��"<<time_begin.wSecond<<"��"<<time_begin.wMilliseconds<<"����"<<endl;
	for(i=N/2;i>=1;i--){ //////�����󶥶�  ʵ���������� 
    	HeapAdjust(a,N,i);
    }
    for(i=N;i>=2;i--){
        t=a[i];
		a[i]=a[1];
		a[1]=t;
        HeapAdjust(a,i-1,1);// 1 ��Ҫ������λ�� 
    }//����  ����ȫ���� 
	GetLocalTime(& time_end);
	cout<<"����:"<<time_end.wMinute<<"��"<<time_end.wSecond<<"��"<<time_end.wMilliseconds<<"����"<<endl;
	if(time_end.wMinute<time_begin.wMinute)
		time_end.wMinute+=60;
	if(time_end.wSecond<time_begin.wSecond){
		time_end.wSecond+=60;
		time_end.wMinute--;
	}
	if(time_end.wMilliseconds<time_begin.wMilliseconds){
		time_end.wMilliseconds+=1000;
		time_end.wSecond--;
	}
	cout<<"��ʱ:"<<time_end.wMinute-time_begin.wMinute<<"��"<<time_end.wSecond-time_begin.wSecond<<"��"<<time_end.wMilliseconds-time_begin.wMilliseconds<<"����"<<endl; 

//	for(i=0;i<N;i++)
//		cout<<a[i]<<" ";
	cout<<endl;
	file_i.close();
}

void MergeSort(int f){
	int i,j,t,arrwidth=2,n;  
	bool flag=true;       
	file_i.open(filename[f],ios::in) ;
	for(i=0;i<N;i++){
		file_i>>a[i];
	}
	GetLocalTime(& time_begin);
	cout<<"��������:"<<endl; 
	cout<<"��ʼ:"<<time_begin.wMinute<<"��"<<time_begin.wSecond<<"��"<<time_begin.wMilliseconds<<"����"<<endl;
	while(flag){
		if((N/arrwidth)*arrwidth<N)
			n=N/arrwidth+1;//��������������ʱ�� 
		else n=N/arrwidth;
		for(j=0;j<n;j++){
			if(j==0&&N<(j+1)*arrwidth){//�����������һ������ 
				InsertList(a,j*arrwidth,N);
				flag=false;	
			}
			else{//����ĩβ���Ȳ�������� 
				if((j+1)*arrwidth>N)
					InsertList(a,j*arrwidth,N-j*arrwidth);//���������м䲢�������ĩβ���ݲ����ȵ���� 
				else
					InsertList(a,j*arrwidth,arrwidth);//��ĩβ��� 
			}
		}
		arrwidth*=2;
	}	
	GetLocalTime(& time_end);
	cout<<"����:"<<time_end.wMinute<<"��"<<time_end.wSecond<<"��"<<time_end.wMilliseconds<<"����"<<endl;
	if(time_end.wMinute<time_begin.wMinute)
		time_end.wMinute+=60;
	if(time_end.wSecond<time_begin.wSecond){
		time_end.wSecond+=60;
		time_end.wMinute--;
	}
	if(time_end.wMilliseconds<time_begin.wMilliseconds){
		time_end.wMilliseconds+=1000;
		time_end.wSecond--;
	}
	cout<<"��ʱ:"<<time_end.wMinute-time_begin.wMinute<<"��"<<time_end.wSecond-time_begin.wSecond<<"��"<<time_end.wMilliseconds-time_begin.wMilliseconds<<"����"<<endl; 
//	for(i=0;i<N;i++)
//		cout<<a[i]<<" ";
	cout<<endl;
	file_i.close();
}

void RadixSort(int f){
	int i,j,e,k,m,b;
	Sqlist L;
	LinkQueue Q[10];
	InitList(L);
	for(i=0;i<10;i++)
		InitQueue(Q[i]);
       
	file_i.open(filename[f],ios::in) ;
	for(i=0;i<N;i++){
		file_i>>L.elem[i];
	}
	GetLocalTime(& time_begin);
	cout<<"��������:"<<endl; 
	cout<<"��ʼ:"<<time_begin.wMinute<<"��"<<time_begin.wSecond<<"��"<<time_begin.wMilliseconds<<"����"<<endl; 
	for(i=0;i<5;i++){
		for(j=0;j<N;j++){
			m=1*pow(10,i);
			k=L.elem[j]/m;
			k=k%10;
			EnQueue(Q[k],L.elem[j]);
		}//���� 
		j=0;
		for(b=0;b<10;b++){
			while(Q[b].front!=Q[b].rear){
				DeQueue(Q[b],e);
				L.elem[j++]=e;
			}//�ռ� 
		}
	}
	GetLocalTime(& time_end);
	cout<<"����:"<<time_end.wMinute<<"��"<<time_end.wSecond<<"��"<<time_end.wMilliseconds<<"����"<<endl;
	if(time_end.wMinute<time_begin.wMinute)
		time_end.wMinute+=60;
	if(time_end.wSecond<time_begin.wSecond){
		time_end.wSecond+=60;
		time_end.wMinute--;
	}
	if(time_end.wMilliseconds<time_begin.wMilliseconds){
		time_end.wMilliseconds+=1000;
		time_end.wSecond--;
	}
	cout<<"��ʱ:"<<time_end.wMinute-time_begin.wMinute<<"��"<<time_end.wSecond-time_begin.wSecond<<"��"<<time_end.wMilliseconds-time_begin.wMilliseconds<<"����"<<endl; 
//	for(i=0;i<N;i++)
	//	cout<<L.elem[i]<<" ";
	cout<<endl;
	file_i.close();
}

void InitStack(Stack& S){
	S.base=(int *)malloc(STACK_INIT_SIZE*sizeof(int));
	if(!S.base){
		cout<<"fail";
		exit(0);
	}
	S.top=S.base;//Ŀǰջ������
	S.stacksize=STACK_INIT_SIZE; 	
} 

void Push(Stack& S,int e){
	*S.top++=e;//�ȵ��ڣ���++  <=> S.top=e;S.top++; 
}

void Pop(Stack& S,int &e){
	if(S.top==S.base){
		cout<<"��ջ";
		exit(0);
	} 
	e=*--S.top;//��Ϊtop��ָ��ǰջ��Ԫ�ص���һλ�� 
}

void HeapAdjust(int a[],int n,int k){
	//nΪ��Ҫ���������鳤�ȣ�kΪҪ������Ԫ��λ�� 
	int i,j,ta;
	i=k;
    j=2*i;
    ta=a[i]; //t��ְ��������pivotkey ����¼Ҫ������Ԫ�� 
    while(j<=n)
    {
        if(j<n&&a[j]<a[j+1])//ѡ������߻������ұߣ�˭������Ǳ� 
			 j++;  
        if(ta>a[j])
			 break;//���˫�״��ں��ӣ�˵�����������µ����ˣ���ΪLdata[j]�Լ��������������� 
       	a[i]=a[j];//�����ӵ�ֵ��˫�� 
        i=j;//���ӱ��µ�˫�� 
		j=2*i;//��˫�׵����� 
    }
    a[i]=ta;//�������ֵ�ҵ�����λ�� 
}

void InsertList(int a[],int beg_locat,int width){
	int i,j,t;
	for(i=beg_locat+1;i<beg_locat+width;i++){//ֱ�Ӳ������� 
		if(a[i]<a[i-1]){
			t=a[i];//�ڱ�
			for(j=i;j>beg_locat&&t<a[j-1];j--)
				a[j]=a[j-1];
				a[j]=t;	
		}
	}	
}

void InitQueue(LinkQueue& Q){
	Q.front=Q.rear=(QNode*)malloc(sizeof(QNode)); //���ﲻҪд��LinkQueue; 
	if(!Q.front){
		cout<<"fail";
		exit(0);
	}
	Q.front->next=NULL;
	Q.rear->next=NULL;
} 

void EnQueue(LinkQueue& Q,int e){
	QueuePtr p;
	p=(QNode*)malloc(sizeof(QNode));
	if(!p){
		cout<<"fail";
		exit(0); 
	}
	p->elem=e;
	p->next=NULL;
	Q.rear->next=p;
	Q.rear=p;
}

void DeQueue(LinkQueue& Q,int &e){
	if(Q.front==Q.rear){
		cout<<"�ն���";
		exit(0); 
	}
	QueuePtr p=Q.front->next;
	e=p->elem;
	Q.front->next=p->next;
	if(Q.rear==p)
		Q.rear=Q.front;  //�ն��� 
	free(p);	
}

void InitList(Sqlist& L){
	L.elem = (int*)malloc(LIST_INIT_SIZE * sizeof(int));
	if (!L.elem) {
		cout << "fail";
		exit(0);
	}
}

