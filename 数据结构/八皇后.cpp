/*八皇后问题 顺序栈   10/23/2019 马丽钧*/
#include<iostream>
using namespace std;
#include<cstdlib>
#define STACK_INIT_SIZE 100 
#define STACKINCREMENT 20 
#define N 8  //八皇后 
typedef struct Stack{
	int *top;
	int *base;
	int stacksize;//当前可使用的最大容量 
} Stack;
void InitStack(Stack& S){
	S.base=(int *)malloc(STACK_INIT_SIZE*sizeof(int));
	if(!S.base){
		cout<<"fail";
		exit(0);
	}
	S.top=S.base;//  哥哥啊  千万别写成S.base=S.top 
	S.stacksize=STACK_INIT_SIZE; 	
} 
//返回栈顶元素 
int GetTop(Stack S){
	if(S.top==S.base){
		cout<<"栈为空";
		exit(0);
	}
	else
	return *(S.top-1);
} 
//入栈 
void Push(Stack& S,int e){
	//if(true)则说并栈顶已经在已开辟的最后一个空间外 
	if(S.top-S.base>S.stacksize){
		int length=STACK_INIT_SIZE+STACKINCREMENT;
		S.base=(int *)realloc(S.base,length*sizeof(int));
		if(!S.base){
			cout<<"增添失败";
			exit(0);
		}
		S.top=S.base+S.stacksize;//设置栈顶 
		S.stacksize+=STACKINCREMENT;
	}
	*S.top++=e;//先等于，再++  <=> S.top=e;S.top++;
}
//出栈 
void Pop(Stack& S){
	if(S.top==S.base){
		cout<<"空栈";
		exit(0);
	} 
	--S.top;
}
//判断当前皇后摆放位置是否冲突 
bool conflict(Stack& Q,int row,int col){
	int row2=0;
	int col2;
	//Q.top-Q.base 表示栈内数据个数 
	while(row2<Q.top-Q.base){
		col2=*(Q.base+row2);
		if(col==col2||(row-row2-1)==(col2-col)||(row-row2-1)==(col-col2)) //因为row是从1开始的  所以要多减 1 
			return false;
		row2++;
	}
	return true;
}
void EightQueen(Stack& Q){
	Stack q;
	q=Q;
	//用i[row]记录每一行皇后的尝试摆放位置 
	int i[9]={0,0,0,0,0,0,0,0,0},order=0;
	//col为列,row为行 
	int col,row;
	row=1;
	for(col=1;col<=N;col++){
		//若符合条件 
		if(conflict(q,row,col)){
			Push(q,col);
			i[row]++;  
			//达到八行，八皇后成功形成，输出 
			if(row==8){
				order++;
				cout<<"第 "<<order<<" 组解: "; 
				for(int j=0;j<8;j++){
					cout<<*(q.base+j)<<" ";	
				}
				i[row]=0;//当前最后一行皇后位置尝试置 0 
				row--; //指向前一行 
				Pop(q); //将栈中最后一个皇后移除 
				col=GetTop(q);//记录移除皇后后当前皇后的位置 
				Pop(q);//将当前皇后从栈内移除，因为此行要进行新的皇后位置摆放尝试
				//若当前行皇后以及摆放到了最后一个位置，则继续移除皇后 
				while(i[row]==N){
					col=GetTop(q);
					Pop(q);
					i[row]=0;
					row--;	
				}
				cout<<endl;
				continue;
			} 
			row++;//符合条件的皇后入栈后，指向下一行，下一行从第一个位置开始尝试摆放皇后	
			col=0;
		}
		//不符合条件 
		else{
			i[row]++;
			while(i[row]==N){
				col=GetTop(q);
				Pop(q);
				i[row]=0;
				row--;
			}
		}
		if(i[1]==8&&i[2]==6)
			exit(0);			
	}	
}
int main(){
	Stack Q;
	InitStack(Q); 
	EightQueen(Q);
	return 0;
} 
