#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ListInitSize 20

typedef struct{
	int id;
	char name[20];
	short int age;
	char phone[20];
	char native[20];
}Student;

typedef struct{
	Student Stu[20];
	//int length;
}SqList;

int stdnum=0;   //用于读取数据时记录总数的计时器

void ReadStuInfo(SqList &L){
	int i,n=0;
	FILE *fp;
	fp=fopen("student.txt","r");
	printf("学生学号 姓名 年龄 电话 籍贯为：\n");
	while(!feof(fp)){
		fscanf(fp,"%d %s %d %s %s\n",&L.Stu[n].id,L.Stu[n].name,&L.Stu[n].age,L.Stu[n].phone,L.Stu[n].native);
		n++;
	}
	stdnum=n;
	fclose(fp);
}

void SaveStuInfo(SqList &L){
	int i;
	FILE *fp;
	fp=fopen("student.txt","w");
	printf("请输入学生个数：");
	scanf("%d",&stdnum);
	printf("请依次输入学生学号 姓名 年龄 电话 籍贯：\n");
	for(i=0;i<stdnum;i++){
		scanf("%d %s %d %s %s",&L.Stu[i].id,L.Stu[i].name,&L.Stu[i].age,L.Stu[i].phone,L.Stu[i].native);
		fprintf(fp,"%d %s %d %s %s\n",L.Stu[i].id,L.Stu[i].name,L.Stu[i].age,L.Stu[i].phone,L.Stu[i].native);
	}
	fclose(fp);
}

void InsertStuInfo(SqList &L){
	int addstdnum,i;
	FILE *fp;
	fp=fopen("student.txt","a");
	printf("请输入增加学生个数：");
	scanf("%d",&addstdnum);
	for(i=0;i<addstdnum;i++){
		scanf("%d %s %d %s %s",&L.Stu[i].id,L.Stu[i].name,&L.Stu[i].age,L.Stu[i].phone,L.Stu[i].native);
		fprintf(fp,"%d %s %d %s %s\n",L.Stu[i].id,L.Stu[i].name,L.Stu[i].age,L.Stu[i].phone,L.Stu[i].native);
	}
	fclose(fp);
}

void DeleteStuInfo(SqList &L){
	int searchid,i,j;
	printf("请输入删除学生信息的学号：\n");
	scanf("%d",&searchid);
	for(i=0;i<stdnum;i++){
		if(L.Stu[i].id==searchid){
			for(j=i;j<stdnum;j++){
//				L.Stu[j].id=L.Stu[j+1].id;
//				strcpy(L.Stu[j].name,L.Stu[j+1].name);
//				L.Stu[j].age=L.Stu[j+1].age;
//				strcpy(L.Stu[j].phone,L.Stu[j+1].phone);
//				strcpy(L.Stu[j].native,L.Stu[j+1].native);
				L.Stu[j]=L.Stu[j+1];
			}
		}
	}
	FILE *fp;
	fp=fopen("student.txt","w");
	for(i=0;i<stdnum-1;i++){
		fprintf(fp,"%d %s %d %s %s\n",L.Stu[i].id,L.Stu[i].name,L.Stu[i].age,L.Stu[i].phone,L.Stu[i].native);
	}
	stdnum=stdnum-1;
	fclose(fp);
}

void PrintfStuInfo(SqList L){
	int i;
	for(i=0;i<stdnum;i++){
		printf("%d %s %d %s %s\n",L.Stu[i].id,L.Stu[i].name,L.Stu[i].age,L.Stu[i].phone,L.Stu[i].native);
	}
}

int main() {
	SqList L;
	int switchnum=-1;
	int switchcase=0;	
	while(switchnum!=0){
		printf("欢迎来到班级管理系统：\n（1）写入学生信息\n（2）读取学生信息\n（3）插入同学信息\n（4）删除同学信息\n（0）退出\n");
		printf("请输入选择的序号：");
		scanf("%d",&switchnum);
		switch(switchnum){
			case 1:
				printf("是否写入数据，是请输入1，不是请输入0（注意：此选项写入数据时将覆盖文件！！）\n");
				scanf("%d",&switchcase);
				if(switchcase==1){
					SaveStuInfo(L);
					PrintfStuInfo(L);
				}
				switchcase=0; 
				break;
			case 2:
				ReadStuInfo(L);
				PrintfStuInfo(L);
				break;
			case 3:
				printf("是否插入数据，是请输入1，不是请输入0\n");
				scanf("%d",&switchcase);
				if(switchcase==1){
					ReadStuInfo(L);
					InsertStuInfo(L);
				}
				switchcase=0; 	
				break;
			case 4:
				printf("是否删除数据，是请输入1，不是请输入0\n");
				scanf("%d",&switchcase);
				if(switchcase==1){
					ReadStuInfo(L);
					DeleteStuInfo(L);
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
