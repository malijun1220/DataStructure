/*寻找马鞍点——矩阵中某一点在其行最小，其列最大  二维数组实现 Am*n  11/2/2019 马丽钧*/
#include<iostream>
using namespace std;
#include<cstdlib>
int main()
{
	cout<<"你想创建的数组行列数(m*n):";
	int row,col;
	cin>>row>>col;
	cout<<"开始输入:"<<endl; 
	int arr[row][col];
	for(int i=0;i<row;i++){
		for(int j=0;j<col;j++){
			cin>>arr[i][j];
		}
	}
	int m;
	bool flag;
	for(int i=0;i<row;i++){
		flag=true;
		m=0;
		//确定行中最小值 
		for(int j=0;j<col;j++){
			if(arr[i][m]>arr[i][j])
			{
				m=j;
			}
		}
		//确定该值是否是列的最大值 
		for(int k=0;k<col;k++){
			if(arr[i][m]<arr[k][m]){
				flag=false;
				break;
			}
		}
		if(flag){
			cout<<"第"<<i+1<<"行第"<<m+1<<"列为马鞍点:"<<arr[i][m]<<endl; 
		}
	}
	return 0;
} 
