/*实现堆排序算法 2019/12/13 马丽钧*/

//将一维数组看成是一棵二叉树，分大顶堆和小顶堆，其排列顺序即对-----应完全二叉树-----------层次遍历的输出 -----

//i= 1,2,3..n/2(不大于n/2的对打整数,fabs(n/2))
//大顶堆：k[i]>=k[2i]  ，k[i]>=k[2i+1]     1<=i<=n/2
//小顶堆：k[i]<=k[2i]  ，k[i]<=k[2i+1]     1<=i<=n/2 
//堆是一个过程，每次找到最大或最小，取出，最后形成一个有序数组 
//从底开始，让每一个树都是一个堆 
//第一个元素的位置为 1  而不是 0  
//从最后一个非子叶的结点开始 


//本程序是建立大顶堆，实现升序 
#include<iostream>
using namespace std;
#include<cstdlib> 
#define LIST_INIT_SIZE 100//初始分配空间
#define LISTINCREMENT 50//分配增量
typedef struct Sqlist{
	int* data;
	int length;
	int listsize;
}Sqlist;
void InitList(Sqlist& L){
	L.data = (int*)malloc(LIST_INIT_SIZE * sizeof(int));
	if (!L.data) {
		cout << "fail";
		exit(0);
	}
	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
} 
void CreateList(Sqlist& L){
	int i;
	cout << "以 0 结束:";
	for (i = 1; i <= L.listsize; i++) {
		cin >> L.data[i];
		L.length++;
		if (L.data[i] == 0) {
			L.length--;
			break;
		}
		if (i >= L.listsize) {
			int* newbase;
			int Length = L.length + LISTINCREMENT;//不替换则会溢出
			newbase = (int*)realloc(L.data, Length * sizeof(int));//原来的基础上重新分配空间，L.elem是原来的首地址
			if (!newbase) {
				cout << "space increase fail";
				exit(0);
			}
			L.data = newbase;//在原来的基础上增加，首地址没有变
			L.listsize = Length;
			cout << "space increase succeed" << endl;
		}

	}
	cout <<"输入长度: "<<L.length << endl;
}
void PrintList(Sqlist L){
	int i;
	for(i=1;i<=L.length;i++){
		cout<<L.data[i]<<" ";
	}
}

void HeapAdjust(Sqlist& L,int n,int k){
	//n为需要操作的数组长度，k为要调整的元素位置 
	int i,j,ta;
	i=k;
    j=2*i;
    ta=L.data[i]; //t的职能类似于pivotkey ，记录要调整的元素 
    while(j<=n)
    {
        if(j<n&&L.data[j]<L.data[j+1])//选择走左边还是走右边，谁大就走那边 
			 j++;  
        if(ta>L.data[j])
			 break;//如果双亲大于孩子，说明不用再往下调整了，因为Ldata[j]以及是子树中最大的了 
        L.data[i]=L.data[j];//否则孩子的值给双亲 
        i=j;//孩子变新的双亲 
		j=2*i;//新双亲的左孩子 
    }
    L.data[i]=ta;//需调整的值找到最终位置 
}
void HeapSort(Sqlist& L){
	int i,t;
	cout<<"初始建堆过程:"<<endl; 
	//第一个for是用于将一组无序的树建立成一个堆，从最后一个非枝叶的双亲开始，由下往上确保每一个结点都是堆 
    for(i=L.length/2;i>=1;i--){
    	HeapAdjust(L,L.length,i);
    	PrintList(L);
    	cout<<endl;
    }//至此，初始堆建成，最大元素在堆顶
	
	//第二个for是排序过程 将堆顶最大元素与最后一个位置的元素对换，
	//最后一个位置就成了大元素了，此时相当于已经取出，最后位置n往前挪，变为n-1
	 
	//由于位置交换，改变了堆，所以要从根结点向下筛选调整 
    cout<<"取出以及再调整过程:"<<endl;
    for(i=L.length;i>=2;i--)
    {
        t=L.data[i];
		L.data[i]=L.data[1];
		L.data[1]=t;
        HeapAdjust(L,i-1,1);// 1 是要调整的位置 
        PrintList(L);
        cout<<endl;
    }//至此  结束全过程 
}
int main()
{
	Sqlist L;
	InitList(L);
	cout<<"输入一组无序数列:";
	CreateList(L);
	HeapSort(L); 
	cout<<"排序结果为: "<<endl; 
	PrintList(L);
	return 0;
}
//49 38 65 97 76 13 27 49 0
//12 36 24 85 47 30 53 91 80 101 012 36 24 85 47 30 53 91 80 101 0
