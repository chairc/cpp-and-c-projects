#include <stdio.h>
#include <stdlib.h>

#define StackInitSize 100
#define StackIncrement 10

typedef struct{
	int *base;
	int top;
	int stacksize;
}SqStack;

typedef struct BitNode{
	char data;
	BitNode* lchild;
    BitNode* rchild;
}BitNode,*Bitree;

/*树栈ADT*/
typedef struct{
    Bitree *base;
    int top;
    int stacksize;
}TreeStack;

//算符间的优先关系
char Con[7][7]={{'>','>','<','<','<','>','>'},{'>','>','<','<','<','>','>'},{'>','>','>','>','<','>','>'},{'>','>','>','>','<','>','>'},{'<','<','<','<','<','=',' '},{'>','>','>','>',' ','>','>'},{'<','<','<','<','<',' ','='}};


void InitStack(SqStack &S){
	S.base=(int*)malloc(StackInitSize*sizeof(int));
	if(!S.base){
		return;
	}
	S.top=0;
	S.stacksize=StackInitSize;
}

int StackEmpty(SqStack &S){
	if(S.top==0){
		return 1;
	}
	return 0;
}

int StackLength(SqStack S){
	return S.top;
}

void Push(SqStack &S,int e){
	if(S.top>=S.stacksize){
		S.base=(int*)realloc(S.base,(S.stacksize+StackIncrement)*sizeof(int));
		if(!S.base){
			return;
		}
		S.stacksize+=StackIncrement;
	}
	S.base[S.top++]=e;
}

void Pop(SqStack &S,int &e){
	if(S.top==0){
		return;
	}
	e=S.base[--S.top];
}

int GetTop(SqStack S){
	int e;
	if(S.top==0){
		return 0;
	}
	e=S.base[S.top-1];
	return e;
}

/*树类型栈*/
void TreeInitStack(TreeStack &S){
	S.base=(Bitree*)malloc(StackInitSize*sizeof(Bitree));
    S.top=0;
    S.stacksize=StackInitSize;
}

Bitree TreeGetTop(TreeStack S){
	if(S.top==0) return 0;
	return S.base[S.top-1];
}

Bitree Pop_t(TreeStack &S,Bitree &e){
	if(S.top==0){
		return 0;
	}
	e=S.base[--S.top];
	return e;
}

void Push_t(TreeStack &S,Bitree e)
{
    if(S.top+1>S.stacksize)
    {
        S.base=(Bitree*)realloc(S.base,(S.stacksize+StackIncrement)*sizeof(Bitree));
        S.stacksize+=StackIncrement;
    }
    S.base[S.top++]=e;
}


//中缀表达式
int Compare(char theta1,char theta2){
	char op[7]={'+','-','*','/','(',')','#'};
	int i,j;
	int t1,t2;
	for(i=0;i<7;i++){
		if(theta1==op[i]){
			t1=i;
			break;
		}
	}
	for(j=0;j<7;j++){
		if(theta2==op[j]){
			t2=j;
			break;
		}
	}
	return Con[t1][t2];
} 

int Operate(int a,char theta,int b){
	switch(theta){
		case '+':
			return a+b;
		case '-':
			return a-b;
		case '*':
			return a*b;
		case '/':
			if(b!=0){
				return a/b;
			}else{
				printf("0不能为除数！");
				return 0;
			}
	}
}

//计算中缀表达式
int EvaluateExpression(char *str){
	//OPTR为算数符号栈，OPND为操作数栈 
	SqStack OPTR,OPND;
	char *p;
	int num=0,ch,a,b,theta;
	p=str;
	InitStack(OPTR);
	InitStack(OPND);
	Push(OPTR,*p);      //'#'入栈
	p++;
	while(*p!='#'||GetTop(OPTR)!='#'){
		if(*p>='0'&&*p<='9'){
			num=0;      //p指向为操作数
			while(*p!='#'&&*p>='0'&&*p<='9'){
				num=num*10+*p-'0';
				p++;
			}
			Push(OPND,num);
		}else{
			switch(Compare(GetTop(OPTR),(int)*p)){
				case '<':
					Push(OPTR,*p);
					p++;
					break;
				case '=':
					Pop(OPTR,ch);
					p++;
					break;
				case '>':
					Pop(OPND,b);
					Pop(OPND,a);
					Pop(OPTR,theta);
					Push(OPND,Operate(a,theta,b));
					break;
			}
		}
	}
	return GetTop(OPND);
}

//创建树
void CreateTree(char *str,Bitree &bt){
	char *p;
	Bitree m,n;
	int num,a,b,ch,theta;
	p=str;
	SqStack OPTR;//运算符
	TreeStack OPND;
	InitStack(OPTR);
	TreeInitStack(OPND);
	Push(OPTR,*p);      //'#'入栈
	p++;
	while(*p!='#'||GetTop(OPTR)!='#'){
		if(*p>='0'&&*p<='9'){
			num=0;      //p指向为操作数
			while(*p!='#'&&*p>='0'&&*p<='9'){
				num=num*10+(*p-'0');                //由于一次只能处理一个数字，这里是将超过一位数的值加起来
				p++;
			}
			bt=(Bitree)malloc(sizeof(BitNode));     //申请结点
			bt->data=num;                           //将数放入结点data中
			bt->lchild=NULL;
			bt->rchild=NULL;
			Push_t(OPND,bt);                        //将结点压入栈中
		}
		switch(Compare(GetTop(OPTR),*p)){           //优先级比较，符号栈栈顶元素和输入进的数比较
			case '<':
				Push(OPTR,*p);
				p++;
				break;
			case '=':
				Pop(OPTR,ch);
				p++;
				break;
			case '>':
				    Pop_t(OPND,m);                  //遇到优先级大的符号时，取出操作数栈的最顶上两个
					Pop_t(OPND,n);
					Pop(OPTR,theta);
					bt=(Bitree)malloc(sizeof(BitNode));
					bt->data=theta;
					bt->lchild=n;                   //后取出的放左子树，先取出的放右子树
					bt->rchild=m;
					Push_t(OPND,bt);
					break;
		}
	}
	bt=TreeGetTop(OPND);
	printf("创建二叉链表成功！\n");
}

//先序遍历递归
void PreOrderTraverse(Bitree bt){
	if(bt){
		if(bt->lchild||bt->rchild)
			printf("%c ",bt->data);
		else
			printf("%d ",bt->data);
		PreOrderTraverse(bt->lchild);
		PreOrderTraverse(bt->rchild);
	}
}
//后序遍历递归
void PostOrderTraverse(Bitree bt){
	if(bt){
		PostOrderTraverse(bt->lchild);
		PostOrderTraverse(bt->rchild);
		if(bt->lchild||bt->rchild)
			printf("%c ",bt->data);
		else
			printf("%d ",bt->data);
	}
}

int main(){
	char ch[100];
	int result;
	Bitree bt;
	
	printf("输入一个中缀表达式：");
	gets(ch);
	result=EvaluateExpression(ch);
	printf("%d\n",result);
	CreateTree(ch,bt);
	printf("前缀表达式为：");
	PreOrderTraverse(bt);
	printf("\n");
	printf("后缀表达式为：");
	PostOrderTraverse(bt);
	
	return 0;
}
