/*Ѱ�����㡪��������ĳһ����������С���������  ��ά����ʵ�� Am*n  11/2/2019 ������*/
#include<iostream>
using namespace std;
#include<cstdlib>
int main()
{
	cout<<"���봴��������������(m*n):";
	int row,col;
	cin>>row>>col;
	cout<<"��ʼ����:"<<endl; 
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
		//ȷ��������Сֵ 
		for(int j=0;j<col;j++){
			if(arr[i][m]>arr[i][j])
			{
				m=j;
			}
		}
		//ȷ����ֵ�Ƿ����е����ֵ 
		for(int k=0;k<col;k++){
			if(arr[i][m]<arr[k][m]){
				flag=false;
				break;
			}
		}
		if(flag){
			cout<<"��"<<i+1<<"�е�"<<m+1<<"��Ϊ����:"<<arr[i][m]<<endl; 
		}
	}
	return 0;
} 
