/*����N��Ȩֵ��1-100������������������������  -----2019/11/28 ������*/
//���� n Ƭ��Ҷһ���� 2*n-1 �����----�������wλ�ô�1��ʼ----0λ�ÿճ�
//���ṹΪ  |lchild----parent----weight----rchild|
//#pragma once
//#pragma warning(disable: 4996)

/*  ���ʾHuffmanCode��һ��char**���͵Ĵ����ʡ�
    char*�������Ϊָ��һ���ַ�����һ���ֵ�ָ�롣
    char**�������Ϊ�ַ�������             */

#include<iostream>
using namespace std;
#include<cstdlib>
#include<cstring> 
#define MAX 99999999;//��ʾ���޴� 
typedef struct Huffman {
	unsigned int weight;  //Ȩֵ 
	unsigned int parent, lchild, rchild;
}HTNode, * HuffmanTree;//��̬�����������
typedef char** HuffmanCode; //��̬��������洢����������� ----����ָ��

int Min(HuffmanTree& t, int n)
{
	int i, flag;
	int f = MAX;
	for (i = 1; i <= n;i++)
	{
		if (t[i].weight<f&&t[i].parent==0)
		{
			f = t[i].weight, flag = i;
 
		}
 
	}
	t[flag].parent = 1;
	return flag;
}
void Select(HuffmanTree& HT,int n,int& s1,int &s2){
	int t;
	s1=Min(HT,n);
	s2=Min(HT,n);
	if(HT[s1].weight>HT[s2].weight){
		t=s1;
		s1=s2;
		s2=t;
	}
} 
void HuffmanCoding(HuffmanTree& HT, HuffmanCode& HC, int* w, int n) { //n:�ַ��� w������ַ���Ȩֵ HC������������ HT���������� 
	if (n == 1)
		return ;
	//������������--------------------------------
	int m;//���������ܵĽ�����
	m = 2 * n - 1;
	HT = (HTNode*)malloc((m+1) * sizeof(HTNode));
	HuffmanTree p;//pָ��HT-----�ӵ�һ��λ�ÿ�ʼ
	p=HT+1;
	int i;
	for (p, i = 1; i <= n; i++, p++,w++) {
		p->weight = *w;
		p->lchild = 0;
		p->parent = 0;
		p->rchild = 0;
	}//Ҷ�ӽ�㸳ֵ,Ŀǰÿ�����Ƕ����� 
	for (i; i <= m; i++, p++) {  //m-n=n-1  ��Ҷ�ӽ���� ������������ϲ�����½ڵ� 
		p->parent = 0;
	}//��Ҷ�ӽ���ʼ��   i����ǰ��ѭ�������� 
	int j, s1,s2;//s1 s2Ϊparent���������ӽ�㣬minΪȨֵ 
 	for (i = n+1 ; i <= m; i++) {
		Select( HT,i-1,s1,s2);
		HT[s1].parent =HT[s2].parent = i; //---�´β����پ�ѡ��СҶ�� 
		HT[i].lchild = s1;
		HT[i].rchild = s2;   //������Һ���ָ����ǽ������
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}//�����շ�����---------�ڷ�Ҷ����ѡȡ

	//�����----------------------
	HC = (HuffmanCode)malloc((n+1) * sizeof(char*));//����n���ַ������ͷָ��ָ������   ��ά 
	char* cd;//һά�ַ������� 
	cd = (char*)malloc(n * sizeof(char));//��Ϊ��n����㣬��Ľ�����Ҳ�� n λ���� 
	cd[n - 1] = '\0'; //��������� 
	int start; //���������λ�� 
	
	//��Ҷ�ӵ�������ÿ���ַ��ĺշ����� 
	for ( i = 1; i <= n; i++) { //ѭ��һ�� ���һ���ַ����������� 
		start = n - 1;
		for (int c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent) {  //f=0˵������������ 
			if (HT[f].lchild == c) {
				cd[--start] = '0';//�����ַ�Ϊ0 
			}//������Ӷ�Ӧ�� 
			else
				cd[--start] = '1'; 
		}//f�����  f==0�� �Լ��������� ������� 
		HC[i] = (char*)malloc((n-start)* sizeof(char));//Ϊ��i���ַ��������ռ� 
		strcpy(HC[i], &cd[start]); //���HC[i]�ռ��С��cd��һ��������cd�ص���λ�ûḴ�ƣ���������  HC[i]��HT[i]��Ӧ 
	}
	free(cd);
}
int main()
{ 
	HuffmanTree HT;
	HuffmanCode HC; //�ַ������� 
	int* w, n;//w������̬������Ȩֵ
	cout << "�ж�����Ҷ(n):";
	cin >> n;
	w = (int*)malloc(n * sizeof(int));
	int i;
	for ( i = 0; i <n; i++) {
		w[i]=i+1;
	}//����Ȩֵ 
	HuffmanCoding(HT, HC, w, n);//��������������������� 
	for ( i = 1; i <= n; i++) {
		cout <<"ȨֵΪ "<< HT[i].weight << " �Ĺ�����������:" << HC[i] << endl;
	}
	for(i = 1;i <= n; i++){
		free(HC[i]);
	}
	free(HC);
	return 0;
}
