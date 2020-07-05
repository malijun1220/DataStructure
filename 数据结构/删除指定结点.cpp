/*编程实现，对二叉树中每个元素值为x的结点，删除以它为根的子树，并释放相应空间 */
//栈实现。思想：用先序遍历，每次输出前先和要删除的结点元素比较，若相等则不输出，存入另外一个栈，
//遍历结束后用在另外一个站使用先序排列方式，销毁该元素结点的子树      2019/11/17 马丽钧
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
//插入t为栈顶元素
void Push(Stack& S,BiTree t){
	if(S.top-S.base>S.stacksize){
		int length=STACK_INIT_SIZE+STACKINCREMENT;
		S.base=(BiTree *)realloc(S.base,length*sizeof(BiTree));
		if(!S.base)
			exit(0);
		S.top=S.base+S.stacksize;//设置栈顶 
		S.stacksize+=STACKINCREMENT;
	}
	*S.top++=t;
}
//栈顶元素出栈，并用t返回 
void Pop(Stack& S,BiTree &t){
	if(S.top==S.base)
		exit(0);
	t=*--S.top;//因为top总指向当前栈顶元素的下一位置 
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
void De_Appoint_BiTree(BiTree& T,char elem){
	if(!T)
		return ;
	if(T->data==elem){
		DestoryBiTree(T);
		T=NULL;
	}
	else{
		De_Appoint_BiTree(T->lchild,elem);//这里直接进入删除函数，而不需要提前判断该店点有没有，因为在销毁函数中，若该点没有，自然会返回。 
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
			Push(S,t->rchild);//若该子树非空，则入栈 
		if(t->lchild)
			Push(S,t->lchild);
	} 
} 
int main()
{
	BiTree T;
	cout<<"创建树:";
	CreateBiTree(T);
	cout<<"输入需要删除的结点的元素:";
	char e;
	cin>>e;
	De_Appoint_BiTree(T,e);
	cout<<"删除后的先序遍历为:";
	PreOrderTraverse(T);
	return 0;
}
 // 测试用例：ABDH##I##E##CF##GJ#K###
 //				ABDE##I#G#E###CF##HEN##M###
 
 //************再写一个孩子兄弟链的删除 
 
