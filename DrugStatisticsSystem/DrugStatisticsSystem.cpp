#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ListInitSize 20

typedef struct{
	//int Med_rank;
	int Med_id;
	char Med_name[30];
	float Med_price;
	float Med_sell_num;
	float Med_sell_price;
}Medicine;

typedef struct{
	Medicine Med[20];
	//int length;
}SqList;

int mednum=0;

void ReadMedInfo(SqList &L){
	int i,n=1;
	FILE *fp;
	fp=fopen("medicine.txt","r");
	printf("药品编号 药品名称 药品单价 药品销售数量 药品销售额为：\n");
	while(!feof(fp)){
		fscanf(fp,"%d %s %f %f %f\n",&L.Med[n].Med_id,L.Med[n].Med_name,&L.Med[n].Med_price,&L.Med[n].Med_sell_num,&L.Med[n].Med_sell_price);
		n++;
	}
	mednum=n-1;
	printf("已读取%d条数据\n",n-1);
	fclose(fp);
}

void SaveMedInfo(SqList &L){
	int i;
	FILE *fp;
	fp=fopen("medicine.txt","w");
	printf("请输入药品个数：");
	scanf("%d",&mednum);
	printf("请依次输入药品编号 药品名称 药品单价 药品销售数量：\n");
	for(i=1;i<=mednum;i++){
		scanf("%d %s %f %f",&L.Med[i].Med_id,L.Med[i].Med_name,&L.Med[i].Med_price,&L.Med[i].Med_sell_num);
		L.Med[i].Med_sell_price=L.Med[i].Med_price*L.Med[i].Med_sell_num;
		//printf("%f",L.Med[i].Med_sell_price);
		fprintf(fp,"%d %s %f %f %f\n",L.Med[i].Med_id,L.Med[i].Med_name,L.Med[i].Med_price,L.Med[i].Med_sell_num,L.Med[i].Med_sell_price);
	}
	fclose(fp);
}

void SearchMedOneOfInfo(SqList &L,int switchcase){
	int i,j;
	FILE *fp;
	int updateid;
	
	printf("请选择需要更新的药品编号：");
	scanf("%d",&updateid);
	for(i=1;i<=mednum;i++){
		if(L.Med[i].Med_id==updateid){
			fp=fopen("medicine.txt","w");
			if(switchcase==1){
				printf("请输入要更新的单价：");
				scanf("%f",&L.Med[i].Med_price);
				L.Med[i].Med_sell_price=L.Med[i].Med_price*L.Med[i].Med_sell_num;
			}else if(switchcase==2){
				float addnum;
				printf("请输入要增加多少销售数量：");
				scanf("%f",&addnum);
				L.Med[i].Med_sell_num+=addnum;
				L.Med[i].Med_sell_price=L.Med[i].Med_price*L.Med[i].Med_sell_num;
			}else{
				printf("选择有误！重新选择！");
				return;
			}
			for(j=1;j<=mednum;j++){
				fprintf(fp,"%d %s %f %f %f\n",L.Med[j].Med_id,L.Med[j].Med_name,L.Med[j].Med_price,L.Med[j].Med_sell_num,L.Med[j].Med_sell_price);
			}
			fclose(fp);
			return;
		}
	}
	return;
}

void PrintfMedInfo(SqList L){
	int i,rank=1;
	for(i=1;i<=mednum;i++){
		printf("%d:%d %s %.2f %.2f %.2f\n",rank,L.Med[i].Med_id,L.Med[i].Med_name,L.Med[i].Med_price,L.Med[i].Med_sell_num,L.Med[i].Med_sell_price);
		rank++;
	}
}

void PriceSort(SqList &L){
	int flag=1,i,j;
	for(i=1;i<mednum;i++){
		flag=0;
		for(j=1;j<=mednum-i;j++){
			if(L.Med[j].Med_price<L.Med[j+1].Med_price){
				L.Med[0]=L.Med[j];
				L.Med[j]=L.Med[j+1];
				L.Med[j+1]=L.Med[0];
				flag=1;
			}
		}
	}
} 

void SellNumAjust(SqList &L,int s,int m){
	int j;
	L.Med[0]=L.Med[s];
	for(j=2*s;j<=m;j*=2){
		if(j<m&&L.Med[j].Med_sell_num>L.Med[j+1].Med_sell_num){
			j++;
		}
		if(L.Med[0].Med_sell_num<=L.Med[j].Med_sell_num){
			break;
		}
		L.Med[s]=L.Med[j];
		s=j;
	}
	L.Med[s]=L.Med[0];		//插入操作 
}

void SellNumSort(SqList &L){
	int i;
	Medicine temp;
	for(i=mednum/2;i>0;i--){	//建立初始堆 
		SellNumAjust(L,i,mednum);
	}
	for(i=mednum;i>1;i--){	//堆的输出和调整 
		temp=L.Med[1];		//堆顶与最后一个记录交换 
		L.Med[1]=L.Med[i];
		L.Med[i]=temp;
		SellNumAjust(L,1,i-1);	//将L.Med[1]到L.Med[i-1]重新调整为堆 
	}
}

void SellPriceSort(SqList &L){
	int i,j;
	for(i=2;i<=mednum;i++){
		if(L.Med[i].Med_sell_price>L.Med[i-1].Med_sell_price){
			L.Med[0]=L.Med[i];  //第i位置作为哨兵放入0位置中
			L.Med[i]=L.Med[i-1];
			for(j=i-2;L.Med[0].Med_sell_price>L.Med[j].Med_sell_price;j--){
				L.Med[j+1]=L.Med[j];
			}
			L.Med[j+1]=L.Med[0];	//插入记录
		}
	}
}

int main(){
	SqList L;
	int switchnum=-1;
	int switchcase=0;	
	while(switchnum!=0){
		printf("欢迎来到药品销售统计系统：\n（1）创建销售信息\n（2）读取销售信息\n（3）排序销售信息\n（4）更新销售信息\n（0）退出\n");
		printf("请输入选择的序号：");
		scanf("%d",&switchnum);
		switch(switchnum){
			case 1:
				printf("是否创建数据，是请输入1，不是请输入0（注意：此选项写入数据时将覆盖文件！！）\n");
				scanf("%d",&switchcase);
				if(switchcase==1){
				SaveMedInfo(L);
				PrintfMedInfo(L);
				}
				switchcase=0; 
				break;
			case 2:
				ReadMedInfo(L);
				PrintfMedInfo(L);
				break;
			case 3:
				ReadMedInfo(L);
				printf("请选择排序方式：（1）按单价排序（2）按销售数量排序（3）按销售额排序（0）返回上一步\n");
				scanf("%d",&switchcase);
				if(switchcase!=0){
					if(switchcase==1){
						PriceSort(L);
						PrintfMedInfo(L);
					}else if(switchcase==2){
						SellNumSort(L);
						PrintfMedInfo(L);
					}else if(switchcase==3){
						SellPriceSort(L);
						PrintfMedInfo(L);
					}
				}			
				switchcase=0; 	
				break;
			case 4:
				ReadMedInfo(L);
				printf("选择更新的类型：（1）单价更新（2）销售数量更新（0）返回上一步\n");
				scanf("%d",&switchcase);
				if(switchcase!=0){
					SearchMedOneOfInfo(L,switchcase);
				}
				break;
			case 0:
				exit(0);
			default:
				printf("输入序号有误！请重新输入！"); 
		}
	}

	return 0;
}
