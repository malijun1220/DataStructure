/*CSP  下井字棋  2019/12/11   马丽钧*/
//ALICE先下  所以下的次数都为奇数，BOB为偶数 
#include<iostream>
using namespace std;
#define N 20
int main()
{
	int chess[N][4][4];
	cout<<"输入井字棋组数(T):";
	int T;
	cin>>T;
	cout<<"数字0代格子为空，1代表X，为Alice所下;2代表 0 ，为Bob所下，每盘Alice先下"<<endl; 
	cout<<"请输入每一组棋:"<<endl;
	int i,j,k;
	for(i=1;i<=T;i++){
		for(j=1;j<=3;j++){
			for(k=1,k<=3;k++){
				cin>>chess[i][j][k];
			}
		}
	}
	int m,n,count=0;
	int score[T+1];
	for(i=1;i<=T;i++){
		for(j=1;j<=3;j++){
			//横排 
			if(chess[i][j][1]==chess[i][j][2]&&chess[i][j][2]==chess[i][j][3]&&(chess[i][j][3]==1||chess[i][j][3]==2)){
				for(m=1;m<=3;m++){
					for(n=1;n<=3;n++){
						if(chess[i][m][n]==0){
							count++;
						}
					}
				} 
				if(chess[i][j][3]==1){
					score[i]=count+1;
				}
				else{
					score[i]=-(count+1);
				}
			}
			//横排 
			else if(chess[i][1][j]==chess[i][2][j]&&chess[i][2][j]==chess[i][3][j]&&(chess[i][3][j]==1||chess[i][3][j]==2)){
				for(m=1;m<=3;m++){
					for(n=1;n<=3;n++){
						if(chess[i][m][n]==0){
							count++;
						}
					}
				} 
				if(chess[i][3][j]==1){
					score[i]=count+1;
				}
				else{
					score[i]=-(count+1);
				}
			}
			else if(	)
		}
	}	
	return 0;
}
