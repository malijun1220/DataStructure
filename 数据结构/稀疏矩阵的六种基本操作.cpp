/*稀疏矩阵的六种基本操作 10/30/2019 马丽钧*/
#include<iostream>
using namespace std;
#include<cstdlib>
typedef struct{
	int row;//行
	int col;//列
	int data; 
}Triple;

typedef struct{
	Triple *elem;//指向Triple结构体的指针
	int rownum;//行数 
	int colnum;//列数 
	int elemnum;//非零元素个数 
}TSMatrix;
//创建 
void CreateTSMatrix(TSMatrix &M)
{
	M.elem=(Triple*)malloc(M.elemnum*sizeof(Triple));//有多少非零元素就开多少空间 
	if(!M.elem){
		cout<<"fail";
		exit(0);
	}
	cout<<"输入三元组（i,j,e)"<<endl; 
	for(int i=1;i<=M.elemnum;i++){
		cin>>M.elem[i].row>>M.elem[i].col>>M.elem[i].data;
	}
}
//输出 (需修改)
void PrintTSMatrix(TSMatrix M){
	int index=1; 
	for(int row=1;row<=M.rownum;row++){
		for(int col=1;col<=M.colnum;col++){
			//检查当前位置是否为非零元素 
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
//复制M->T 
void CopyTSMatrix(TSMatrix M,TSMatrix &T){
	
} 
//矩阵相加 Q=M+N 
void AddTSMatrix(TSMatrix M,TSMatrix N,TSMatrix& Q){
	
}
//矩阵相减 Q=M-N 
void SubTSMatrix(TSMatrix M,TSMatrix N,TSMatrix& Q){
	
}
//矩阵相乘 Q=M*N 
void MultTSMatrix(TSMatrix M,TSMatrix N,TSMatrix& Q){
	
}
//矩阵转置 ——方法一  按照T中三元组次序排列， 即按照M列来转置 
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
//矩阵转置 ——方法二  按照M中三元组的次序转置，先确定M每一列的非零元素 
void TransposeTSMatrix_2(TSMatrix M,TSMatrix& T){
	T.rownum=M.colnum;
	T.colunm=M.rownum;
	T.elemnum=M.elemnum;
	if(T.elemnum){
		int num[M.colnum+1];//存放M中每一列的元素个数 
		for(int col=1;col<=M.colnum;col++){
			num[col]=0;//初始每一列为0 
		}
		for(int t=1;t<=M.elemunm;t++){
			num[M.data[t].j]++;//求每一列的元素个数   j的最大值即为M.colunm 列 J出现几次则该列有几个元素，转到T就是行有几个元素 
		} 
		int copt[M.colnum+1];//第copt[i]列第一个元素在T.data中的位置 (按行存放) 
		copt[1]=1;//第一行第一个元素的位置为T.data中的第一个三元组 
		for(int col=2;col<=M.colnum;col++){
			copt[col]=copt[col-1]+num[col-1];//本行首元素位置+本行元素个数=下一行元素位置 
		}
		int col,p;
		for(int p=1;p<=M.elemnum;p++){
			col=M.data[p].j;  //elemnum即为T.data中有几个三元组 
			q=copt[col];//当前元素转置后(T)的下标  即q为M的列，T的行 
			T.elem[q].i=M.elem[p].j;
			T.elem[q].j=M.elem[p].i;
			T.elem[q].data=M.elem[p].data;
			copt[col]++;//更新指示位置 
		}
	}	
}
//矩阵转置 ——方法三 按列优先，列进行冒泡排序，然后交换行列数，即可 
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
	cout<<"输入稀疏矩阵的行数，列数，非0元素个数:";
	cin>>M.rownum>>M.colnum>>M.elemnum;
	CreateTSMatrix(M);
} 
