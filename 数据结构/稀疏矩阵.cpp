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
	//�� 1���ڶ���λ�ÿ�ʼ�� 
	for(int k=1;k<=M.tu;k++){
		cin>>M.data[k].i>>M.data[k].j>>M.data[k].e;
	}
}
void TransposeTSMatrix(TSMatrix M,TSMatrix& T){
	T.data=(Triple*)malloc((M.tu+1)*sizeof(Triple));//Ҫ���ռ䣬��Ȼ����� 
	T.mu=M.nu;
	T.nu=M.mu;
	T.tu=M.tu;
	if(T.tu){
		int k=1;
		//M(ije)=T(jie)
		for(int m=1;m<=M.nu;m++){
			for(int p=1;p<=M.tu;p++){
				if(M.data[p].j==m){//��ת�ú��һ�п�ʼѰ����û�и���Ӧ��ŵ�ֵ 
					T.data[k].i=M.data[p].j;
					T.data[k].j=M.data[p].i;
					T.data[k].e=M.data[p].e;
					k++;
				}
			}
		}
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
