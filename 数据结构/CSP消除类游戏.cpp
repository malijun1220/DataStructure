/*CSP��Ŀ����������Ϸ  2019/11/22 ������ */
#include<iostream>
using namespace std;
#include<cmath>
#define N 50
#define M 50
int clear_arr[N][M];
int main()
{
	int n,m;
	cout<<"������������(n,m):";
	cin>>n>>m;
	cout<<"��������ÿ����λ����ɫ(1-9):"<<endl;
	int i,j;
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			cin>>clear_arr[i][j]; 
		}
	}
	//�ж������,��Ϊ��ɫ������1-9��ʾ�ģ��ʿ�����������-1��ʾ 
	for(i=0;i<n-2;i++){
		for(j=0;j<m;j++){
			if(clear_arr[i][j]==clear_arr[i+1][j] && clear_arr[i+1][j]==clear_arr[i+2][j]){
				clear_arr[i][j]=-clear_arr[i][j];
				clear_arr[i+1][j]=-clear_arr[i+2][j];
				clear_arr[i+2][j]=-clear_arr[i+2][j];
			}
		}
	}
	//�ж������,��Ϊ��ɫ������1-9��ʾ�ģ��ʿ�����������-1��ʾ 
	for(i=0;i<n;i++){
		for(j=0;j<m-2;j++){
			if(fabs(clear_arr[i][j])==fabs(clear_arr[i][j+1]) && fabs(clear_arr[i][j+1])==fabs(clear_arr[i][j+2])){
				clear_arr[i][j]=-fabs(clear_arr[i][j]);
				clear_arr[i][j+1]=-fabs(clear_arr[i][j+1]);
				clear_arr[i][j+2]=-fabs(clear_arr[i][j+2]);
			}
		}
	}
	//�ж������,��Ϊ��ɫ������1-9��ʾ�ģ��ʿ�����������-1��ʾ 
	cout<<"���������Ϊ:"<<endl;
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			if(clear_arr[i][j]>0)
				cout<<clear_arr[i][j]<<" ";
			else
				cout<<0<<" ";
		}
		cout<<endl; 
	} 
	return 0;
}
