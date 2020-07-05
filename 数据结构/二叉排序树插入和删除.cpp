/*ʵ�ֶ����������Ĳ����ɾ��  2019/12/12 ������*/
//������ֱ�������ź���Ķ���������     (�����Լ���һ������ͨ��ת���ɶ����������ĳ���) 
//�ж϶����������ķ��������������������Ƿ����� 
//�����õݹ鷽�� 

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
		CreateBST(T->lchild);//�ȴ��������� 
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
		return ;//�����Ѿ����ڸ�Ԫ�� 
	}
	if(T->data<key){
		InsertBST(T->rchild,key);//key���ڱ�Ԫ�أ�����������Ѱ�� 
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
		if(P->data==key)//�ҵ�ɾ���� 
			break;
		t=P;
		if(key>P->data)
			P=P->rchild ;
		else
			P=P->lchild ;
	}
	////////////////
	if(!P){
		cout<<"δ�ҵ�ɾ�����"<<endl;  //��ֹ��������while ��û���ҵ�ɾ���� 
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
			Q->rchild=S->lchild; //S->lchild���Ի���NULL 
		}
		else{
			Q->lchild =S->lchild;//ֻ��һ�����ӵ���� 
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
	cout<<T->data<<" "; //���������cout���м� 
	InOrderTraverse(T->rchild);
}
int main()
{
	BST T;
	cout<<"�빹�����������(-1��ʾ��):"; 
	CreateBST(T);
	InOrderTraverse(T);
	cout<<endl;
	int key,again;
	bool flag=true;
	while(flag){
		cout<<"��������������:"; //����Ķ���Ҷ�� 
		cin>>key;
		InsertBST(T,key);
		InOrderTraverse(T);
		cout<<"������(1/0)";
		cin>>again;
		if(again==0){
			break;
		} 
	}
	while(flag){
		cout<<"������ɾ��������:";   //ɾ����Ӧ�������������������ҽ�����ɾ���� 
		cin>>key;
		DeleteBST(T,key); 
		InOrderTraverse(T);
		cout<<"������(1/0)";
		cin>>again;
		if(again==0){
			break;
		} 
	}
	return 0;
} 

//�������� 45 12 3 -1 -1 37 24 -1 -1 -1 53 -1 100 61 -1 90 78 -1 -1 -1 -1
//45 24 3 2 -1 -1 12 -1 -1 37 -1 -1 61 -1 -1

