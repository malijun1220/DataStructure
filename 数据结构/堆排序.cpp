/*ʵ�ֶ������㷨 2019/12/13 ������*/

//��һά���鿴����һ�ö��������ִ󶥶Ѻ�С���ѣ�������˳�򼴶�-----Ӧ��ȫ������-----------��α�������� -----

//i= 1,2,3..n/2(������n/2�ĶԴ�����,fabs(n/2))
//�󶥶ѣ�k[i]>=k[2i]  ��k[i]>=k[2i+1]     1<=i<=n/2
//С���ѣ�k[i]<=k[2i]  ��k[i]<=k[2i+1]     1<=i<=n/2 
//����һ�����̣�ÿ���ҵ�������С��ȡ��������γ�һ���������� 
//�ӵ׿�ʼ����ÿһ��������һ���� 
//��һ��Ԫ�ص�λ��Ϊ 1  ������ 0  
//�����һ������Ҷ�Ľ�㿪ʼ 


//�������ǽ����󶥶ѣ�ʵ������ 
#include<iostream>
using namespace std;
#include<cstdlib> 
#define LIST_INIT_SIZE 100//��ʼ����ռ�
#define LISTINCREMENT 50//��������
typedef struct Sqlist{
	int* data;
	int length;
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
	for (i = 1; i <= L.listsize; i++) {
		cin >> L.data[i];
		L.length++;
		if (L.data[i] == 0) {
			L.length--;
			break;
		}
		if (i >= L.listsize) {
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
void PrintList(Sqlist L){
	int i;
	for(i=1;i<=L.length;i++){
		cout<<L.data[i]<<" ";
	}
}

void HeapAdjust(Sqlist& L,int n,int k){
	//nΪ��Ҫ���������鳤�ȣ�kΪҪ������Ԫ��λ�� 
	int i,j,ta;
	i=k;
    j=2*i;
    ta=L.data[i]; //t��ְ��������pivotkey ����¼Ҫ������Ԫ�� 
    while(j<=n)
    {
        if(j<n&&L.data[j]<L.data[j+1])//ѡ������߻������ұߣ�˭������Ǳ� 
			 j++;  
        if(ta>L.data[j])
			 break;//���˫�״��ں��ӣ�˵�����������µ����ˣ���ΪLdata[j]�Լ��������������� 
        L.data[i]=L.data[j];//�����ӵ�ֵ��˫�� 
        i=j;//���ӱ��µ�˫�� 
		j=2*i;//��˫�׵����� 
    }
    L.data[i]=ta;//�������ֵ�ҵ�����λ�� 
}
void HeapSort(Sqlist& L){
	int i,t;
	cout<<"��ʼ���ѹ���:"<<endl; 
	//��һ��for�����ڽ�һ���������������һ���ѣ������һ����֦Ҷ��˫�׿�ʼ����������ȷ��ÿһ����㶼�Ƕ� 
    for(i=L.length/2;i>=1;i--){
    	HeapAdjust(L,L.length,i);
    	PrintList(L);
    	cout<<endl;
    }//���ˣ���ʼ�ѽ��ɣ����Ԫ���ڶѶ�
	
	//�ڶ���for��������� ���Ѷ����Ԫ�������һ��λ�õ�Ԫ�ضԻ���
	//���һ��λ�þͳ��˴�Ԫ���ˣ���ʱ�൱���Ѿ�ȡ�������λ��n��ǰŲ����Ϊn-1
	 
	//����λ�ý������ı��˶ѣ�����Ҫ�Ӹ��������ɸѡ���� 
    cout<<"ȡ���Լ��ٵ�������:"<<endl;
    for(i=L.length;i>=2;i--)
    {
        t=L.data[i];
		L.data[i]=L.data[1];
		L.data[1]=t;
        HeapAdjust(L,i-1,1);// 1 ��Ҫ������λ�� 
        PrintList(L);
        cout<<endl;
    }//����  ����ȫ���� 
}
int main()
{
	Sqlist L;
	InitList(L);
	cout<<"����һ����������:";
	CreateList(L);
	HeapSort(L); 
	cout<<"������Ϊ: "<<endl; 
	PrintList(L);
	return 0;
}
//49 38 65 97 76 13 27 49 0
//12 36 24 85 47 30 53 91 80 101 012 36 24 85 47 30 53 91 80 101 0
