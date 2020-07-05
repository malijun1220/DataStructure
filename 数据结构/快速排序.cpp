/*ʵ�ֿ��������㷨    2019/12/12 ������*/
//���������Ƕ�ð�������һ�ָĽ�
//ͨ��һ�����򽫴��ż�¼�ָ�ɶ����������֣�����һ���ּ�¼�Ĺؼ��־�����һ���ּ�¼�Ĺؼ���С 

//һ�������� pivotkey������������������ź������м�λ�ã���ʼĬ��pivotkeyΪ��Ԫ�� 

//��ջ�ķ�����ÿ�ν�ջ��������ûջ�������ݣ��ֱ���pivotkeyǰ�沿��ͷ��β��λ�ã���һ����ͷ��β��λ�� 

#include<iostream>
using namespace std;
#include<cstdlib>
#define LIST_INIT_SIZE 100//��ʼ����ռ�
#define LISTINCREMENT 50//��������
#define STACK_INIT_SIZE 100 //��ʼ���� 
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
void GetTop(Stack S,int& e){
	if(S.top==S.base){
		cout<<"ջΪ��";
		exit(0);
	}
	else
		e=*(S.top-1);
}
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
void Pop(Stack& S,int &e){
	if(S.top==S.base){
		cout<<"��ջ";
		exit(0);
	} 
	e=*--S.top;//��Ϊtop��ָ��ǰջ��Ԫ�ص���һλ�� 
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
	cout << "�� 0 ����:";
	for (i = 0; i < L.listsize; i++) {
		cin >> L.data[i];
		L.length++;
		if (L.data[i] == 0) {
			L.length--;
			break;
		}
		if (i >= L.listsize - 1) {
			int* newbase;
			int Length = L.length + LISTINCREMENT;//���滻������
			newbase = (int*)realloc(L.data, Length * sizeof(int));//ԭ���Ļ��������·���ռ䣬L.elem��ԭ�����׵�ַ
			if (!newbase) {
				cout << "space increase fail";
				exit(0);
			}
			L.data = newbase;//��ԭ���Ļ��������ӣ��׵�ַû�б�
			L.listsize = Length;
			cout << "space increase succeed" << endl;
		}

	}
	cout <<"���볤��: "<<L.length << endl;
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
	Push(S,low);//�Ƚ�low 
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
		cout<<"һ�˿��Ž��: "; 
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
	cout<<endl<<"���������: ";
	PrintList(L);
	return 0;
}
//�������ݣ� 
 //49 38 65 97 76 13 27 49 0
 //12 6 8 4 56 78 6 5 32 1 5 6 48 0
