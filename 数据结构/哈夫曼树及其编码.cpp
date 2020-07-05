/*输入N个权值（1-100正整数），建立哈夫曼树。  -----2019/11/28 马丽钧*/
//根据 n 片子叶一共有 2*n-1 个结点----储存结点的w位置从1开始----0位置空出
//树结构为  |lchild----parent----weight----rchild|
//#pragma once
//#pragma warning(disable: 4996)

/*  这表示HuffmanCode是一个char**类型的代名词。
    char*可以理解为指向一个字符串第一个字的指针。
    char**可以理解为字符串数组             */

#include<iostream>
using namespace std;
#include<cstdlib>
#include<cstring> 
#define MAX 99999999;//表示无限大 
typedef struct Huffman {
	unsigned int weight;  //权值 
	unsigned int parent, lchild, rchild;
}HTNode, * HuffmanTree;//动态分配哈夫曼树
typedef char** HuffmanCode; //动态分配数组存储哈夫曼编码表 ----二重指针

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
void HuffmanCoding(HuffmanTree& HT, HuffmanCode& HC, int* w, int n) { //n:字符数 w：存放字符的权值 HC：哈夫曼编码 HT：哈夫曼树 
	if (n == 1)
		return ;
	//建立哈夫曼树--------------------------------
	int m;//哈夫曼数总的结点个数
	m = 2 * n - 1;
	HT = (HTNode*)malloc((m+1) * sizeof(HTNode));
	HuffmanTree p;//p指向HT-----从第一个位置开始
	p=HT+1;
	int i;
	for (p, i = 1; i <= n; i++, p++,w++) {
		p->weight = *w;
		p->lchild = 0;
		p->parent = 0;
		p->rchild = 0;
	}//叶子结点赋值,目前每个都是独立的 
	for (i; i <= m; i++, p++) {  //m-n=n-1  飞叶子结点数 ——用来代表合并后的新节点 
		p->parent = 0;
	}//非叶子结点初始化   i继续前面循环的数字 
	int j, s1,s2;//s1 s2为parent的两个孩子结点，min为权值 
 	for (i = n+1 ; i <= m; i++) {
		Select( HT,i-1,s1,s2);
		HT[s1].parent =HT[s2].parent = i; //---下次不会再竞选最小叶子 
		HT[i].lchild = s1;
		HT[i].rchild = s2;   //这里的右孩子指向的是结点的序号
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}//创建赫夫曼树---------在非叶子中选取

	//求编码----------------------
	HC = (HuffmanCode)malloc((n+1) * sizeof(char*));//分配n个字符编码的头指针指向向量   二维 
	char* cd;//一维字符串数组 
	cd = (char*)malloc(n * sizeof(char));//因为有n个结点，最长的结点编码也就 n 位长度 
	cd[n - 1] = '\0'; //编码结束符 
	int start; //编码结束符位置 
	
	//从叶子到根逆求每个字符的赫夫曼树 
	for ( i = 1; i <= n; i++) { //循环一次 求得一个字符的完整编码 
		start = n - 1;
		for (int c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent) {  //f=0说明遍历完树了 
			if (HT[f].lchild == c) {
				cd[--start] = '0';//左孩子字符为0 
			}//如果左孩子对应上 
			else
				cd[--start] = '1'; 
		}//f是序号  f==0即 以及到达根结点 编码结束 
		HC[i] = (char*)malloc((n-start)* sizeof(char));//为第i个字符编码分配空间 
		strcpy(HC[i], &cd[start]); //如果HC[i]空间大小和cd不一样，则与cd重叠的位置会复制，其他不变  HC[i]与HT[i]对应 
	}
	free(cd);
}
int main()
{ 
	HuffmanTree HT;
	HuffmanCode HC; //字符串数组 
	int* w, n;//w用来动态储存结点权值
	cout << "有多少子叶(n):";
	cin >> n;
	w = (int*)malloc(n * sizeof(int));
	int i;
	for ( i = 0; i <n; i++) {
		w[i]=i+1;
	}//输入权值 
	HuffmanCoding(HT, HC, w, n);//创建哈夫曼树并且求编码 
	for ( i = 1; i <= n; i++) {
		cout <<"权值为 "<< HT[i].weight << " 的哈夫曼编码是:" << HC[i] << endl;
	}
	for(i = 1;i <= n; i++){
		free(HC[i]);
	}
	free(HC);
	return 0;
}
