/*输入稀疏矩阵，建立稀疏矩阵三元组顺序结构，实现转置  10/26/2019 马丽钧*/
#include<iostream>
using namespace std;
#include<cstdlib>
typedef struct LNode{
	int i;//行下标 
	int j;//列下标 
	int e; 
}Triple;
typedef struct LNode_h{
	Triple* data;//指向上一结构体的指针 
	int mu; //行数 
	int nu;//列数 
	int tu;//非零元个数 
}TSMatrix;
void CreateTSMatrix(TSMatrix &M)
{
	int m,n,t;
	cout<<"你想创建行、列、非零元素个数(mu,nu,tu):";
	cin>>m>>n>>t;
	M.data=(Triple*)malloc((t+1)*sizeof(Triple));//有多少非零元素就开多少空间 
	if(!M.data){
		cout<<"fail";
		exit(0);
	}
	M.mu=m;
	M.nu=n;
	M.tu=t;
	cout<<"输入三元组（i,j,e)"<<endl; 
	for(int k=1;k<=M.tu;k++){
		cin>>M.data[k].i>>M.data[k].j>>M.data[k].e;
	}
}
// 按列优先，列进行冒泡排序，然后交换行列数，即可 
void TransposeTSMatrix(TSMatrix M,TSMatrix& T){
	T.data=(Triple*)malloc((M.tu+1)*sizeof(Triple));//要开空间，不然会出错 
	T.mu=M.nu;
	T.nu=M.mu;
	T.tu=M.tu;
	if(M.tu){
		int i,j,e1;
		for(int p=1;p<M.tu;p++){
			for(int q=1;q<=M.tu-p;q++){
				if(M.data[q].j>M.data[q+1].j){
					j=M.data[q].j;
					M.data[q].j=M.data[q+1].j;
					M.data[q+1].j=j;
				
					i=M.data[q].i;
					M.data[q].i=M.data[q+1].i;
					M.data[q+1].i=i;
				
					e1=M.data[q].e;
					M.data[q].e=M.data[q+1].e;
					M.data[q+1].e=e1;	
	
				}
			}
		}
	} 	
	for(int p=1;p<=T.tu;p++){
		T.data[p].i=M.data[p].j;
		T.data[p].j=M.data[p].i;
		T.data[p].e=M.data[p].e;
	}
}
void PrintTSMatrix(TSMatrix T){
	int t;
	t=T.tu;
	for(int k=1;k<=t;k++){
		cout<<T.data[k].i<<" "<<T.data[k].j<<" "<<T.data[k].e<<endl;
	}
}
int main(){
	TSMatrix M,T;
	CreateTSMatrix(M); 
	TransposeTSMatrix(M,T);
	cout<<"转置结果如下:"<<endl;
	PrintTSMatrix(T);
	return 0;
} 
