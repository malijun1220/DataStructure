/*����ϡ����󣬽���ϡ�������Ԫ��˳��ṹ��ʵ��ת��  10/26/2019 ������*/
#include<iostream>
using namespace std;
#include<cstdlib>
typedef struct LNode{
	int i;//���±� 
	int j;//���±� 
	int e; 
}Triple;
typedef struct LNode_h{
	Triple* data;//ָ����һ�ṹ���ָ�� 
	int mu; //���� 
	int nu;//���� 
	int tu;//����Ԫ���� 
}TSMatrix;
void CreateTSMatrix(TSMatrix &M)
{
	int m,n,t;
	cout<<"���봴���С��С�����Ԫ�ظ���(mu,nu,tu):";
	cin>>m>>n>>t;
	M.data=(Triple*)malloc((t+1)*sizeof(Triple));//�ж��ٷ���Ԫ�ؾͿ����ٿռ� 
	if(!M.data){
		cout<<"fail";
		exit(0);
	}
	M.mu=m;
	M.nu=n;
	M.tu=t;
	cout<<"������Ԫ�飨i,j,e)"<<endl; 
	for(int k=1;k<=M.tu;k++){
		cin>>M.data[k].i>>M.data[k].j>>M.data[k].e;
	}
}
// �������ȣ��н���ð������Ȼ�󽻻������������� 
void TransposeTSMatrix(TSMatrix M,TSMatrix& T){
	T.data=(Triple*)malloc((M.tu+1)*sizeof(Triple));//Ҫ���ռ䣬��Ȼ����� 
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
	cout<<"ת�ý������:"<<endl;
	PrintTSMatrix(T);
	return 0;
} 
