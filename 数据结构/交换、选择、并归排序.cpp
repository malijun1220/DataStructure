/*ʵ�ֽ���(ð��)��ѡ�񡢹鲢�ȼ������㷨  2019/12/12 ������*/
//д��������************************ 
#include<iostream>
using namespace std;
#include<cstdlib>
#include<cmath>
#define LIST_INIT_SIZE 100//��ʼ����ռ�
#define LISTINCREMENT 50//��������
typedef struct Sqlist{
	int *data;
	int length;  //��ǰ����
	int listsize;
}Sqlist;
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
void BubbleSort(Sqlist& L){
	if(L.length<2){
		exit(0);
	}
	cout<<"��������:";
	int i,j,t;	
	for(i=0;i<L.length-1 ;i++){
		for(j=0;j<L.length-i-1;j++){
			if(L.data[j]>L.data[j+1]){
				t=L.data[j];
				L.data[j]=L.data[j+1];
				L.data[j+1]=t;	
			}
		}
	}
	
}
void SelectionSort(Sqlist& L){
	if(L.length<2){
		exit(0);
	}
	cout<<"ѡ������:";
	int i,j,t;
	for(i=0;i<L.length-1;i++){
		for(j=i+1;j<L.length;j++){
			if(L.data[i]>L.data[j]){
				t=L.data[i];
				L.data[i]=L.data[j];
				L.data[j]=t;
			}
		}
	}
}
void PrintList(Sqlist L){
	int i;
	for(i=0;i<L.length;i++){
		cout<<L.data[i]<<" ";
	}
}
void InsertList(Sqlist& L,int beg_locat,int width){
	int i,j,t;
	for(i=beg_locat;i<beg_locat+width-1;i++){//ѡ������ 
		for(j=i+1;j<beg_locat+width;j++){
			if(L.data[i]>L.data[j]){
				t=L.data[i];
				L.data[i]=L.data[j];
				L.data[j]=t;
			}
		}
	}	
}
void MergingSort(Sqlist& L){
	if(L.length<2)
		exit(0);
	cout<<"���������������:"<<endl;
	int i,j;
	int arrwidth=2,n;//��һ�˲���Ϊ��������һ�� 49 38 65 97 76 13 27
	bool flag=true;
	while(flag){
		if((L.length/arrwidth)*arrwidth<L.length)
			n=L.length/arrwidth+1;//��������������ʱ�� 
		else n=L.length/arrwidth;
		for(j=0;j<n;j++){
			if(j==0&&L.length<(j+1)*arrwidth){//�����������һ������ 
				InsertList(L,j*arrwidth,L.length);
				flag=false;	
			}
			else{//����ĩβ���Ȳ�������� 
				if((j+1)*arrwidth>L.length)
					InsertList(L,j*arrwidth,L.length-j*arrwidth);//���������м䲢�������ĩβ���ݲ����ȵ���� 
				else
					InsertList(L,j*arrwidth,arrwidth);//��ĩβ��� 
			}
		}
		PrintList(L);
		cout<<endl;
		arrwidth*=2;
	}	
}
int main()
{
	Sqlist L;
	InitList(L);
	CreateList(L);
//	BubbleSort(L);
//	SelectionSort(L);
	MergingSort(L);
//	PrintList(L);
	return 0;//49 38 65 97 76 13 2749 38 65 97 76 13 27
}
//��������  49 38 65 97 76 13 27 
