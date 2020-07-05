/*Dijkstra�㷨 -------��Դ���·��  2019/12/11  ������*/
#include<iostream>
#include<cstdlib>
using namespace std;
#define INFINITY 999
#define MAX_VERTEX_NUM 50
typedef struct {
	char vexs[MAX_VERTEX_NUM];  //�����/���� ��
	int  arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];   //�ڽӾ��������ڱߵ�����Ȩֵ��������ֵINFINITY��ʾ����
	int vexnum, arcnum;         //ͼ�ĵ�ǰ�������ͻ���
}AMGraph;
void CreateGraph(AMGraph& G) {
	cout << "�ж��ٶ���(v):";
	cin >> G.vexnum;
	cout << "�ж��ٱ�(a):";
	cin >> G.arcnum;
	cout << "���������붥��:";
	int i, j, weight, k;// weightȨ�� 
	for (i = 1; i <= G.vexnum; i++) {
		cin >> G.vexs[i];
	}
	for (i = 1; i <= G.vexnum; i++)
		for (int j = 1; j <= G.vexnum; j++)
			G.arcs[i][j] = INFINITY;
	cout << "�������ڵ�֮���Ȩֵ(i,j,w,i->j):" << endl;
	for (k = 1; k <= G.arcnum; k++) {
		cin >> i >> j >> weight;
		G.arcs[i][j] = weight;//˵��i,jλ�õĶ������ڣ�ȨֵΪw
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
void ShortestPath_DIJ(AMGraph &G){
	bool final[G.vexnum+1],path[G.vexnum+1][G.vexnum+1];//final��������¼V0��Vi���Ƿ��ҵ����·����path�Ǽ�¼���·���м�Ķ��㣬true������·���� 
	int Distance[G.vexnum+1];
	for(int i=1;i<=G.vexnum;i++){
		final[i]=false;//��ʾû���ҵ����·��
		Distance[i]=G.arcs[1][i];//V0�ܾ���һ��·�����·�ߣ���ʱDistanceҲ�Ǵ������̾���  
		for(int j=1;j<=G.vexnum ;j++){
			path[i][j]=false;//����Ŀǰû���ҵ�һ��·�� 
		} 
		if(Distance[i]<INFINITY){
			path[i][i]=true;
			path[i][1]=true;
		} 
	}
	Distance[1]=0;//1������Դ���λ�� 
	final[1]=true;
	int min,v,w,i,j,k;
	
	for( i=1;i<=G.vexnum ;i++){
		min=INFINITY; //��¼��ǰ��֪���ľ���V0����̾����
		for( w=1;w<=G.vexnum ;w++){
			if(!final[w] && Distance[w]<min){
				v=w;
				min=Distance[w];
			}
		} 
		final[v]=true;//�ҵ��˸õ�����·�� 
		for(w=1;w<=G.vexnum ;w++){
			//�ҵ���ǰ���·���Ƿ��������������·�� 
			if(!final[w]&&(min+G.arcs[v][w]<Distance[w])){
				Distance[w]=min+G.arcs[v][w];
				for(k=1;k<=G.vexnum ;k++){
					path[w][k]=path[v][k];  //��ֵ��� 
				} 
				path[w][w]=true;
			}
		}
	}
	bool flag;
	for( i=2;i<=G.vexnum;i++){
		flag=false;
		cout<<"a"<<"��"<<G.vexs[i]<<"�����·���ϵĶ�����: ";
		for( j=1;j<=G.vexnum;j++){
			if(path[i][j]){
				flag=true;
				if(G.arcs[1][j]){
					cout<<G.vexs[j]<<" ";//����Ⱥ�˳��ͬ��Ŀǰû�뵽��ô������Ҫ�Ľ� 
				}
			}
		}	
		if(!flag){
			cout<<"�޷�����";
		}
		
		cout<<endl;
	} 
	
}
int main()
{
	AMGraph G;
	CreateGraph(G);
	int Distance[G.vexnum];
	cout<<"Ĭ��Ϊ��a��ʼ"<<endl; 
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
 
