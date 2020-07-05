	/*编程实现书P156  ADT Graph 基本操作13个，用邻接矩阵存储结构实现 注意n个顶点就是n*n二位数组  2019/11/23 马丽钧*/
//---------------------深度用栈-------------广度用层次
//此程序写的是---------有向网---------------所有位置都从1开始，0位置放置不计
//--------------------顶点为本程序用 int型表示-------------
//#pragma once
//#pragma warning(disable:4996)
#include<iostream>
using namespace std;
#include<cstdlib>
#define STACK_INIT_SIZE 100 //初始分配 
#define STACKINCREMENT 20 //增量 
#define INFINITY 999 //表示边权值无穷，即不相邻的边
#define MAX_VERTEX_NUM 50 //顶点信息，即顶点最大个数
#include<windows.h>
typedef int VertexType; //VertexType 代表char 表示顶点数据类型为字符型
//typedef enum{DG,DN,UDG,UDN} GraohKind;  //图的种类{有向图，有向网，无向图，无相网}
//typedef int AdjMatrix;//假设边的权值为整型
typedef struct {
	VertexType vexs[MAX_VERTEX_NUM];  //顶点表/向量 数
	VertexType  arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];   //邻接矩阵，有相邻边的输入权值，其他赋值INFINITY表示无穷
	int vexnum, arcnum;         //图的当前顶点数和弧数
}AMGraph;
//链式队列 
typedef struct QNode {
	VertexType elem;
	struct QNode* next;
}QNode, * QueuePtr;
typedef struct {
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;
//顺序栈
typedef struct Stack {
	VertexType* top;
	VertexType* base;
	int stacksize;
}Stack;
/*-------------------------------------------------栈*/
void InitStack(Stack& S) {
	S.base = (VertexType*)malloc(STACK_INIT_SIZE * sizeof(VertexType));
	if (!S.base)
		exit(0);
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
}
//插入t为栈顶元素
void Push(Stack& S, VertexType t) {
	if (S.top - S.base > S.stacksize) {
		int length = STACK_INIT_SIZE + STACKINCREMENT;
		S.base = (VertexType*)realloc(S.base, length * sizeof(VertexType));
		if (!S.base)
			exit(0);
		S.top = S.base + S.stacksize;//设置栈顶 
		S.stacksize += STACKINCREMENT;
	}
	*S.top++ = t;
}
//栈顶元素出栈，并用t返回 
void Pop(Stack& S, VertexType& t) {
	if (S.top == S.base)
		exit(0);
	t = *--S.top;//因为top总指向当前栈顶元素的下一位置 
}
//返回栈顶元素 
void GetTop(Stack S, VertexType& t) {
	if (S.top == S.base) {
		exit(0);
	}
	else
		t = *(S.top - 1);
}
/*-------------------------------------------------队列*/
void InitQueue(LinkQueue& Q) {
	Q.front = (QNode*)malloc(sizeof(QNode));
	if (!Q.front)
		exit(0);
	Q.front->next = NULL;
	Q.rear = Q.front;
}
void EnQueue(LinkQueue& Q, VertexType T) {
	QueuePtr P;
	P = (QNode*)malloc(sizeof(QNode));
	if (!P) {
		exit(0);
	}
	P->elem = T;
	P->next = NULL;
	Q.rear->next = P;
	Q.rear = P;
}
void DeQueue(LinkQueue& Q, VertexType& t) {
	if (Q.front == Q.rear)
		exit(0);
	QueuePtr P;
	P = Q.front->next;
	t = P->elem;
	Q.front->next = P->next;
	if (Q.rear == P) {
		Q.rear = Q.front;//指向空		
	}
	free(P);
}
/*-------------------------------------------------*/
void CreateGraph(AMGraph& G) {
	cout << "有多少顶点(v):";
	cin >> G.vexnum;
	cout << "有多少边(a):";
	cin >> G.arcnum;
	cout << "按次序输入顶点:";
	int i, j, weight, k;//w表示权值 weight
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
void DestoryGraph(AMGraph& G) {
	if (!G.vexnum)
		exit(0);
	G.arcnum = 0;
	G.vexnum = 0;
}
int  LocateVex(AMGraph G, VertexType u) {
	if (!G.vexnum)
		exit(0);
	for (int i = 1; i <= G.vexnum; i++) {
		if (G.vexs[i] == u)
			return i;//相当于返回坐标  (i,i)
	}
	return -1;//表示没有该顶点
}
//返回顶点v的值  什么值？？？？？？？？总度数？？可能是该点相关的指针信息
int GetVex(AMGraph G, VertexType v) {
	if (!G.vexnum)
		exit(0);
	int i;
	for (i = 1; i <= G.vexnum; i++) {
		if (G.vexs[i] == v)
			break;
	}
	int degree = 0;
	for (int j = 1; j <= G.vexnum; j++) {
		if (G.arcs[i][j] != INFINITY) {
			degree++;//出度
		}
	}
	for (int k = 1; k <= G.vexnum; k++) {
		if (G.arcs[k][i] != INFINITY) {
			degree++;//入度
		}
	}
	return degree;//总度数
}
//顶点改名
void PutVex(AMGraph& G, VertexType v, VertexType value) {
	if (!G.vexnum)
		exit(0);
	for (int i = 1; i <= G.vexnum; i++) {
		if (G.vexs[i] == v) {
			G.vexs[i] = value;
			break;
		}
	}
}
//返回第一个邻接顶点，网里面应该是返回权值最小的邻接顶点(有向图返回的是出度边的相邻点)
char FirstAdjVex(AMGraph G, VertexType v) {
	if (!G.vexnum)
		exit(0);
	int i, j, z;
	int w = 0;
	for (i = 1; i <= G.vexnum; i++) {
		if (G.vexs[i] == v)
			break;
	}//确定弧尾顶点位置
	for (j = 1; j <= G.vexnum; j++) {
		if (G.arcs[i][j] != INFINITY) {
			if (w < G.arcs[i][j]) {
				w = G.arcs[i][j];
				z = j;
			}
		}
	}//确定弧头顶点位置
	if (w)
		return G.vexs[z];//如果有出度，优先返回出度中权值最小的边
	/*else {
		for (int k = 0; k < G.vexnum; k++) {
			if (G.arcs[k][i] != INFINITY) {
				if (w < G.arcs[k][i]) {
					w = G.arcs[k][i];
					z = k;
				}
			}
		}
	}
	if (w)
		return G.vexs[z];//若无出度，则返回入度中权值最小的*/
	else
		return 0;//无相邻点
}
//v->w,返回w的下一个(出度)相邻点，如无返回空。
char NextAdjVex(AMGraph G, VertexType v, VertexType w) {
	if (!G.vexnum)
		exit(0);
	int i;
	for (i = 1; i <= G.vexnum; i++) {
		if (G.vexs[i] == w)
			break;
	}
	for (int j = 1; j <= G.vexnum; j++) {
		if (G.arcs[i][j] != INFINITY) {
			return G.arcs[i][j];
		}
	}
	return  0;//无下一个顶点
}
void InsertVex(AMGraph& G, VertexType v) {
	if (!G.vexnum)
		exit(0);
	for (int i = 1; i <= G.vexnum; i++) {
		if (G.vexs[i] == v) {
			G.arcs[i][i] = 0;
			break; //添加v，即v有一个圈，自己到自己，权值为0；
		}
	}
}
//删除顶点v以及相关的弧
void DeleteVex(AMGraph& G, VertexType v) {
	if (!G.vexnum)
		exit(0);
	int i;
	for (i = 1; i <= G.vexnum; i++) {
		if (G.vexs[i] == v) {
			break;//找到该顶点位置
		}
	}
	for (int j = i; j <= G.arcnum - 1; j++) {
		G.vexs[j] = G.vexs[j + 1];//去掉该顶点
	}
	//-------------------------------
	int arcs = 0;
	for (int j = 1; j <= G.vexnum; j++) {
		if (G.arcs[i][j] != INFINITY) {
			G.arcs[i][j] = INFINITY;//删去与v关联弧
			arcs++;//出度
		}
	}
	for (int k = 1; k <= G.vexnum; k++) {
		if (G.arcs[k][i] != INFINITY) {
			G.arcs[k][i] = INFINITY;
			arcs++;//入度
		}
	}
	//---------------------------------
	for (int j = i; j <= G.arcnum - 1; j++) {
		for (int k = 1; k <= G.arcnum; k++) {
			G.arcs[k][j] = G.arcs[k][j + 1];//去掉入度相邻的边 _则列数减一
		}
	}
	for (int j = i; j <= G.arcnum - 1; j++) {
		for (int k = 1; k <= G.arcnum - 1; k++) {
			G.arcs[j][k] = G.arcs[j + 1][k];//去掉出度相邻的边 _则行数减一
		}
	}
	G.arcnum = G.arcnum - arcs;//减去该顶点关联弧
}
//添加弧<v,w>，若是无相边，则还要添加<w,v>
void InsertArc(AMGraph& G, VertexType v, VertexType w) {
	if (!G.vexnum)
		exit(0);
	int locat_v, locat_w;
	for (locat_v = 1; locat_v <= G.vexnum; locat_v++) {
		if (G.vexs[locat_v] == v) {
			break;//找到该顶点位置
		}
	}
	for (locat_w = 1; locat_w <= G.vexnum; locat_w++) {
		if (G.vexs[locat_w] == v) {
			break;//找到该顶点位置
		}
	}
	cout << "输入<v,w>的权值:";
	int weight;
	cin >> weight;
	G.arcs[locat_v][locat_w] = weight;
	G.arcnum++;
	//	G.arcs[locat_w][locat_v] = w;  //无向边
	//	G.arcnum+=2;
}
//删除弧<v,w>，若是无相边，则还要删除<w,v>
void DeleteArc(AMGraph& G, VertexType v, VertexType w) {
	if (!G.vexnum)
		exit(0);
	int locat_v, locat_w;
	for (locat_v = 1; locat_v <= G.vexnum; locat_v++) {
		if (G.vexs[locat_v] == v) {
			break;//找到该顶点位置
		}
	}
	for (locat_w = 1; locat_w <= G.vexnum; locat_w++) {
		if (G.vexs[locat_w] == v) {
			break;//找到该顶点位置
		}
	}
	G.arcs[locat_v][locat_w] = INFINITY;
	G.arcnum--;
	//	G.arcs[locat_w][locat_v] = INFINITY;  //无向边
	//	G.arcnum-=2;

}
void PrintGraph(AMGraph G) {
	cout<<"以下为邻接矩阵输出:"<<endl; 
	for (int i = 1; i <= G.vexnum; i++) {
		cout << G.vexs[i] << "      ";
	}
	cout << endl;
	for (int i = 1; i <= G.vexnum; i++) {
		for (int j = 1; j <= G.vexnum; j++) {
			cout << G.arcs[i][j] << "    ";
		}
		cout << endl;
	}
}
//深度优先遍历，按照先序遍历思想做
void DFSTraverse(AMGraph G) {
	int locate, i;
	bool visited[MAX_VERTEX_NUM];//顶点用字符1 2 3。。。表示
	for (int i = 1; i <= G.vexnum; i++) {
		visited[i] = false;
	}
	Stack DFSstack;
	InitStack(DFSstack);
	VertexType vex_frist;//遍历开始顶点
	cout << "输入开始深度优先遍历的顶点:";
	cin >> vex_frist;
	Push(DFSstack, vex_frist);
	for (i = 1; i <= G.vexnum; i++) {
		if (vex_frist == G.vexs[i]) {
			visited[i] = true;
			break;
		}
	}
	int count = 0;//记录已经遍历的顶点数
	count++;
	VertexType re_vex;//用来返回顶点
	bool flag = false;
	cout << "以下为深度遍历输出:";
	cout << vex_frist;
	while (DFSstack.base != DFSstack.top) {
		GetTop(DFSstack, re_vex);//返回栈顶元素，看该点是否有相邻点，有则进栈，无则本点退栈
		locate = LocateVex(G, re_vex);//返回位置
		for (i = 1; i <= G.vexnum; i++) {
			if (G.arcs[locate][i] != INFINITY && visited[i] == false) {
				G.arcs[locate][i] = INFINITY;
				visited[i] = true;
				flag = true;
				break;
			}//找出下一个没有被访问过的邻接点
		}
		if (flag) {
			Push(DFSstack, G.vexs[i]);
			cout << " -> " << G.vexs[i];
			flag = false;
			count++;
		}
		else {
			Pop(DFSstack, re_vex);
		}
		if (DFSstack.base == DFSstack.top && count != G.vexnum) {
			cout << "  ";
			for (i = 1; i <= G.vexnum; i++) {
				if (visited[i] == false) {
					Push(DFSstack, G.vexs[i]);
					visited[i] = true;
					cout << G.vexs[i];
					break;
				}
			}
		}//有分支情况
	}
}
void BFSTraverse(AMGraph G) {
	if (!G.vexnum)
		exit(0);
	int locate, i;
	bool visited[MAX_VERTEX_NUM];//布尔数组，记录每个元素有没有访问过  顶点用字符1 2 3。。。表示
	for (int i = 1; i <= G.vexnum; i++) {
		visited[i] = false;
	}
	LinkQueue BFSQueue;//队列 
	InitQueue(BFSQueue);
	VertexType vex_frist;//遍历开始顶点
	cout << "输入开始广度优先遍历的顶点:";
	cin >> vex_frist;
	for (i = 1; i <= G.vexnum; i++) {
		if (vex_frist == G.vexs[i]) {
			EnQueue(BFSQueue, vex_frist);
			visited[i] = true;
			break;
		}
	}
	int count = 0;//记录已经遍历的顶点数
	count++;
	VertexType re_vex;//用来返回顶点
	bool flag = false;
	cout << "以下为广度优先搜索输出:";
	cout << G.vexs[i];
	while (BFSQueue.front != BFSQueue.rear) {
		DeQueue(BFSQueue, re_vex);
		locate = LocateVex(G, re_vex);//返回位置
		for (i = 1; i <= G.vexnum; i++) {
			if (G.arcs[locate][i] != INFINITY && visited[i] == false) {
				G.arcs[locate][i] = INFINITY;
				EnQueue(BFSQueue, G.vexs[i]);
				cout << " -> " << G.vexs[i];
				visited[i] = true;
				count++;
			}//找出下一个没有被访问过的邻接点
		}
		if (BFSQueue.front == BFSQueue.rear && count != G.vexnum) {
			cout << "  ";
			for (i = 1; i <= G.vexnum; i++) {
				if (visited[i] == false) {
					EnQueue(BFSQueue, G.vexs[i]);
					visited[i] = true;
					cout << G.vexs[i];
					break;
				}
			}
		}//有分支情况

	}
}
int main()
{
	AMGraph G;
	CreateGraph(G);
	PrintGraph(G);
	while(1){
		DFSTraverse(G);
		cout<<endl; 
		BFSTraverse(G);
		system("pause");
		system("cls");
	} 
	
	return 0;
}

/*测试数据   
1 2 5
1 4 7
2 3 4
3 1 8
3 6 9
4 3 5
4 6 6
5 4 5
6 1 3
6 5 1  */
