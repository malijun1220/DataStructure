/*编程实现书P121  ADT BinaryTree 基本操作20个，用二叉链表结构实现 11/7/2019 马丽钧*/
#include<iostream>
using namespace std;
#include<cstdlib>2
typedef struct BiTNode{
	char data;  
	struct BiTNode *lchild;//左孩子指针 
	struct BiTNode *rchild;//右孩子指针 
}BiTNode,*BiTree;
/*————————————————————————————————————————------------------*/ 
//队列基本曹操作，用于层次遍历 
typedef struct QNode{
	BiTree elem;//储存根节点 
	struct QNode *next;
}QNode,*QueuePtr;
typedef struct{
	QueuePtr front;//队头指针 
	QueuePtr rear;//队尾指针 
}LinkQueue;
void InitQueue(LinkQueue& Q){
	Q.front=(QNode*)malloc(sizeof(QNode)); //这里不要写成LinkQueue; 
	if(!Q.front){
		cout<<"fail";
		exit(0);
	}
	Q.front->next=NULL;
	Q.rear=Q.front;
} 
//插入元素e作为Q队尾元素 
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
//删除Q的队头元素, 并free 
void DeQueue(LinkQueue& Q,BiTree &t){
	if(Q.front==Q.rear){
		cout<<"空队列";
		exit(0); 
	}
	QueuePtr p=Q.front->next;
	t=p->elem;
	Q.front->next=p->next;
	if(Q.rear==p)
		Q.rear=Q.front;  //空队列 
	free(p);	
}
/*————————————————————————————————————————————————*/
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
	if(ch=='#') T=NULL; //即相当于左/右子树为空 
	else{
		if(!(T=(BiTNode*)malloc(sizeof(BiTNode)))){
			exit(0);
		}
		T->data=ch;
		CreateBiTree(T->lchild);//创建左子树 
		CreateBiTree(T->rchild);//创建右子树 
	}
}
void DestoryBiTree(BiTree& T){
	if(!T)     
		return ;//不能用exit(0),会将整个程序强制退出 
	DestoryBiTree(T->lchild);	//递归 
	DestoryBiTree(T->rchild);
	free(T);	
} 
void ClearBiTree(BiTree& T){
	if(!T)     
		return ;//不能用exit(0),会将整个程序强制退出 
	DestoryBiTree(T->lchild);	//递归 
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
	//类似现需遍历一样，m表示向左遍历的深度，n表示向右遍历的深度，然后比较那边的更深 
	int m=BiTreeDepth(T->lchild)+1;
	int n=BiTreeDepth(T->rchild)+1;
	return m>n?m:n; 
}
//返回T的根  
char Root(BiTree T){
	return T->data;
}
//e是T中某个结点，返回e的值  已经确定e存在 
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
//e是T的某个节点，将value赋值给该结点  已经确定e存在 
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
//e是T某个节点，返回该结点的双亲 
BiTree Parent(BiTree T,BiTree e){
	if(e==T||T==NULL)
		return 0;//表示返回空 
	else{
		if(T->lchild==e||T->rchild==e)	
			return T;
		else if(T->lchild)
			Parent(T->lchild,e);
		else if(T->rchild)
			Parent(T->rchild,e);
	} 
}
//e是T某个节点，返回e的左孩子，若无左孩子，则返回空 
BiTree LeftChild(BiTree T,BiTree e){
	if(T==e){
		if(T->lchild)
			return T->lchild;
		else
			return 0;//返回空 
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
			return 0;//返回空 
	}
	else{
		if(T->lchild)
			LeftChild(T->lchild,e);
		if(T->rchild)
			LeftChild(T->rchild,e);
	} 
}
//返回左兄弟，若e为T的左孩子或无左兄弟，返回空 
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
//p指向T某个节点，LR为0或者1，非空二叉树c 与T不相交且右子树为空
//根于LR为0/1，插C为T中p所指结点的左或右子树。p所指结点的原有左或右子树则为c的右子树    0左1右 
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
//T存在，p指向T中某个结点，LR为0/1 
// 根据LR 0/1，删除T中p所指结点的左或右子树 
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
//先序遍历T，——递归方法 
int PreOrderTraverse(BiTree T){
	if(!T)
		return 0;//退出当前的递归返回上一层而不是整个递归结束 
	cout<<T->data<<" "; //先序遍历则cout在最上层    先根 
	PreOrderTraverse(T->lchild);  //先序遍历左子树 
	PreOrderTraverse(T->rchild);//先序遍历右子树 
}
//中序遍历T 
int InOrderTraverse(BiTree T){
	if(!T)
		return 0; 
	 InOrderTraverse(T->lchild);
	 cout<<T->data<<" "; //中序遍历则cout在中间 
	 InOrderTraverse(T->rchild);
}
//后序遍历T 
int PostOrderTraverse(BiTree T){
	if(!T)
		return 0;
	PostOrderTraverse(T->lchild);
	PostOrderTraverse(T->rchild);
	cout<<T->data<<" ";  //后序遍历则cout在最下边 
}
//层次遍历T——用队列 由上到下，由左到右 
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
	cout<<"输入:";//按先序序列输入 
	CreateBiTree(T);
	cout<<"先序遍历:";
	PreOrderTraverse(T);
	cout<<endl<<"中序遍历:";
	InOrderTraverse(T);
	cout<<endl<<"后序遍历:";
	PostOrderTraverse(T);
	cout<<endl<<"层次遍历:";
	LevelOrderTraverse(T);
	cout<<endl<<"树深度:";
	cout<<BiTreeDepth(T);
	DestoryBiTree(T);
	cout<<endl<<"销毁完成";
	return 0;
}

// 测试用例：ABDH##I##E##CF##GJ#K###
