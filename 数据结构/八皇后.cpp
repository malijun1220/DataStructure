/*�˻ʺ����� ˳��ջ   10/23/2019 ������*/
#include<iostream>
using namespace std;
#include<cstdlib>
#define STACK_INIT_SIZE 100 
#define STACKINCREMENT 20 
#define N 8  //�˻ʺ� 
typedef struct Stack{
	int *top;
	int *base;
	int stacksize;//��ǰ��ʹ�õ�������� 
} Stack;
void InitStack(Stack& S){
	S.base=(int *)malloc(STACK_INIT_SIZE*sizeof(int));
	if(!S.base){
		cout<<"fail";
		exit(0);
	}
	S.top=S.base;//  ��簡  ǧ���д��S.base=S.top 
	S.stacksize=STACK_INIT_SIZE; 	
} 
//����ջ��Ԫ�� 
int GetTop(Stack S){
	if(S.top==S.base){
		cout<<"ջΪ��";
		exit(0);
	}
	else
	return *(S.top-1);
} 
//��ջ 
void Push(Stack& S,int e){
	//if(true)��˵��ջ���Ѿ����ѿ��ٵ����һ���ռ��� 
	if(S.top-S.base>S.stacksize){
		int length=STACK_INIT_SIZE+STACKINCREMENT;
		S.base=(int *)realloc(S.base,length*sizeof(int));
		if(!S.base){
			cout<<"����ʧ��";
			exit(0);
		}
		S.top=S.base+S.stacksize;//����ջ�� 
		S.stacksize+=STACKINCREMENT;
	}
	*S.top++=e;//�ȵ��ڣ���++  <=> S.top=e;S.top++;
}
//��ջ 
void Pop(Stack& S){
	if(S.top==S.base){
		cout<<"��ջ";
		exit(0);
	} 
	--S.top;
}
//�жϵ�ǰ�ʺ�ڷ�λ���Ƿ��ͻ 
bool conflict(Stack& Q,int row,int col){
	int row2=0;
	int col2;
	//Q.top-Q.base ��ʾջ�����ݸ��� 
	while(row2<Q.top-Q.base){
		col2=*(Q.base+row2);
		if(col==col2||(row-row2-1)==(col2-col)||(row-row2-1)==(col-col2)) //��Ϊrow�Ǵ�1��ʼ��  ����Ҫ��� 1 
			return false;
		row2++;
	}
	return true;
}
void EightQueen(Stack& Q){
	Stack q;
	q=Q;
	//��i[row]��¼ÿһ�лʺ�ĳ��԰ڷ�λ�� 
	int i[9]={0,0,0,0,0,0,0,0,0},order=0;
	//colΪ��,rowΪ�� 
	int col,row;
	row=1;
	for(col=1;col<=N;col++){
		//���������� 
		if(conflict(q,row,col)){
			Push(q,col);
			i[row]++;  
			//�ﵽ���У��˻ʺ�ɹ��γɣ���� 
			if(row==8){
				order++;
				cout<<"�� "<<order<<" ���: "; 
				for(int j=0;j<8;j++){
					cout<<*(q.base+j)<<" ";	
				}
				i[row]=0;//��ǰ���һ�лʺ�λ�ó����� 0 
				row--; //ָ��ǰһ�� 
				Pop(q); //��ջ�����һ���ʺ��Ƴ� 
				col=GetTop(q);//��¼�Ƴ��ʺ��ǰ�ʺ��λ�� 
				Pop(q);//����ǰ�ʺ��ջ���Ƴ�����Ϊ����Ҫ�����µĻʺ�λ�ðڷų���
				//����ǰ�лʺ��Լ��ڷŵ������һ��λ�ã�������Ƴ��ʺ� 
				while(i[row]==N){
					col=GetTop(q);
					Pop(q);
					i[row]=0;
					row--;	
				}
				cout<<endl;
				continue;
			} 
			row++;//���������Ļʺ���ջ��ָ����һ�У���һ�дӵ�һ��λ�ÿ�ʼ���԰ڷŻʺ�	
			col=0;
		}
		//���������� 
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
