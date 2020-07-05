	/*���ʵ����P156  ADT Graph ��������13�������ڽӾ���洢�ṹʵ�� ע��n���������n*n��λ����  2019/11/23 ������*/
//---------------------�����ջ-------------����ò��
//�˳���д����---------������---------------����λ�ö���1��ʼ��0λ�÷��ò���
//--------------------����Ϊ�������� int�ͱ�ʾ-------------
//#pragma once
//#pragma warning(disable:4996)
#include<iostream>
using namespace std;
#include<cstdlib>
#define STACK_INIT_SIZE 100 //��ʼ���� 
#define STACKINCREMENT 20 //���� 
#define INFINITY 999 //��ʾ��Ȩֵ����������ڵı�
#define MAX_VERTEX_NUM 50 //������Ϣ��������������
#include<windows.h>
typedef int VertexType; //VertexType ����char ��ʾ������������Ϊ�ַ���
//typedef enum{DG,DN,UDG,UDN} GraohKind;  //ͼ������{����ͼ��������������ͼ��������}
//typedef int AdjMatrix;//����ߵ�ȨֵΪ����
typedef struct {
	VertexType vexs[MAX_VERTEX_NUM];  //�����/���� ��
	VertexType  arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];   //�ڽӾ��������ڱߵ�����Ȩֵ��������ֵINFINITY��ʾ����
	int vexnum, arcnum;         //ͼ�ĵ�ǰ�������ͻ���
}AMGraph;
//��ʽ���� 
typedef struct QNode {
	VertexType elem;
	struct QNode* next;
}QNode, * QueuePtr;
typedef struct {
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;
//˳��ջ
typedef struct Stack {
	VertexType* top;
	VertexType* base;
	int stacksize;
}Stack;
/*-------------------------------------------------ջ*/
void InitStack(Stack& S) {
	S.base = (VertexType*)malloc(STACK_INIT_SIZE * sizeof(VertexType));
	if (!S.base)
		exit(0);
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
}
//����tΪջ��Ԫ��
void Push(Stack& S, VertexType t) {
	if (S.top - S.base > S.stacksize) {
		int length = STACK_INIT_SIZE + STACKINCREMENT;
		S.base = (VertexType*)realloc(S.base, length * sizeof(VertexType));
		if (!S.base)
			exit(0);
		S.top = S.base + S.stacksize;//����ջ�� 
		S.stacksize += STACKINCREMENT;
	}
	*S.top++ = t;
}
//ջ��Ԫ�س�ջ������t���� 
void Pop(Stack& S, VertexType& t) {
	if (S.top == S.base)
		exit(0);
	t = *--S.top;//��Ϊtop��ָ��ǰջ��Ԫ�ص���һλ�� 
}
//����ջ��Ԫ�� 
void GetTop(Stack S, VertexType& t) {
	if (S.top == S.base) {
		exit(0);
	}
	else
		t = *(S.top - 1);
}
/*-------------------------------------------------����*/
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
		Q.rear = Q.front;//ָ���		
	}
	free(P);
}
/*-------------------------------------------------*/
void CreateGraph(AMGraph& G) {
	cout << "�ж��ٶ���(v):";
	cin >> G.vexnum;
	cout << "�ж��ٱ�(a):";
	cin >> G.arcnum;
	cout << "���������붥��:";
	int i, j, weight, k;//w��ʾȨֵ weight
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
			return i;//�൱�ڷ�������  (i,i)
	}
	return -1;//��ʾû�иö���
}
//���ض���v��ֵ  ʲôֵ�����������������ܶ������������Ǹõ���ص�ָ����Ϣ
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
			degree++;//����
		}
	}
	for (int k = 1; k <= G.vexnum; k++) {
		if (G.arcs[k][i] != INFINITY) {
			degree++;//���
		}
	}
	return degree;//�ܶ���
}
//�������
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
//���ص�һ���ڽӶ��㣬������Ӧ���Ƿ���Ȩֵ��С���ڽӶ���(����ͼ���ص��ǳ��ȱߵ����ڵ�)
char FirstAdjVex(AMGraph G, VertexType v) {
	if (!G.vexnum)
		exit(0);
	int i, j, z;
	int w = 0;
	for (i = 1; i <= G.vexnum; i++) {
		if (G.vexs[i] == v)
			break;
	}//ȷ����β����λ��
	for (j = 1; j <= G.vexnum; j++) {
		if (G.arcs[i][j] != INFINITY) {
			if (w < G.arcs[i][j]) {
				w = G.arcs[i][j];
				z = j;
			}
		}
	}//ȷ����ͷ����λ��
	if (w)
		return G.vexs[z];//����г��ȣ����ȷ��س�����Ȩֵ��С�ı�
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
		return G.vexs[z];//���޳��ȣ��򷵻������Ȩֵ��С��*/
	else
		return 0;//�����ڵ�
}
//v->w,����w����һ��(����)���ڵ㣬���޷��ؿա�
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
	return  0;//����һ������
}
void InsertVex(AMGraph& G, VertexType v) {
	if (!G.vexnum)
		exit(0);
	for (int i = 1; i <= G.vexnum; i++) {
		if (G.vexs[i] == v) {
			G.arcs[i][i] = 0;
			break; //���v����v��һ��Ȧ���Լ����Լ���ȨֵΪ0��
		}
	}
}
//ɾ������v�Լ���صĻ�
void DeleteVex(AMGraph& G, VertexType v) {
	if (!G.vexnum)
		exit(0);
	int i;
	for (i = 1; i <= G.vexnum; i++) {
		if (G.vexs[i] == v) {
			break;//�ҵ��ö���λ��
		}
	}
	for (int j = i; j <= G.arcnum - 1; j++) {
		G.vexs[j] = G.vexs[j + 1];//ȥ���ö���
	}
	//-------------------------------
	int arcs = 0;
	for (int j = 1; j <= G.vexnum; j++) {
		if (G.arcs[i][j] != INFINITY) {
			G.arcs[i][j] = INFINITY;//ɾȥ��v������
			arcs++;//����
		}
	}
	for (int k = 1; k <= G.vexnum; k++) {
		if (G.arcs[k][i] != INFINITY) {
			G.arcs[k][i] = INFINITY;
			arcs++;//���
		}
	}
	//---------------------------------
	for (int j = i; j <= G.arcnum - 1; j++) {
		for (int k = 1; k <= G.arcnum; k++) {
			G.arcs[k][j] = G.arcs[k][j + 1];//ȥ��������ڵı� _��������һ
		}
	}
	for (int j = i; j <= G.arcnum - 1; j++) {
		for (int k = 1; k <= G.arcnum - 1; k++) {
			G.arcs[j][k] = G.arcs[j + 1][k];//ȥ���������ڵı� _��������һ
		}
	}
	G.arcnum = G.arcnum - arcs;//��ȥ�ö��������
}
//��ӻ�<v,w>����������ߣ���Ҫ���<w,v>
void InsertArc(AMGraph& G, VertexType v, VertexType w) {
	if (!G.vexnum)
		exit(0);
	int locat_v, locat_w;
	for (locat_v = 1; locat_v <= G.vexnum; locat_v++) {
		if (G.vexs[locat_v] == v) {
			break;//�ҵ��ö���λ��
		}
	}
	for (locat_w = 1; locat_w <= G.vexnum; locat_w++) {
		if (G.vexs[locat_w] == v) {
			break;//�ҵ��ö���λ��
		}
	}
	cout << "����<v,w>��Ȩֵ:";
	int weight;
	cin >> weight;
	G.arcs[locat_v][locat_w] = weight;
	G.arcnum++;
	//	G.arcs[locat_w][locat_v] = w;  //�����
	//	G.arcnum+=2;
}
//ɾ����<v,w>����������ߣ���Ҫɾ��<w,v>
void DeleteArc(AMGraph& G, VertexType v, VertexType w) {
	if (!G.vexnum)
		exit(0);
	int locat_v, locat_w;
	for (locat_v = 1; locat_v <= G.vexnum; locat_v++) {
		if (G.vexs[locat_v] == v) {
			break;//�ҵ��ö���λ��
		}
	}
	for (locat_w = 1; locat_w <= G.vexnum; locat_w++) {
		if (G.vexs[locat_w] == v) {
			break;//�ҵ��ö���λ��
		}
	}
	G.arcs[locat_v][locat_w] = INFINITY;
	G.arcnum--;
	//	G.arcs[locat_w][locat_v] = INFINITY;  //�����
	//	G.arcnum-=2;

}
void PrintGraph(AMGraph G) {
	cout<<"����Ϊ�ڽӾ������:"<<endl; 
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
//������ȱ����������������˼����
void DFSTraverse(AMGraph G) {
	int locate, i;
	bool visited[MAX_VERTEX_NUM];//�������ַ�1 2 3��������ʾ
	for (int i = 1; i <= G.vexnum; i++) {
		visited[i] = false;
	}
	Stack DFSstack;
	InitStack(DFSstack);
	VertexType vex_frist;//������ʼ����
	cout << "���뿪ʼ������ȱ����Ķ���:";
	cin >> vex_frist;
	Push(DFSstack, vex_frist);
	for (i = 1; i <= G.vexnum; i++) {
		if (vex_frist == G.vexs[i]) {
			visited[i] = true;
			break;
		}
	}
	int count = 0;//��¼�Ѿ������Ķ�����
	count++;
	VertexType re_vex;//�������ض���
	bool flag = false;
	cout << "����Ϊ��ȱ������:";
	cout << vex_frist;
	while (DFSstack.base != DFSstack.top) {
		GetTop(DFSstack, re_vex);//����ջ��Ԫ�أ����õ��Ƿ������ڵ㣬�����ջ�����򱾵���ջ
		locate = LocateVex(G, re_vex);//����λ��
		for (i = 1; i <= G.vexnum; i++) {
			if (G.arcs[locate][i] != INFINITY && visited[i] == false) {
				G.arcs[locate][i] = INFINITY;
				visited[i] = true;
				flag = true;
				break;
			}//�ҳ���һ��û�б����ʹ����ڽӵ�
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
		}//�з�֧���
	}
}
void BFSTraverse(AMGraph G) {
	if (!G.vexnum)
		exit(0);
	int locate, i;
	bool visited[MAX_VERTEX_NUM];//�������飬��¼ÿ��Ԫ����û�з��ʹ�  �������ַ�1 2 3��������ʾ
	for (int i = 1; i <= G.vexnum; i++) {
		visited[i] = false;
	}
	LinkQueue BFSQueue;//���� 
	InitQueue(BFSQueue);
	VertexType vex_frist;//������ʼ����
	cout << "���뿪ʼ������ȱ����Ķ���:";
	cin >> vex_frist;
	for (i = 1; i <= G.vexnum; i++) {
		if (vex_frist == G.vexs[i]) {
			EnQueue(BFSQueue, vex_frist);
			visited[i] = true;
			break;
		}
	}
	int count = 0;//��¼�Ѿ������Ķ�����
	count++;
	VertexType re_vex;//�������ض���
	bool flag = false;
	cout << "����Ϊ��������������:";
	cout << G.vexs[i];
	while (BFSQueue.front != BFSQueue.rear) {
		DeQueue(BFSQueue, re_vex);
		locate = LocateVex(G, re_vex);//����λ��
		for (i = 1; i <= G.vexnum; i++) {
			if (G.arcs[locate][i] != INFINITY && visited[i] == false) {
				G.arcs[locate][i] = INFINITY;
				EnQueue(BFSQueue, G.vexs[i]);
				cout << " -> " << G.vexs[i];
				visited[i] = true;
				count++;
			}//�ҳ���һ��û�б����ʹ����ڽӵ�
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
		}//�з�֧���

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

/*��������   
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
