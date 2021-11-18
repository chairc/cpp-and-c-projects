#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

#define LET_CODE 26	//存放要输入的字母数目（可拓展可一键更改）

typedef struct{
	unsigned int weight;
	unsigned int parent,lchild,rchild;
}HTNode,*HuffmanTree;       //哈夫曼树结构

typedef char **HuffmanCode;	//哈夫曼编码存储结构

//char Let[LET_CODE]={'a','b','c','d','e','f','g'};//存放要输入的字母（可拓展）
char Let[LET_CODE]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
int Num[LET_CODE]={0};
int letternum=0;
char a[1000];

void SaveFile(){
	FILE *fp;
	char ch[100];
	fp=fopen("article.txt","w");
	scanf("%s",ch);
	fprintf(fp,"%s",ch);			
	fclose(fp);
}

void ReadFile(){
	int m=0,ch,k;
	FILE *fp;
	fp=fopen("article.txt","r");
	if(fp){                                                                                                                                                                                                         
		while(!feof(fp)){
			ch=fgetc(fp);
			if(ch==EOF){
				break;
			}
			a[m]=ch;
			k=ch-'a';
			if(Let[k]==a[m]){
				Num[k]++;
			}
			m++;    //用于控制读出的字符个数
		}
		letternum=m;
		a[m]=0;
		fclose(fp);
	}	
}

void PrintfArticle(){
	int i;
	for(i=0;i<letternum;i++){
  		printf("%c",a[i]);
	}
	printf("\n");
}

void LetterCount(){
	int i;
	for(i=0;i<LET_CODE;i++){
		printf("%c:%d\n",Let[i],Num[i]);	
	}	
}

//哈夫曼树
void CreateHuffmanTree(HuffmanTree &HT,int *w,int n){
	//*w为每个字母的权值数组Num[LET_CODE]；n为统计出来所有字母个数（叶子结点个数）
	int m,i,j,min1,min2,s1,s2;
	if(n<1){
		printf("....\n");
		return;
	}
	m=2*n-1;    //所有结点数
	HT=(HuffmanTree)malloc((m+1)*sizeof(HTNode));
	for(i=1;i<=n;i++){      //初始化数组HT[1]到HT[n]
		HT[i].weight=*w++;	
		HT[i].parent=HT[i].lchild=HT[i].rchild=0;
	}
	for(;i<=m;i++){         //初始化数组HT[n+1]到HT[m]
		HT[i].weight=0;
		HT[i].parent=HT[i].lchild=HT[i].rchild=0;
	}
	for(i=n+1;i<=m;i++){	//在HT[1]到HT[i-1]中选取parent值为0，且weight值最小的两个结点 
		min1=min2=32767;    //赋初值,32767代表最大
		s1=s2=0;
		for(j=1;j<i;j++){    //查找双亲值为0且权值最小的两个结点
			if(HT[j].parent==0){
				if(HT[j].weight<min1){
					min2=min1;      //min2记住min1
					s2=s1;          //s2记住s1
					min1=HT[j].weight;
					s1=j;           //修改最小值及位置
				}
				else if(HT[j].weight<min2){
					min2=HT[j].weight;
					s2=j;           //修改次小值及位置
				}
			}
		}
		HT[s1].parent=i;
		HT[s2].parent=i;            //修改最小值和次小值双亲值
		HT[i].weight=HT[s1].weight+HT[s2].weight;   //修改双亲结点的相关信息
		HT[i].lchild=s1;
		HT[i].rchild=s2;
	}
	printf("创建哈夫曼树成功\n");
} 

void HuffmanCoding(HuffmanTree HT,HuffmanCode &HC,int n){
	char *cd;
	int i,c,f,start;
	HC=(HuffmanCode)malloc((n+1)*sizeof(char*));    //分配编码的头指针
	cd=(char*)malloc(n*sizeof(char));   //分配给编码的临时存储空间
	cd[n-1]='\0';                       //编码结束符
	for(i=1;i<=n;i++){
		start=n-1;                      //编码结束位置
		for(c=i,f=HT[i].parent;f!=0;c=f,f=HT[f].parent){
			//从叶子到根逆向求编码
			if(HT[f].lchild==c){
				cd[--start]='0';        //c为其双亲结点的左孩子
   			}else{
			 	cd[--start]='1';        //c为其双亲结点的右孩子
			}    
		}
		HC[i]=(char*)malloc((n-start)*sizeof(char));
		strcpy(HC[i],cd+start);
	}
	free(cd);
}

void PrintfHuffmanCode(HuffmanTree HT,HuffmanCode HC){
	int i,j=1;
	for(i=0;i<LET_CODE;i++){
		if(Num[i]!=0){
			printf("%c:%s\n",Let[i],HC[j++]);
		}
	}
}

int main(){
	int switchnum=-1;
	int switchcase=0;	
	while(switchnum!=0){
		for(int i=0;i<LET_CODE;i++){
			Num[i]=0;
		}
		printf("（1）写入文章\n（2）读取文章\n（3）计算字符出现次数\n（4）设计哈夫曼编码\n（0）退出\n");
		printf("请输入选择的序号：");
		scanf("%d",&switchnum);
		switch(switchnum){
			case 1:
				printf("是否写入数据，是请输入1，不是请输入0（注意：此选项写入数据时将覆盖文件！！）\n");
				scanf("%d",&switchcase);
				if(switchcase==1){
					SaveFile();
				}
				switchcase=0; 
				break;
			case 2:
				ReadFile();
				PrintfArticle();
				break;
			case 3:
				printf("是否算字符出现次数，是请输入1，不是请输入0\n");
				scanf("%d",&switchcase);
				if(switchcase==1){
					ReadFile();
					LetterCount();
				}
				switchcase=0; 	
				break;
			case 4:
				printf("是否设计哈夫曼编码，是请输入1，不是请输入0\n");
				scanf("%d",&switchcase);
				if(switchcase==1){
					HuffmanTree HT;
					HuffmanCode HC;
					ReadFile();
					LetterCount();
					int i,n=0;
					int Let[LET_CODE];
					printf("正在创建哈夫曼树....\n");
					for(i=0;i<LET_CODE;i++){
						 Let[n]=Num[i];
						 n++;
					}
					CreateHuffmanTree(HT,Let,n);
					HuffmanCoding(HT,HC,n);
					PrintfHuffmanCode(HT,HC);
				}
				switchcase=0; 
				break;
			case 0:
				exit(0);
			default:
				printf("输入序号有误！请重新输入！"); 
		}
	}
	
	return 0;
}
