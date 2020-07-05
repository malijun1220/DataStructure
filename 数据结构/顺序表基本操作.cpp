/*���ݽṹ �ڶ���  ���Ա�(1.˳��(��̬))  
2019-9-16 ������*/

#include<iostream>
#include<cstdlib>
using namespace std;
#define LIST_INIT_SIZE 10//��ʼ����ռ�
#define LISTINCREMENT 10//��������
typedef struct ADTList
{
	int* elem;  //����ռ��ַ
	int length;  //��ǰ����
	int listsize; //��ǰ����Ĵ�������
}Sqlist;
// ����һ���յ���������
void InitList(Sqlist& L){
	L.elem = (int*)malloc(LIST_INIT_SIZE * sizeof(int));
	if (!L.elem) {
		cout << "fail";
		exit(0);
	}
	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
}
//�������Ա�L
void DestoryList(Sqlist& L) {
	if (L.elem)
		free(L.elem);//˳����ǲ���Ҫfree�ģ��������Ҫ 
	L.elem = NULL;  //����ĵ���û��
	L.length = 0;
	L.listsize = 0;
	}
//����LΪ�ձ�
void ClearList(Sqlist& L) {
	L.length = 0;
}
//��ΪLΪ�ձ��򷵻�true
bool ListEmpty(Sqlist L) {
	if (L.length == 0)
		return true;
	else
		return false;
}
//��ΪLΪ�ձ��򷵻�true
int ListLength(Sqlist &L) {
	return L.length;
}
//��e����L�е�i������Ԫ�ص�ֵ
void GetElem(Sqlist L, int i, int& e) {
	if (L.length == 0 || i<1 || i>L.length){
		cout<<"��ȡʧ��"<<endl;
		exit(0); 
	}
	e =*(L.elem + i - 1); //L.elem�׵�ַ

}
//����L�е�1����e�����ϵcompare����������Ԫ�ص�λ�����������򷵻�ֵΪ0
void LocatElem(Sqlist L, int e) {
	int i = 1;
	int* p;
	p = L.elem;
	bool compare(int, int);
	while (i <= L.length && !compare(*p++, e)) //ָ��������������������������������
		++i;
	if (i <= L.length)
		cout << i;
	else 
		cout<<"��ƥ��ֵ"<<endl;

}
//��cur_e��L������Ԫ�أ��Ҳ��ǵ�һ��������pre_e��������ǰ�����������ʧ�ܡ�pre_e�޶���
bool PriorElem(Sqlist L, int cur_e, int & pre_e) {
	int i = 2;
	int* p = L.elem + 1;  //�ڶ���Ԫ�صĵ�ַ  
	while (i <= L.length && *p != cur_e)  //ֵ�����
	{
		p++;
		i++;
	}
	if (i > L.length)
		return false;
	else {
		pre_e = *(--p);   //ǰ��ֵ
	}
	return true;
}
//��cur_e��L������Ԫ�أ��Ҳ������һ��������next_e�������ĺ���
bool NextElem(Sqlist L, int cur_e, int& next_e) {
	int i = 1;
	int* p = L.elem;
	while (i <= L.length && *p!= cur_e) {
		i++;
		p++;
	}
	if (i == L.length)
		return false;
	else {
	
		next_e = *++p;
	}
	return  true;
}
//��L�еĵ�i��λ��֮ǰ�����µ�����Ԫ��e��L�ĳ��ȼ� 1
bool ListInsert(Sqlist &L, int i, int e) {
	if (i<1 || i>L.length+1) 
		return false;
	if (L.length >= L.listsize) {
		int* newbase;
		int length = L.listsize + LISTINCREMENT;//���滻������
		newbase = (int*)realloc(L.elem,(length) * sizeof(int)); //ԭ���Ļ��������·���ռ䣬L.elem��ԭ�����׵�ַ
		if (!newbase)
			return false;
		L.elem = newbase;  //��ԭ���Ļ��������ӣ��׵�ַû�б�
		L.listsize += LISTINCREMENT;
	}
	int *q,*p;
	q = L.elem + i - 1;
	for (p = L.elem + L.length - 1; p >= q; --p)//�����Ŀ�ʼŲ 
		* (p + 1) = *p;
	*q = e;
	++L.length;
	return true;
}
//ɾ��L�ĵ�i��Ԫ�أ�����e������ֵ��L�ĳ��ȼ�1
bool ListDelete(Sqlist& L,int i, int& e) {
	if (i<1 || i>L.length)
		return false;
	int* p, * q;
	p = L.elem + i - 1;
	e = *p;
	q = L.elem + L.length - 1;//��ǰ���ȵ����һ��Ԫ�صĵ�ַ   ��*����Ԫ��
	for (++p; p <= q; ++p)
		* (p - 1) = *p;
	--L.length;
	return true;

}
//һ�ζ�L��ÿ������Ԫ�ص���visit������һ��ʧ�ܣ������ʧ��
void ListTraverse(Sqlist L) {
	int* p;
	int i;
	p = L.elem;
	bool visit(int);
	for (i = 1; i <= L.length; i++) {
		if (!visit(*p++))
			break;
	}
	cout << "ok";
}
//��������һ��һ���������ȥ
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
			L.elem = newbase;//��ԭ���Ļ��������ӣ��׵�ַû�б�  ֮ǰ������Ҳû�б� ��Ϊ˳���ռ��������� 
			L.listsize = Length;
			cout << "space increase succeed" << endl;
		}

	}
	cout <<"���볤��: "<<L.length << endl;
}
bool compare(int, int) {
	return true;
}
bool  visit(int) {
	return true;
}
int main()
{
	
}
