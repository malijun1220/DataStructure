/*���ʵ����P121  ADT BinaryTree ��������20�����ö�������ṹʵ�� 11/7/2019 ������*/
#include<iostream>
using namespace std;
#include<cstdlib>2
typedef struct BiTNode{
	char data;  
	struct BiTNode *lchild;//����ָ�� 
	struct BiTNode *rchild;//�Һ���ָ�� 
}BiTNode,*BiTree;
/*��������������������������������������������������������������������������������------------------*/ 
//���л����ܲ��������ڲ�α��� 
typedef struct QNode{
	BiTree elem;//������ڵ� 
	struct QNode *next;
}QNode,*QueuePtr;
typedef struct{
	QueuePtr front;//��ͷָ�� 
	QueuePtr rear;//��βָ�� 
}LinkQueue;
void InitQueue(LinkQueue& Q){
	Q.front=(QNode*)malloc(sizeof(QNode)); //���ﲻҪд��LinkQueue; 
	if(!Q.front){
		cout<<"fail";
		exit(0);
	}
	Q.front->next=NULL;
	Q.rear=Q.front;
} 
//����Ԫ��e��ΪQ��βԪ�� 
void EnQueue(LinkQueue& Q,BiTree T){
	QueuePtr p;
	p=(QNode*)malloc(sizeof(QNode));
	if(!p){
		cout<<"fail";
		exit(0); 
	}
	p->elem=T;
	p->next=NULL;
	Q.rear->next=p;
	Q.rear=p;
}
//ɾ��Q�Ķ�ͷԪ��, ��free 
void DeQueue(LinkQueue& Q,BiTree &t){
	if(Q.front==Q.rear){
		cout<<"�ն���";
		exit(0); 
	}
	QueuePtr p=Q.front->next;
	t=p->elem;
	Q.front->next=p->next;
	if(Q.rear==p)
		Q.rear=Q.front;  //�ն��� 
	free(p);	
}
/*������������������������������������������������������������������������������������������������*/
void InitBiTree(BiTree &T){
	T=(BiTNode*)malloc(sizeof(BiTNode));
	if(!T){
		cout<<"fail";
		exit(0);
	}
	T->data=' ';
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
void ClearBiTree(BiTree& T){
	if(!T)     
		return ;//������exit(0),�Ὣ��������ǿ���˳� 
	DestoryBiTree(T->lchild);	//�ݹ� 
	DestoryBiTree(T->rchild);
	free(T);
}
bool BiTreeEmpty(BiTree T){
	if(T)
		return false;
	else
		return true;	
}
int  BiTreeDepth(BiTree T){
	if(!T)
		return 0;
	//�����������һ����m��ʾ�����������ȣ�n��ʾ���ұ�������ȣ�Ȼ��Ƚ��Ǳߵĸ��� 
	int m=BiTreeDepth(T->lchild)+1;
	int n=BiTreeDepth(T->rchild)+1;
	return m>n?m:n; 
}
//����T�ĸ�  
char Root(BiTree T){
	return T->data;
}
//e��T��ĳ����㣬����e��ֵ  �Ѿ�ȷ��e���� 
char Value(BiTree T,BiTree e){
	if(T==e)
		return T->data;
	else{
		if(T->lchild)
			Value(T->lchild,e);
		if(T->rchild)
			Value(T->rchild,e);
	}
}
//e��T��ĳ���ڵ㣬��value��ֵ���ý��  �Ѿ�ȷ��e���� 
void Assign(BiTree& T,BiTree e,char value){
	if(!T)
		return ;
	if(T==e){
		T->data=value;
		exit(0);
	} 
	else{
		Assign(T->lchild,e,value);
		Assign(T->rchild,e,value);
	}
}
//e��Tĳ���ڵ㣬���ظý���˫�� 
BiTree Parent(BiTree T,BiTree e){
	if(e==T||T==NULL)
		return 0;//��ʾ���ؿ� 
	else{
		if(T->lchild==e||T->rchild==e)	
			return T;
		else if(T->lchild)
			Parent(T->lchild,e);
		else if(T->rchild)
			Parent(T->rchild,e);
	} 
}
//e��Tĳ���ڵ㣬����e�����ӣ��������ӣ��򷵻ؿ� 
BiTree LeftChild(BiTree T,BiTree e){
	if(T==e){
		if(T->lchild)
			return T->lchild;
		else
			return 0;//���ؿ� 
	}
	else{
		if(T->lchild)
			LeftChild(T->lchild,e);
		if(T->rchild)
			LeftChild(T->rchild,e);
	} 
}
BiTree RightChild(BiTree T,BiTree e){
	if(T==e){
		if(T->rchild)
			return T->rchild;
		else
			return 0;//���ؿ� 
	}
	else{
		if(T->lchild)
			LeftChild(T->lchild,e);
		if(T->rchild)
			LeftChild(T->rchild,e);
	} 
}
//�������ֵܣ���eΪT�����ӻ������ֵܣ����ؿ� 
BiTree  LeftSibling(BiTree T,BiTree e){
	if(T==e||T->lchild==e)	
		return 0;
	else{
		if(T->rchild==e){
			if(T->lchild==NULL)
				return 0;
			else
				return T->lchild;
		}
		if(T->lchild)
			LeftSibling(T,e);
		if(T->rchild)
			LeftSibling(T,e);
	}
}
BiTree RightBiTree(BiTree T,BiTree e){
	if(T==e||T->rchild==e)	
		return 0;
	else{
		if(T->lchild==e){
			if(T->rchild==NULL)
				return 0;
			else
				return T->rchild;
		}
		if(T->lchild)
			LeftSibling(T,e);
		if(T->rchild)
			LeftSibling(T,e);
	}
}
//pָ��Tĳ���ڵ㣬LRΪ0����1���ǿն�����c ��T���ཻ��������Ϊ��
//����LRΪ0/1����CΪT��p��ָ���������������p��ָ����ԭ�������������Ϊc��������    0��1�� 
void InsertChild(BiTree T,BiTree p,int LR,BiTree c){
	if(T==p){
		if(LR==0){
			c->rchild=T->lchild;
			T->lchild=c;
		}
		else if(LR==1){
			c->rchild=T->rchild;
			T->rchild==c;
		}
	} 
	else{
		if(T->lchild)
			InsertChild(T->lchild,p,LR,c);
		if(T->rchild)
			InsertChild(T->rchild,p,LR,c);
	}
}
//T���ڣ�pָ��T��ĳ����㣬LRΪ0/1 
// ����LR 0/1��ɾ��T��p��ָ������������� 
void DeleteChild(BiTree& T,BiTree& p,int LR){
	if(T==p){
		if(LR==0){
			DestoryBiTree(T->lchild); 
		}
		else{
			DestoryBiTree(T->rchild);
		}
	} 
	else{
		if(T->lchild)
			DeleteChild(T,p,LR);
		if(T->rchild)
			DeleteChild(T,p,LR);
	}
}
//�������T�������ݹ鷽�� 
int PreOrderTraverse(BiTree T){
	if(!T)
		return 0;//�˳���ǰ�ĵݹ鷵����һ������������ݹ���� 
	cout<<T->data<<" "; //���������cout�����ϲ�    �ȸ� 
	PreOrderTraverse(T->lchild);  //������������� 
	PreOrderTraverse(T->rchild);//������������� 
}
//�������T 
int InOrderTraverse(BiTree T){
	if(!T)
		return 0; 
	 InOrderTraverse(T->lchild);
	 cout<<T->data<<" "; //���������cout���м� 
	 InOrderTraverse(T->rchild);
}
//�������T 
int PostOrderTraverse(BiTree T){
	if(!T)
		return 0;
	PostOrderTraverse(T->lchild);
	PostOrderTraverse(T->rchild);
	cout<<T->data<<" ";  //���������cout�����±� 
}
//��α���T�����ö��� ���ϵ��£������� 
void LevelOrderTraverse(BiTree T){
	if(!T)
		exit(0);
	LinkQueue Q;
	InitQueue(Q);
	EnQueue(Q,T);
	BiTree t;
	while(Q.front!=Q.rear){
		DeQueue(Q,t);
		cout<<t->data<<" ";
		if(t->lchild)
			EnQueue(Q,t->lchild);
		if(t->rchild)
			EnQueue(Q,t->rchild);	
	}	 
}
int main()
{
	BiTree T;
	cout<<"����:";//�������������� 
	CreateBiTree(T);
	cout<<"�������:";
	PreOrderTraverse(T);
	cout<<endl<<"�������:";
	InOrderTraverse(T);
	cout<<endl<<"�������:";
	PostOrderTraverse(T);
	cout<<endl<<"��α���:";
	LevelOrderTraverse(T);
	cout<<endl<<"�����:";
	cout<<BiTreeDepth(T);
	DestoryBiTree(T);
	cout<<endl<<"�������";
	return 0;
}

// ����������ABDH##I##E##CF##GJ#K###
