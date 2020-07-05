/*实现二叉排序树的插入和删除  2019/12/12 马丽钧*/
//本程序直接输入排好序的二叉排序树     (后期自己编一个将普通树转换成二叉排序树的程序) 
//判断二叉排序树的方法是中序遍历输出，看是否有序 
//插入用递归方法 

#include<iostream>
#include<cstdlib>
using namespace std;
typedef struct BSTree{
	int data;
	struct BSTree *lchild;
	struct BSTree *rchild;
}BSTNode,*BST;
void CreateBST(BST& T){
	int key;
	cin>>key; 
	if(key==-1){
		T=NULL;
	} 
	else{
		if(!(T=(BSTNode*)malloc(sizeof(BSTNode)))){
			exit(0);
		}
		T->data=key;
		CreateBST(T->lchild);//先创建左子树 
		CreateBST(T->rchild);
	}
}

void InsertBST(BST& T,int key){	
	if(!T){
		T=(BSTNode*)malloc(sizeof(BSTNode));
		T->data=key;
		T->rchild=NULL;
		T->lchild=NULL;
		return ;
	}
	if(T->data==key){
		return ;//树中已经存在该元素 
	}
	if(T->data<key){
		InsertBST(T->rchild,key);//key大于本元素，故向右子树寻找 
	}
	else{
		InsertBST(T->lchild,key);
	}	
}
void DeleteBST(BST& T,int key){
	if(!T){
		exit(0);
	} 
	BST P,Q,S,t=NULL;
	P=T;
	while(P){
		if(P->data==key)//找到删除点 
			break;
		t=P;
		if(key>P->data)
			P=P->rchild ;
		else
			P=P->lchild ;
	}
	////////////////
	if(!P){
		cout<<"未找到删除结点"<<endl;  //防止正常跳出while 而没有找到删除点 
		return ; 
	} 
	///////////////
	Q=P;
	if(P->lchild &&P->rchild){
		S=P->lchild ;
		while(S->rchild){
			Q=S;
			S=S->rchild ;
		}
		P->data=S->data;
		if(Q!=P){
			Q->rchild=S->lchild; //S->lchild可以换成NULL 
		}
		else{
			Q->lchild =S->lchild;//只有一个左孩子的情况 
		}
		free(S);
	} 
	else if(!P->rchild){
		P=P->lchild;
	}////
	else if(!P->lchild){
		P=P->rchild;
	}///
/*	if(Q==t->lchild){
		t->lchild=P;
	}
	else{
		t->rchild=P;
	}*/
}

int InOrderTraverse(BST T){
	if(!T)
		return 0; 
	InOrderTraverse(T->lchild);
	cout<<T->data<<" "; //中序遍历则cout在中间 
	InOrderTraverse(T->rchild);
}
int main()
{
	BST T;
	cout<<"请构造二叉排序树(-1表示空):"; 
	CreateBST(T);
	InOrderTraverse(T);
	cout<<endl;
	int key,again;
	bool flag=true;
	while(flag){
		cout<<"输入需插入的数据:"; //插入的都是叶子 
		cin>>key;
		InsertBST(T,key);
		InOrderTraverse(T);
		cout<<"继续？(1/0)";
		cin>>again;
		if(again==0){
			break;
		} 
	}
	while(flag){
		cout<<"输入需删除的数据:";   //删除后应更矮，将左子树的最右结点代替删除点 
		cin>>key;
		DeleteBST(T,key); 
		InOrderTraverse(T);
		cout<<"继续？(1/0)";
		cin>>again;
		if(again==0){
			break;
		} 
	}
	return 0;
} 

//测试数据 45 12 3 -1 -1 37 24 -1 -1 -1 53 -1 100 61 -1 90 78 -1 -1 -1 -1
//45 24 3 2 -1 -1 12 -1 -1 37 -1 -1 61 -1 -1

