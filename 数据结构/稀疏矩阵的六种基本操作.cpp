/*ϡ���������ֻ������� 10/30/2019 ������*/
#include<iostream>
using namespace std;
#include<cstdlib>
typedef struct{
	int row;//��
	int col;//��
	int data; 
}Triple;

typedef struct{
	Triple *elem;//ָ��Triple�ṹ���ָ��
	int rownum;//���� 
	int colnum;//���� 
	int elemnum;//����Ԫ�ظ��� 
}TSMatrix;
//���� 
void CreateTSMatrix(TSMatrix &M)
{
	M.elem=(Triple*)malloc(M.elemnum*sizeof(Triple));//�ж��ٷ���Ԫ�ؾͿ����ٿռ� 
	if(!M.elem){
		cout<<"fail";
		exit(0);
	}
	cout<<"������Ԫ�飨i,j,e)"<<endl; 
	for(int i=1;i<=M.elemnum;i++){
		cin>>M.elem[i].row>>M.elem[i].col>>M.elem[i].data;
	}
}
//��� (���޸�)
void PrintTSMatrix(TSMatrix M){
	int index=1; 
	for(int row=1;row<=M.rownum;row++){
		for(int col=1;col<=M.colnum;col++){
			//��鵱ǰλ���Ƿ�Ϊ����Ԫ�� 
			if(check(M,index,row,col)){
				cout<<"  "<<M.elem[row].col; 
			}
			else{
				cout<<"  "<<0;
			}
		}
		cout<<endl;
	}
}
//����M->T 
void CopyTSMatrix(TSMatrix M,TSMatrix &T){
	
} 
//������� Q=M+N 
void AddTSMatrix(TSMatrix M,TSMatrix N,TSMatrix& Q){
	
}
//������� Q=M-N 
void SubTSMatrix(TSMatrix M,TSMatrix N,TSMatrix& Q){
	
}
//������� Q=M*N 
void MultTSMatrix(TSMatrix M,TSMatrix N,TSMatrix& Q){
	
}
//����ת�� ��������һ  ����T����Ԫ��������У� ������M����ת�� 
void TransposeTSMatrix_1(TSMatrix M,TSMatrix& T){
	T.rownum=M.colnum;
	T.colunm=M.rownum;
	T.elemnum=M.elemnum;
	if(T.elemnum){
		int i=1;
		//M(ije)=T(jie)
		for(int col=1;col<=M.colnum;col++){
			for(int p=1;p<=M.elemnum;p++){
				if(M.elem[p].col==col){
					T.elem[i].row=M.elem[p].col;
					T.elem[i].col=M.elem[p].row;
					T.elem[i].data=M.elem[p].data;
					i++;
				}
			}
		}
	}
}
//����ת�� ����������  ����M����Ԫ��Ĵ���ת�ã���ȷ��Mÿһ�еķ���Ԫ�� 
void TransposeTSMatrix_2(TSMatrix M,TSMatrix& T){
	T.rownum=M.colnum;
	T.colunm=M.rownum;
	T.elemnum=M.elemnum;
	if(T.elemnum){
		int num[M.colnum+1];//���M��ÿһ�е�Ԫ�ظ��� 
		for(int col=1;col<=M.colnum;col++){
			num[col]=0;//��ʼÿһ��Ϊ0 
		}
		for(int t=1;t<=M.elemunm;t++){
			num[M.data[t].j]++;//��ÿһ�е�Ԫ�ظ���   j�����ֵ��ΪM.colunm �� J���ּ���������м���Ԫ�أ�ת��T�������м���Ԫ�� 
		} 
		int copt[M.colnum+1];//��copt[i]�е�һ��Ԫ����T.data�е�λ�� (���д��) 
		copt[1]=1;//��һ�е�һ��Ԫ�ص�λ��ΪT.data�еĵ�һ����Ԫ�� 
		for(int col=2;col<=M.colnum;col++){
			copt[col]=copt[col-1]+num[col-1];//������Ԫ��λ��+����Ԫ�ظ���=��һ��Ԫ��λ�� 
		}
		int col,p;
		for(int p=1;p<=M.elemnum;p++){
			col=M.data[p].j;  //elemnum��ΪT.data���м�����Ԫ�� 
			q=copt[col];//��ǰԪ��ת�ú�(T)���±�  ��qΪM���У�T���� 
			T.elem[q].i=M.elem[p].j;
			T.elem[q].j=M.elem[p].i;
			T.elem[q].data=M.elem[p].data;
			copt[col]++;//����ָʾλ�� 
		}
	}	
}
//����ת�� ���������� �������ȣ��н���ð������Ȼ�󽻻������������� 
void TransposeTSMatrix_3(TSMatrix M,TSMatrix& T){
	if(M.elemnum){
		int i,j,e;
		for(int i=1;i<M.elemnum;i++){
			for(int j=1;j<=M.elemnum-i;j++){
				if(M.elem[j].col>M.elem[j+1].col){
					i=M.elem[j].col;
					M.elem[j].col=M.elem[j+1].col;
					M.elem[j+1].col=i;
					j=M.elem[j].row;
					M.elem[j].row=M.elem[j+1].row;
					M.elem[j+1].row=j;
					e=M.elem[j].data;
					M.elem[j].data=M.elem[j+1].data;
					M.elem[j].data=e;			
				}
			}
		}
		int mu;
		mu=M.rownum;
		M.rownum=M.colnum;
		M.colnum=mu;
	} 	
}
int main()
{
	TSMatrix M;
	cout<<"����ϡ��������������������0Ԫ�ظ���:";
	cin>>M.rownum>>M.colnum>>M.elemnum;
	CreateTSMatrix(M);
} 
