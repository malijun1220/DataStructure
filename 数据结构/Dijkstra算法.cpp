/*Dijkstra算法 -------单源最短路径  2019/12/11  马丽钧*/
#include<iostream>
#include<cstdlib>
using namespace std;
#define INFINITY 999
#define MAX_VERTEX_NUM 50
typedef struct {
	char vexs[MAX_VERTEX_NUM];  //顶点表/向量 数
	int  arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];   //邻接矩阵，有相邻边的输入权值，其他赋值INFINITY表示无穷
	int vexnum, arcnum;         //图的当前顶点数和弧数
}AMGraph;
void CreateGraph(AMGraph& G) {
	cout << "有多少顶点(v):";
	cin >> G.vexnum;
	cout << "有多少边(a):";
	cin >> G.arcnum;
	cout << "按次序输入顶点:";
	int i, j, weight, k;// weight权重 
	for (i = 1; i <= G.vexnum; i++) {
		cin >> G.vexs[i];
	}
	for (i = 1; i <= G.vexnum; i++)
		for (int j = 1; j <= G.vexnum; j++)
			G.arcs[i][j] = INFINITY;
	cout << "输入相邻点之间的权值(i,j,w,i->j):" << endl;
	for (k = 1; k <= G.arcnum; k++) {
		cin >> i >> j >> weight;
		G.arcs[i][j] = weight;//说明i,j位置的顶点相邻，权值为w
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
void ShortestPath_DIJ(AMGraph &G){
	bool final[G.vexnum+1],path[G.vexnum+1][G.vexnum+1];//final是用来记录V0到Vi点是否找到最短路径，path是记录最短路径中间的顶点，true代表在路径上 
	int Distance[G.vexnum+1];
	for(int i=1;i<=G.vexnum;i++){
		final[i]=false;//表示没有找到最短路径
		Distance[i]=G.arcs[1][i];//V0能经过一条路到达的路线，此时Distance也是储存的最短距离  
		for(int j=1;j<=G.vexnum ;j++){
			path[i][j]=false;//代表目前没有找到一条路径 
		} 
		if(Distance[i]<INFINITY){
			path[i][i]=true;
			path[i][1]=true;
		} 
	}
	Distance[1]=0;//1代表求源点的位置 
	final[1]=true;
	int min,v,w,i,j,k;
	
	for( i=1;i<=G.vexnum ;i++){
		min=INFINITY; //记录当前所知道的距离V0点最短距离的
		for( w=1;w<=G.vexnum ;w++){
			if(!final[w] && Distance[w]<min){
				v=w;
				min=Distance[w];
			}
		} 
		final[v]=true;//找到了该点的最短路径 
		for(w=1;w<=G.vexnum ;w++){
			//找到当前最短路径是否有连接其他最短路径 
			if(!final[w]&&(min+G.arcs[v][w]<Distance[w])){
				Distance[w]=min+G.arcs[v][w];
				for(k=1;k<=G.vexnum ;k++){
					path[w][k]=path[v][k];  //赋值相等 
				} 
				path[w][w]=true;
			}
		}
	}
	bool flag;
	for( i=2;i<=G.vexnum;i++){
		flag=false;
		cout<<"a"<<"到"<<G.vexs[i]<<"的最短路径上的顶点有: ";
		for( j=1;j<=G.vexnum;j++){
			if(path[i][j]){
				flag=true;
				if(G.arcs[1][j]){
					cout<<G.vexs[j]<<" ";//输出先后顺序不同，目前没想到怎么做，需要改进 
				}
			}
		}	
		if(!flag){
			cout<<"无法到达";
		}
		
		cout<<endl;
	} 
	
}
int main()
{
	AMGraph G;
	CreateGraph(G);
	int Distance[G.vexnum];
	cout<<"默认为从a开始"<<endl; 
	ShortestPath_DIJ(G);
	return 0;
}
/*1 2 10
1 5 100
1 4 30
6 2 5
2 3 50
4 3 20
4 5 60
3 5 10*/
 
