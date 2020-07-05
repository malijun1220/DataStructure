/*CSP题目：消除类游戏  2019/11/22 马丽钧 */
#include<iostream>
using namespace std;
#include<cmath>
#define N 50
#define M 50
int clear_arr[N][M];
int main()
{
	int n,m;
	cout<<"请输入行列数(n,m):";
	cin>>n>>m;
	cout<<"按行输入每个单位的颜色(1-9):"<<endl;
	int i,j;
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			cin>>clear_arr[i][j]; 
		}
	}
	//判断列情况,因为颜色都是用1-9表示的，故可以消除的用-1表示 
	for(i=0;i<n-2;i++){
		for(j=0;j<m;j++){
			if(clear_arr[i][j]==clear_arr[i+1][j] && clear_arr[i+1][j]==clear_arr[i+2][j]){
				clear_arr[i][j]=-clear_arr[i][j];
				clear_arr[i+1][j]=-clear_arr[i+2][j];
				clear_arr[i+2][j]=-clear_arr[i+2][j];
			}
		}
	}
	//判断行情况,因为颜色都是用1-9表示的，故可以消除的用-1表示 
	for(i=0;i<n;i++){
		for(j=0;j<m-2;j++){
			if(fabs(clear_arr[i][j])==fabs(clear_arr[i][j+1]) && fabs(clear_arr[i][j+1])==fabs(clear_arr[i][j+2])){
				clear_arr[i][j]=-fabs(clear_arr[i][j]);
				clear_arr[i][j+1]=-fabs(clear_arr[i][j+1]);
				clear_arr[i][j+2]=-fabs(clear_arr[i][j+2]);
			}
		}
	}
	//判断行情况,因为颜色都是用1-9表示的，故可以消除的用-1表示 
	cout<<"消除后输出为:"<<endl;
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
