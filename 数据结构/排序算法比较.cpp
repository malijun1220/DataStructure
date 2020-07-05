//直接插入排序、希尔排序，冒泡排序、快速排序、选择排序、堆排序，归并排序、基数排序
#include<iostream>
using namespace std;
#include<algorithm>  //sort 
#include<cstdlib>
#include<fstream>
#include<time.h>
#include<windows.h>
#include<math.h> 
#define STACK_INIT_SIZE 50000 //初始分配 
#define LIST_INIT_SIZE 50000
#define N  50000
typedef struct Stack{
	int *top;
	int *base;
	int stacksize;//当前可使用的最大容量 
} Stack;
//基数排序 
typedef struct Sqlist{
	int* elem;
}Sqlist;
typedef struct QNode{
	int elem;
	struct QNode *next;
}QNode,*QueuePtr;
typedef struct{
	QueuePtr front;//队头指针 
	QueuePtr rear;//队尾指针 
}LinkQueue;
char filename[10][20]={{"datasample1.txt"},{"datasample2.txt"},{"datasample3.txt"},
					{"datasample4.txt"},{"datasample5.txt"},{"datasample6.txt"},
					{"datasample7.txt"},{"datasample8.txt"},{"datasample9.txt"},
					{"datasample10.txt"}};
int a[50001];
ifstream file_i;
ofstream file_o;
	
SYSTEMTIME time_begin,time_end;//获取系统时间 

void InsertSort(int i);
void ShellSort(int i);  //分若干子序列分别进行直接插入法 
void BubbleSort(int i);//也叫交换 
void QuickSort(int i);
void SelectSort(int i);
void HeapSort(int i);//堆 
void MergeSort(int i);//并归 
void RadixSort(int i);//基数排序 
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
		srand( (unsigned)time( NULL ) );//初始化随机数  时间做随机种子 
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
		cout<<"***************样本"<<i+1<<"*****************"<<endl;
		InsertSort(i);//
 		ShellSort(i);//
 		BubbleSort(i);//
		QuickSort(i);//
		SelectSort(i);//
		HeapSort(i);//堆 
		MergeSort(i);//并归 
		RadixSort(i);//基数排序 
	}
	system("pause");
	return 0;
}

bool compare(int a, int b){
	return a>b; //逆序 
}

void InsertSort(int f){
	int i,j,t;         
	file_i.open(filename[f],ios::in) ;
	for(i=0;i<N;i++){
		file_i>>a[i];
	}
	cout<<"直接插入法:"<<endl; 
	GetLocalTime(& time_begin);
	cout<<"开始:"<<time_begin.wMinute<<"分"<<time_begin.wSecond<<"秒"<<time_begin.wMilliseconds<<"毫秒"<<endl;
	for(i=1;i<N;i++){
		if(a[i]<a[i-1]){  //0~i-1 已经是有序 所以只需要和i-1相比 如果比i1大 就不需要比较前边 
			t=a[i];//哨兵
			for(j=i;j>0&&t<a[j-1];j--)
				a[j]=a[j-1];
			a[j]=t;	
		}
	}
	GetLocalTime(& time_end);
	cout<<"结束:"<<time_end.wMinute<<"分"<<time_end.wSecond<<"秒"<<time_end.wMilliseconds<<"毫秒"<<endl;
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
	cout<<"用时:"<<time_end.wMinute-time_begin.wMinute<<"分"<<time_end.wSecond-time_begin.wSecond<<"秒"<<time_end.wMilliseconds-time_begin.wMilliseconds<<"毫秒"<<endl; 
//	for(i=0;i<N;i++)
	//	cout<<a[i]<<" ";
	cout<<endl;
	file_i.close();
}

void ShellSort(int f){
	int i,j,k,t,dk[3]={5,3,1};   //间隔      
	file_i.open(filename[f],ios::in) ;
	for(i=0;i<N;i++){
		file_i>>a[i];
	}
	cout<<"希尔排序法:"<<endl;
	GetLocalTime(& time_begin); 
	cout<<"开始:"<<time_begin.wMinute<<"分"<<time_begin.wSecond<<"秒"<<time_begin.wMilliseconds<<"毫秒"<<endl;
	for(k=0;k<3;k++){
		for(i=dk[k];i<N;i++){
			if(a[i]<a[i-dk[k]]){  
				t=a[i];//哨兵
				for(j=i-dk[k];j>0 && t<a[j-dk[k]];j-=dk[k])
						a[j]=a[j-1];
				a[j]=t;	
			}	
		}
	}
	GetLocalTime(& time_end);
	cout<<"结束:"<<time_end.wMinute<<"分"<<time_end.wSecond<<"秒"<<time_end.wMilliseconds<<"毫秒"<<endl;
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
	cout<<"用时:"<<time_end.wMinute-time_begin.wMinute<<"分"<<time_end.wSecond-time_begin.wSecond<<"秒"<<time_end.wMilliseconds-time_begin.wMilliseconds<<"毫秒"<<endl; 
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
	cout<<"冒泡排序法:"<<endl;
	GetLocalTime(& time_begin); 
	cout<<"开始:"<<time_begin.wMinute<<"分"<<time_begin.wSecond<<"秒"<<time_begin.wMilliseconds<<"毫秒"<<endl;
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
	cout<<"结束:"<<time_end.wMinute<<"分"<<time_end.wSecond<<"秒"<<time_end.wMilliseconds<<"毫秒"<<endl;
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
	cout<<"用时:"<<time_end.wMinute-time_begin.wMinute<<"分"<<time_end.wSecond-time_begin.wSecond<<"秒"<<time_end.wMilliseconds-time_begin.wMilliseconds<<"毫秒"<<endl; 
//	for(i=0;i<N;i++)
//		cout<<a[i]<<" ";
	cout<<endl;
	file_i.close();
}

void QuickSort(int f){
	int i,j,t,pivotkey,low,high,start,end,mid; 
	Stack S;  
	InitStack(S);  
	Push(S,0);//先进low 
	Push(S,N-1);   
	file_i.open(filename[f],ios::in) ;
	for(i=0;i<N;i++){
		file_i>>a[i];
	}
	pivotkey=a[0];
	GetLocalTime(& time_begin);
	cout<<"快速排序法:"<<endl; 
	cout<<"开始:"<<time_begin.wMinute<<"分"<<time_begin.wSecond<<"秒"<<time_begin.wMilliseconds<<"毫秒"<<endl;
	while(S.top!=S.base){      //每快速一次 找到一个中间点 low==high  将整个序列分成两半 然后再对每半使用快速  知道不能在又中间位置的数 
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
	cout<<"结束:"<<time_end.wMinute<<"分"<<time_end.wSecond<<"秒"<<time_end.wMilliseconds<<"毫秒"<<endl;
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
	cout<<"用时:"<<time_end.wMinute-time_begin.wMinute<<"分"<<time_end.wSecond-time_begin.wSecond<<"秒"<<time_end.wMilliseconds-time_begin.wMilliseconds<<"毫秒"<<endl; 
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
	cout<<"选择排序法:"<<endl; 
	cout<<"开始:"<<time_begin.wMinute<<"分"<<time_begin.wSecond<<"秒"<<time_begin.wMilliseconds<<"毫秒"<<endl;
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
	cout<<"结束:"<<time_end.wMinute<<"分"<<time_end.wSecond<<"秒"<<time_end.wMilliseconds<<"毫秒"<<endl;
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
	cout<<"用时:"<<time_end.wMinute-time_begin.wMinute<<"分"<<time_end.wSecond-time_begin.wSecond<<"秒"<<time_end.wMilliseconds-time_begin.wMilliseconds<<"毫秒"<<endl; 
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
	cout<<"堆排序法:"<<endl; 
	cout<<"开始:"<<time_begin.wMinute<<"分"<<time_begin.wSecond<<"秒"<<time_begin.wMilliseconds<<"毫秒"<<endl;
	for(i=N/2;i>=1;i--){ //////建立大顶堆  实现正序排列 
    	HeapAdjust(a,N,i);
    }
    for(i=N;i>=2;i--){
        t=a[i];
		a[i]=a[1];
		a[1]=t;
        HeapAdjust(a,i-1,1);// 1 是要调整的位置 
    }//至此  结束全过程 
	GetLocalTime(& time_end);
	cout<<"结束:"<<time_end.wMinute<<"分"<<time_end.wSecond<<"秒"<<time_end.wMilliseconds<<"毫秒"<<endl;
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
	cout<<"用时:"<<time_end.wMinute-time_begin.wMinute<<"分"<<time_end.wSecond-time_begin.wSecond<<"秒"<<time_end.wMilliseconds-time_begin.wMilliseconds<<"毫秒"<<endl; 

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
	cout<<"并归排序法:"<<endl; 
	cout<<"开始:"<<time_begin.wMinute<<"分"<<time_begin.wSecond<<"秒"<<time_begin.wMilliseconds<<"毫秒"<<endl;
	while(flag){
		if((N/arrwidth)*arrwidth<N)
			n=N/arrwidth+1;//总数据有奇数个时候 
		else n=N/arrwidth;
		for(j=0;j<n;j++){
			if(j==0&&N<(j+1)*arrwidth){//用来处理最后一个并归 
				InsertList(a,j*arrwidth,N);
				flag=false;	
			}
			else{//处理末尾长度不足的数据 
				if((j+1)*arrwidth>N)
					InsertList(a,j*arrwidth,N-j*arrwidth);//用来处理中间并归过程中末尾数据不足宽度的情况 
				else
					InsertList(a,j*arrwidth,arrwidth);//非末尾情况 
			}
		}
		arrwidth*=2;
	}	
	GetLocalTime(& time_end);
	cout<<"结束:"<<time_end.wMinute<<"分"<<time_end.wSecond<<"秒"<<time_end.wMilliseconds<<"毫秒"<<endl;
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
	cout<<"用时:"<<time_end.wMinute-time_begin.wMinute<<"分"<<time_end.wSecond-time_begin.wSecond<<"秒"<<time_end.wMilliseconds-time_begin.wMilliseconds<<"毫秒"<<endl; 
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
	cout<<"基数排序法:"<<endl; 
	cout<<"开始:"<<time_begin.wMinute<<"分"<<time_begin.wSecond<<"秒"<<time_begin.wMilliseconds<<"毫秒"<<endl; 
	for(i=0;i<5;i++){
		for(j=0;j<N;j++){
			m=1*pow(10,i);
			k=L.elem[j]/m;
			k=k%10;
			EnQueue(Q[k],L.elem[j]);
		}//分配 
		j=0;
		for(b=0;b<10;b++){
			while(Q[b].front!=Q[b].rear){
				DeQueue(Q[b],e);
				L.elem[j++]=e;
			}//收集 
		}
	}
	GetLocalTime(& time_end);
	cout<<"结束:"<<time_end.wMinute<<"分"<<time_end.wSecond<<"秒"<<time_end.wMilliseconds<<"毫秒"<<endl;
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
	cout<<"用时:"<<time_end.wMinute-time_begin.wMinute<<"分"<<time_end.wSecond-time_begin.wSecond<<"秒"<<time_end.wMilliseconds-time_begin.wMilliseconds<<"毫秒"<<endl; 
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
	S.top=S.base;//目前栈无数据
	S.stacksize=STACK_INIT_SIZE; 	
} 

void Push(Stack& S,int e){
	*S.top++=e;//先等于，再++  <=> S.top=e;S.top++; 
}

void Pop(Stack& S,int &e){
	if(S.top==S.base){
		cout<<"空栈";
		exit(0);
	} 
	e=*--S.top;//因为top总指向当前栈顶元素的下一位置 
}

void HeapAdjust(int a[],int n,int k){
	//n为需要操作的数组长度，k为要调整的元素位置 
	int i,j,ta;
	i=k;
    j=2*i;
    ta=a[i]; //t的职能类似于pivotkey ，记录要调整的元素 
    while(j<=n)
    {
        if(j<n&&a[j]<a[j+1])//选择走左边还是走右边，谁大就走那边 
			 j++;  
        if(ta>a[j])
			 break;//如果双亲大于孩子，说明不用再往下调整了，因为Ldata[j]以及是子树中最大的了 
       	a[i]=a[j];//否则孩子的值给双亲 
        i=j;//孩子变新的双亲 
		j=2*i;//新双亲的左孩子 
    }
    a[i]=ta;//需调整的值找到最终位置 
}

void InsertList(int a[],int beg_locat,int width){
	int i,j,t;
	for(i=beg_locat+1;i<beg_locat+width;i++){//直接插入排序 
		if(a[i]<a[i-1]){
			t=a[i];//哨兵
			for(j=i;j>beg_locat&&t<a[j-1];j--)
				a[j]=a[j-1];
				a[j]=t;	
		}
	}	
}

void InitQueue(LinkQueue& Q){
	Q.front=Q.rear=(QNode*)malloc(sizeof(QNode)); //这里不要写成LinkQueue; 
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
		cout<<"空队列";
		exit(0); 
	}
	QueuePtr p=Q.front->next;
	e=p->elem;
	Q.front->next=p->next;
	if(Q.rear==p)
		Q.rear=Q.front;  //空队列 
	free(p);	
}

void InitList(Sqlist& L){
	L.elem = (int*)malloc(LIST_INIT_SIZE * sizeof(int));
	if (!L.elem) {
		cout << "fail";
		exit(0);
	}
}

