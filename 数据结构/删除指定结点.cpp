/*���ʵ�֣��Զ�������ÿ��Ԫ��ֵΪx�Ľ�㣬ɾ������Ϊ�������������ͷ���Ӧ�ռ� */
//ջʵ�֡�˼�룺�����������ÿ�����ǰ�Ⱥ�Ҫɾ���Ľ��Ԫ�رȽϣ���������������������һ��ջ��
//������������������һ��վʹ���������з�ʽ�����ٸ�Ԫ�ؽ�������      2019/11/17 ������
#include<iostream>
using namespace std;
#include<cstdlib>
#define STACK_INIT_SIZE 100 
#define STACKINCREMENT 20 
typedef struct BiTNode{
	char data;
	struct BiTNode *lchild;
	struct BiTNode *rchild;
}BiTNode,*BiTree;
typedef struct Stack{
	BiTree* top;
	BiTree* base;
	int stacksize; 
}Stack;
/*----------------------------------------------------------------*/
void InitStack(Stack& S){
	S.base=(BiTree*)malloc(STACK_INIT_SIZE*sizeof(BiTree)); 
	if(!S.base)
		exit(0);
	S.top=S.base;
	S.stacksize=STACK_INIT_SIZE;
} 
//����tΪջ��Ԫ��
void Push(Stack& S,BiTree t){
	if(S.top-S.base>S.stacksize){
		int length=STACK_INIT_SIZE+STACKINCREMENT;
		S.base=(BiTree *)realloc(S.base,length*sizeof(BiTree));
		if(!S.base)
			exit(0);
		S.top=S.base+S.stacksize;//����ջ�� 
		S.stacksize+=STACKINCREMENT;
	}
	*S.top++=t;
}
//ջ��Ԫ�س�ջ������t���� 
void Pop(Stack& S,BiTree &t){
	if(S.top==S.base)
		exit(0);
	t=*--S.top;//��Ϊtop��ָ��ǰջ��Ԫ�ص���һλ�� 
}

/*----------------------------------------------------------------*/
void InitBiTree(BiTree &T){
	T=(BiTNode*)malloc(sizeof(BiTNode));
	if(!T){
		cout<<"fail";
		exit(0);
	}
	T->lchild=NULL;
	T->rchild=NULL;
} 
void CreateBiTree(BiTree& T ){
	char ch;
	cin>>ch;
	if(ch=='#') T=NULL; //���൱����/������Ϊ�� 
	else{
		if(!(T=(BiTNode*)malloc(sizeof(BiTNode)))){
			exit(0);
		}
		T->data=ch;
		CreateBiTree(T->lchild);//���������� 
		CreateBiTree(T->rchild);//���������� 
	}
}
void DestoryBiTree(BiTree& T){
	if(!T)     
		return ;//������exit(0),�Ὣ��������ǿ���˳� 
	DestoryBiTree(T->lchild);	//�ݹ� 
	DestoryBiTree(T->rchild);
	free(T);	
} 
void De_Appoint_BiTree(BiTree& T,char elem){
	if(!T)
		return ;
	if(T->data==elem){
		DestoryBiTree(T);
		T=NULL;
	}
	else{
		De_Appoint_BiTree(T->lchild,elem);//����ֱ�ӽ���ɾ��������������Ҫ��ǰ�жϸõ����û�У���Ϊ�����ٺ����У����õ�û�У���Ȼ�᷵�ء� 
		De_Appoint_BiTree(T->rchild,elem);
	} 
}
void PreOrderTraverse(BiTree T){
	if(!T)
		exit(0);
	Stack S;
	InitStack(S);
	BiTree t;
	Push(S,T);
	while(S.top!=S.base){
		Pop(S,t);
		cout<<t->data<<" "; 
		if(t->rchild)
			Push(S,t->rchild);//���������ǿգ�����ջ 
		if(t->lchild)
			Push(S,t->lchild);
	} 
} 
int main()
{
	BiTree T;
	cout<<"������:";
	CreateBiTree(T);
	cout<<"������Ҫɾ���Ľ���Ԫ��:";
	char e;
	cin>>e;
	De_Appoint_BiTree(T,e);
	cout<<"ɾ������������Ϊ:";
	PreOrderTraverse(T);
	return 0;
}
 // ����������ABDH##I##E##CF##GJ#K###
 //				ABDE##I#G#E###CF##HEN##M###
 
 //************��дһ�������ֵ�����ɾ�� 
 
