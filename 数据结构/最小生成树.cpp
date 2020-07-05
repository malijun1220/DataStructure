//����������ͼ  �����Ϊ���� 
//Prim�ʺ����ϵ����  Kruskal��ȫ�Ƕ������� 
#include<iostream>
using namespace std;
#include<cstdlib>
#include<vector>
#include<fstream>
#define infinity 999
typedef struct {
    int begin;  //ǰ��(����)����
    int weight;  //������֮���Ȩֵ
    int end;  //���(����)����
    bool visit;  //�Ƿ��Ѱ�������������
}Closest;
 
typedef struct { //����kruskal 
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
	file>>key;//������ 
	cout<<key<<endl;
	vector<int> key_name(key+1,0);
	for(i=1;i<=key;i++){
		file>>key_name[i];//�������� 
		cout<<key_name[i]<<" ";
	}
	file>>edge;//���� 
	cout<<endl<<edge<<endl;
	vector<vector<int> > Edge;
	Edge.resize(key+1);//����һά
	for(i=0;i<=key;i++)
		Edge[i].resize(key+1);

	for(i=1;i<=key;i++){ //��ʼ�� 
		for(j=1;j<=key;j++){
			if(i!=j)
				Edge[i][j]=infinity;//�ȸ��������
			else
				Edge[i][j]=0; 
		}
	}
	EDGE* C;//////
	C = (EDGE*)malloc(edge * sizeof(EDGE));//��¼��̶���֮����� 
	for(i=0;i<edge;i++){
		file>>a>>b>>w;
		if(file.fail())
			break;
		C[i].x=a;C[i].y=b;C[i].w=w; 
		Edge[a][b]=w;
		Edge[b][a]=w;
		cout<<a<<" "<<b<<" "<< Edge[a][b]<<endl;
	}
	cout<<"��ά�ڽӾ���:"<<endl;
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
	C = (Closest*)malloc((key + 1) * sizeof(Closest));//��¼��̶���֮����� 
	start=key_name[1];//�ӵ�һ�����㿪ʼѰ�� 
	for(i=1;i<=key;i++){//��һ�γ�ʼ 
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
		C[index].visit=true;//ѭ��һ�� ���һ�����·������������ 
		for(j=1;j<=key;j++){
			if(C[j].visit==false && Edge[index][j] < C[j].weight){
					C[j].weight=Edge[index][j];//����֮ǰ�����·�� 
					C[j].begin=index;  //����ǰ������ 
			}
		} 
	}
	for (i = 1; i <=key; i++) {
		if(C[i].weight!=0)
        	cout << C[i].begin <<  " <-> " << C[i].end << " Ȩֵ " << C[i].weight  << endl;
    }
}
void Kruskal(int key,int edge,vector<int> key_name,EDGE* C){
	int i,j,a,b,w,edge_num=0;
	for(i=0;i<edge-1;i++){
		for(j=i+1;j<edge;j++){
			if(C[i].w>C[j].w){
				a=C[i].x;  C[i].x=C[j].x; C[j].x=a; //��Ȩֵ���� 
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
			cout<<C[i].x<<" <-> "<<C[i].y<<" Ȩֵ "<<C[i].w<<endl; 
			edge_num++;
			link[C[i].x]=C[i].y;
			if(edge_num==key-1){
				break;
			}
		}
	}
}
