/*���ݽṹ  ������ ˳��ṹ 10/12/2019 ������  
����������n��m��m<n��������n��������һȦ���ӵ�1���˿�ʼѭ������������m���˳��У�Ȼ���ٴ���һ���˿�ʼ������
����m�����ֳ��У�����ظ���ֱ�����е��˶�����Ϊֹ��
Ҫ������ʽ�ṹ��˳��ṹʵ�֣������е��Ⱥ�˳�����ÿ���˵���Ϣ*/


#include<iostream>
#include<stdlib.h>
using namespace std;
#define LIST_INIT_SIZE 100//��ʼ����ռ�
#define LISTINCREMENT 10//��������
typedef struct List_Sq
{
	int* elem;  //����ռ��ַ
	int length;  //��ǰ����
	int listsize; //��ǰ����Ĵ�������
}Sqlist;
void InitList(Sqlist& L) {
	L.elem = (int*)malloc(LIST_INIT_SIZE * sizeof(int));
	if (!L.elem) {
		cout << "fail";
		exit(0);
	}
	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
}
void CreatList(Sqlist& L)
{
	int i;
	cout << "�� 0 ����" << endl;
	for (i = 0; i < L.listsize; i++) {
		cin >> L.elem[i];
		L.length++;
		if (L.elem[i] == 00) {
			L.length--;
			break;
		}
		if (i >= L.listsize - 1) {
			int* newbase;
			int Length = L.length + LISTINCREMENT;
			newbase = (int*)realloc(L.elem, Length * sizeof(int));
			if (!newbase) {
				cout << "space increase fail";
				exit(0);
			}
			L.elem = newbase;
			L.listsize = Length;
			cout << "space increase succeed" << endl;
		}

	}
	cout << "��һ�������� "<<L.length <<" ��"<< endl;
}
void Listout(Sqlist &L,int n) {
	int Listlength, order = 0, true_order=0,i = 0;
	Listlength = L.length;
	while (true) {
		order++;
		if (order % Listlength == 0) //˳�������һ�����֣���ʱorder&Listlength==0����ʱ��-1û��ָ�� 
			if (L.elem[Listlength - 1] == 0)
				continue;
		if (L.elem[order % Listlength-1]==0)
			continue;
		true_order++;
		if (true_order % n == 0) {
			i++;
			if (order % Listlength == 0) {
				cout << "��" << i << "�� " << L.elem[Listlength-1 ] << "����" << endl; //˳������һ������ 
				L.elem[ Listlength - 1] = 0;
			}
			else
			{
				cout << "��" << i << "�� " << L.elem[order % Listlength - 1] << "����" << endl;
				L.elem[order % Listlength - 1] = 0;
			}
		}
		if (i == Listlength)
			break;
	}

}
int main()
{
	Sqlist L;
	int n;
	InitList(L);
	CreatList(L);
	cout << "����������ֵı�������:";
	cin >> n;
	Listout(L,n);
	return 0;
}
