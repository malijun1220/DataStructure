//本题用无向图  顶点皆为数字 
//Prim适合求边系数的  Kruskal从全是顶点入手 
#include<iostream>
using namespace std;
#include<cstdlib>
#include<vector>
#include<fstream>
#define infinity 999
typedef struct {
    int begin;  //前驱(出发)城市
    int weight;  //两城市之间的权值
    int end;  //后继(到达)城市
    bool visit;  //是否已包含在生成树内
}Closest;
 
typedef struct { //用于kruskal 
	int x,y,w;
}EDGE;
void Prim(int key,vector<int> key_name,vector<vector<int> > Edge);
void Kruskal(int key,int edge,vector<int> key_name,EDGE* C);
int main()
{
	int key,i,j,edge,a,b,w;
	fstream file;
	file.open("mintree.txt",ios::in);
	if(file.fail())
		exit(0);
	file>>key;//顶点数 
	cout<<key<<endl;
	vector<int> key_name(key+1,0);
	for(i=1;i<=key;i++){
		file>>key_name[i];//顶点名称 
		cout<<key_name[i]<<" ";
	}
	file>>edge;//边数 
	cout<<endl<<edge<<endl;
	vector<vector<int> > Edge;
	Edge.resize(key+1);//开第一维
	for(i=0;i<=key;i++)
		Edge[i].resize(key+1);

	for(i=1;i<=key;i++){ //初始化 
		for(j=1;j<=key;j++){
			if(i!=j)
				Edge[i][j]=infinity;//先赋上无穷大
			else
				Edge[i][j]=0; 
		}
	}
	EDGE* C;//////
	C = (EDGE*)malloc(edge * sizeof(EDGE));//记录最短顶点之间距离 
	for(i=0;i<edge;i++){
		file>>a>>b>>w;
		if(file.fail())
			break;
		C[i].x=a;C[i].y=b;C[i].w=w; 
		Edge[a][b]=w;
		Edge[b][a]=w;
		cout<<a<<" "<<b<<" "<< Edge[a][b]<<endl;
	}
	cout<<"二维邻接矩阵:"<<endl;
	for(i=1;i<=key;i++){
		for(j=1;j<=key;j++){
			if(Edge[i][j]==infinity)
				cout<<"#"<<" ";
			else 
				cout<<Edge[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<"Prim:"<<endl; 
	Prim(key,key_name,Edge);
	cout<<"Kruskal:"<<endl;
	Kruskal(key,edge,key_name,C);	
	return 0; 
} 

void Prim(int key,vector<int> key_name,vector<vector<int> > Edge){
	int start,i,j,k,weight,index,minweight;
	Closest* C;
	C = (Closest*)malloc((key + 1) * sizeof(Closest));//记录最短顶点之间距离 
	start=key_name[1];//从第一个顶点开始寻找 
	for(i=1;i<=key;i++){//第一次初始 
		C[i].begin=start;
		C[i].end=i;
		if(i==start)
			C[i].visit=true;
		else
			C[i].visit=false;
		if(Edge[start][i]!=infinity)
			C[i].weight=Edge[start][i];
		else
			C[i].weight=infinity; 
	}
	for(i=1;i<key;i++){
		minweight=infinity;
		for(j=1;j<=key;j++){
			if(C[j].visit==false && C[j].weight < minweight){
				minweight=C[j].weight;
				index=j;
			} 
		}
		C[index].visit=true;//循环一次 添加一个最短路径到生成树中 
		for(j=1;j<=key;j++){
			if(C[j].visit==false && Edge[index][j] < C[j].weight){
					C[j].weight=Edge[index][j];//更新之前的最短路径 
					C[j].begin=index;  //更新前区城市 
			}
		} 
	}
	for (i = 1; i <=key; i++) {
		if(C[i].weight!=0)
        	cout << C[i].begin <<  " <-> " << C[i].end << " 权值 " << C[i].weight  << endl;
    }
}
void Kruskal(int key,int edge,vector<int> key_name,EDGE* C){
	int i,j,a,b,w,edge_num=0;
	for(i=0;i<edge-1;i++){
		for(j=i+1;j<edge;j++){
			if(C[i].w>C[j].w){
				a=C[i].x;  C[i].x=C[j].x; C[j].x=a; //按权值排序 
				b=C[i].y;  C[i].y=C[j].y; C[j].y=b;
				w=C[i].w;  C[i].w=C[j].w; C[j].w=w;
			}
		}
	}
	cout<<"x  y     w"<<endl;
	for(i=0;i<edge;i++){
		cout<<C[i].x<<"  "<<C[i].y<<"     "<<C[i].w<<endl;
	}
	cout<<endl;
	int link[key+1];
	for(i=0;i<=key;i++)
		link[i]=0;
	for(i=0;i<edge;i++){//////////// 
		a=C[i].x;
		while(link[a]!=0){
			a=link[a];
		}
		b=C[i].y;
		while(link[b]!=0){
			b=link[b];
		}
		if(a!=b){
			cout<<C[i].x<<" <-> "<<C[i].y<<" 权值 "<<C[i].w<<endl; 
			edge_num++;
			link[C[i].x]=C[i].y;
			if(edge_num==key-1){
				break;
			}
		}
	}
}
