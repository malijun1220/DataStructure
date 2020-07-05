w/*���ݽṹ��Ŀ�������Ա�A��B��Ԫ��ֵΪ���ͣ��ҵ������򣬱�д����ʵ�����й��ܣ�
		�Բ���˳��ṹ����ʽ�ṹ2�ִ洢�ṹ��Ҫ����A�Ŀռ��Ϲ���һ�������Ա�C��
		��Ԫ��ΪA��BԪ�صĲ������ұ�C�е�Ԫ��ֵ�������򣨻�����ͬ��
		*/
/* ˳��ṹ 	------���ⲻ������C�ռ䣬������A����������ռ䡣   10/19/2019 ������*/
#include<iostream>
using namespace std;
#include<stdlib.h>
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 100 
typedef struct List{
	int *elem;//�������
	int length; 
	int listsize; 
}Sqlist;
void InitList(Sqlist& L){
	L.elem = (int*)malloc(LIST_INIT_SIZE * sizeof(int));
	if (!L.elem) {
		cout << "fail";
		exit(0);
	}
	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
}
void CreateList(Sqlist& L){
	int i;
	cout << "�� 0 ����" << endl;
	for (i = 0; i < L.listsize; i++) {
		cin >> L.elem[i];
		L.length++;
		if (L.elem[i] == 0) {
			L.length--;
			break;
		}
		if (i >= L.listsize - 1) {
			int* newbase;
			int Length = L.length + LISTINCREMENT;//���滻������
			newbase = (int*)realloc(L.elem, Length * sizeof(int));//ԭ���Ļ��������·���ռ䣬L.elem��ԭ�����׵�ַ
			if (!newbase) {
				cout << "space increase fail";
				exit(0);
			}
			L.elem = newbase;//��ԭ���Ļ��������ӣ��׵�ַû�б�
			L.listsize = Length;
			cout << "space increase succeed" << endl;
		}

	}
	cout <<"���볤��: "<<L.length << endl;
}
void Union_A_B(Sqlist& L_A,Sqlist L_B){
	Sqlist p,q;
	int length_C;
	length_C=L_A.length+L_B.length;
	//�ж������������� A�Ŀռ��Ƿ�ȫ������A B�������� 
	if(L_A.listsize<length_C){
		int* newbase;
		newbase = (int*)realloc(L_A.elem, length_C * sizeof(int));//ԭ���Ļ��������·���ռ䣬L.elem��ԭ�����׵�ַ
		if (!newbase) {
			cout << "space increase fail";
			exit(0);
		}
		L_A.elem = newbase;//��ԭ���Ļ��������ӣ��׵�ַû�б�
		L_A.listsize = length_C;
		cout << "space increase succeed" << endl;		
	}
	int i=0,length_A=L_A.length;//��ʾA 
	int j=0;//��ʾB
	bool flag;
	while(j<L_B.length){
		flag=false;
		if(L_A.elem[i]<=L_B.elem[j]){
			while(L_A.elem[i]<=L_B.elem[j]&&i<length_A){
				if(L_A.elem[i]==L_B.elem[j]){
					flag=true;
					break;
				}
				i++;
			}
			if(!flag){
				for(i;i<length_A;length_A--){
				L_A.elem[length_A]=L_A.elem[length_A-1];
				}
				L_A.elem[i]=L_B.elem[j];
			}
		}
		else{
			for(i;i<length_A;length_A--){
				L_A.elem[length_A]=L_A.elem[length_A-1];
			}
			L_A.elem[i]=L_B.elem[j];
		}
		if(flag){
			j++;
			continue;
		}
		length_A=L_A.length;
		length_A++;
		L_A.length=length_A;
		j++;
		
	}	
}
int main(){
	Sqlist L_A;
	Sqlist L_B;
	InitList(L_A);
	cout<<"����A,B�������ݶ����������"<<endl; 
	cout<<"����A:";
	CreateList(L_A);
	InitList(L_B);
	cout<<"����B:";
	CreateList(L_B);
	Union_A_B(L_A,L_B);
	cout<<"�ϲ���:";
	for(int i=0;i<L_A.length;i++){
		cout<<L_A.elem[i]<<" ";
	}
	return 0;
}
