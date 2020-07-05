/*ͼ��������Ⱥ͹�����ȱ���    2019/12/11  ������*/

#include<iostream>
using namespace std;
#include<cstdlib>
#define STACK_INIT_SIZE 100 //��ʼ���� 
#define STACKINCREMENT 20 //���� 
#define INFINITY 999 //��ʾ��Ȩֵ����������ڵı�
#define MAX_VERTEX_NUM 50 //������Ϣ��������������
typedef int VertexType; //VertexType ����char ��ʾ������������Ϊ�ַ���
typedef struct {
	VertexType vexs[MAX_VERTEX_NUM];  //�����/���� ��
	VertexType  arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];   //�ڽӾ��������ڱߵ�����Ȩֵ��������ֵINFINITY��ʾ����
	int vexnum, arcnum;         //ͼ�ĵ�ǰ�������ͻ���
}AMGraph;

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
/*--------------------------------------------------------*/

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
int  LocateVex(AMGraph G, VertexType u) {
	if (!G.vexnum)
		exit(0);
	for (int i = 1; i <= G.vexnum; i++) {
		if (G.vexs[i] == u)
			return i;//�൱�ڷ�������  (i,i)
	}
	return -1;//��ʾû�иö���
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

void DFSTraverse(AMGraph G) {
	int locate, i;
	bool visited[MAX_VERTEX_NUM];//�������ַ�1 2 3��������ʾ�Ƿ���ʹ� 
	for (int i = 1; i <= G.vexnum; i++) {
		visited[i] = false;
	}
	Stack DFSstack;
	InitStack(DFSstack);
	VertexType vex_frist;//������ʼ����
	cout << "���뿪ʼ������ȱ����Ķ���:";
	cin >> vex_frist;
	Push(DFSstack, vex_frist);//��ʼ����ջ 
	for (i = 1; i <= G.vexnum; i++) {
		if (vex_frist == G.vexs[i]) {
			visited[i] = true; //Ѱ�ҿ�ʼ�ĵ� ����Ϊ���ʹ� 
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
		if (DFSstack.base == DFSstack.top && count != G.vexnum) {//�з�֧���
			cout << "  ";
			for (i = 1; i <= G.vexnum; i++) {
				if (visited[i] == false) {
					Push(DFSstack, G.vexs[i]);
					visited[i] = true;
					cout << G.vexs[i];
					break;
				}
			}
		}
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
			}//�ҳ���һ��û�б����ʹ����ڽӵ�    ���ﲻ��break  ��ΪҪ���õ����ӵ����е㶼�Ž��������� 
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
	DFSTraverse(G);
	cout<<endl; 
	BFSTraverse(G);
	return 0;
}

/*��������   ��������6  �ߣ�10 ���㣺1 2 3 4 5 6 
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
