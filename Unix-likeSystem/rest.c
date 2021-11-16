/*
*   @author:chairc
*   @github:chairc
*   @time:2020-1-22 03:14:03
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define num 10
#define INC 10
#define sizeofNum 1000
#define filenameLength 100

typedef struct{
	char buf[100];
}Buf;

typedef struct{
	char filename[filenameLength];
	char lasttime[40];
	char createtime[40];
}File;

File ind[20];

int filenum=0,bufLength=100,indexnum=0; 
char *argv[10];
int argc;

void ReadFileIndex(){
	FILE *in;
	int n=0,i;
	in=fopen("index.txt","r");
	if(!in){
		printf("文件异常！\n");
		return;
	}
	while(!feof(in)){
		fscanf(in,"%s %s %s\n",ind[n].filename,ind[n].createtime,ind[n].lasttime);
		n++;
	}
	indexnum=n;
	fclose(in);
}

void PrintfFileIndex(){
	int i;
	for(i=0;i<indexnum;i++){
		printf("%s %s %s\n",ind[i].filename,ind[i].createtime,ind[i].lasttime);
	}
}

void WriteFileIndex(const char *filename,int flag){
	FILE *in;
	char lasttime[30],createtime[30],ch[20];
	int i;

	time_t timep;
	struct tm *p;
	time (&timep);
	p=gmtime(&timep);
	sprintf(ch,"%d-%d-%d/%d:%d:%d",1900+p->tm_year,1+p->tm_mon,p->tm_mday,8+p->tm_hour,p->tm_min,p->tm_sec);
	
	ReadFileIndex();
	//printf("filename:%s;flag:%d;time:%s\n",filename,flag,ch);
	if(flag==1){
	//printf("flag=1\n");
  	char *name=(char*)malloc(strlen(filename)+INC);
		for(i=0;i<indexnum;i++){
			strcpy(name,ind[i].filename);
			if(strcmp(name,filename)==0){
				//printf("i=%d;name=%s;filename=%s\n",i,name,filename);
				in=fopen("index.txt","r+");
				if(!in){
					printf("文件异常！\n");
					return;
				}
				//printf("ch=%s\n",ch);
				strcpy(ind[i].lasttime,ch);
				//printf("lasttime=%s\n",ind[i].lasttime);
				fprintf(in,"%s %s %s",ind[i].filename,ind[i].createtime,ind[i].lasttime);
				fclose(in);
			}
		}
		in=fopen("index.txt","w");
		if(!in){
			printf("文件异常！\n");
			return;
		}
		for(i=0;i<indexnum;i++){
			fprintf(in,"%s %s %s\n",ind[i].filename,ind[i].createtime,ind[i].lasttime);
		}
	}else if(flag==0){
		in=fopen("index.txt","a+");
		if(!in){
			printf("文件异常！\n");
			return;
		}
		fprintf(in,"%s %s %s\n",filename,ch,ch);
	}
	fclose(in);
}

void CreateFile(){
	char filename[filenameLength],extendedname[20];
	int flag=0;
	FILE *fp;	
	//printf("请输入创建的文件名：");
	scanf("%s",filename);
	//printf("请输入创建的拓展名：");
	//scanf("%s",extendedname);
	//char *namecat=(char*)malloc(strlen(filename)+strlen(extendedname)+INC);
	//sprintf(namecat,"%s.%s",filename,extendedname);
	//fp=fopen(namecat,"w");
	fp=fopen(filename,"w");
	if(!fp){
		printf("文件创建异常！\n");
		return;
	}
	fclose(fp);
	//printf("文件%s.%s创建成功！\n",filename,extendedname);
	//WriteFileIndex(namecat,flag);
	printf("文件%s创建成功！\n",filename);
	WriteFileIndex(filename,flag);
}

void DeleteFile(){
	ReadFileIndex();
	FILE *in;
	int i,j;
	char filename[filenameLength],extendedname[20];
	//printf("请输入删除的文件名：");
	scanf("%s",filename);
	if(remove(filename)==0){
		printf("文件%s删除成功！\n",filename);
		char *name=(char*)malloc(strlen(filename)+INC);
		for(i=0;i<indexnum;i++){
			strcpy(name,ind[i].filename);
			if(strcmp(name,filename)==0){
				//printf("%s;%s\n",name,filename);
				for(j=i;j<indexnum;j++){
					ind[j]=ind[j+1];
				}
				break;
			}
		}
		in=fopen("index.txt","w");
		if(!in){
			printf("文件异常！\n");
			return;
		}
		for(i=0;i<indexnum-1;i++){
			fprintf(in,"%s %s %s\n",ind[i].filename,ind[i].createtime,ind[i].lasttime);
		}
		indexnum=indexnum-1;
		fclose(in);
	}else{
		printf("文件%s删除失败！\n",filename);
	}
}

void ReadFile(){
	char filename[filenameLength];
 	Buf a[num];
	int n=0,i;
	FILE *fp;
	//printf("请输入读取的文件名：");
	scanf("%s",filename);
	fp=fopen(filename,"r");
	if(!fp){
		printf("文件异常！\n");
		return;
	}
	while(!feof(fp)){
		fscanf(fp,"%s\n",a[n].buf);
	   	n++;	   
	}
	filenum=n;
	for(i=0;i<filenum;i++){
		printf("%s\n",a[i].buf);
	}	
	fclose(fp);
}

void WriteFile(){
	char filename[filenameLength];
 	Buf a[num];
	int i,flag=1;
	FILE *fp;
	//printf("请输入写入的文件名：");
	scanf("%s",filename);
	//printf("请输入写入的文件条数：");
	scanf("%d",&filenum);
	fp=fopen(filename,"r+");
	if(!fp){
		printf("文件异常！\n");
		return;
	}
	for(i=0;i<filenum;i++){
		scanf("%s",a[i].buf);
		fprintf(fp,"%s\n",a[i].buf);
	}
	fclose(fp);
	WriteFileIndex(filename,flag);
}

void ReadFile1(){
	char filename[filenameLength],buf[100];
	int n=0,ch,i;
	FILE *fp;
	//printf("请输入读取的文件名：");
	scanf("%s",filename);
	fp=fopen(filename,"r");	
	if(!fp){
		printf("文件异常！\n");
		return;
	}	
	fread(buf,1,bufLength+1,fp);
	printf("%s\n",buf);
	fclose(fp);
}

void WriteFile1(){
	char filename[filenameLength],buf[100];
	int i,flag=1;
	FILE *fp;	
	//printf("请输入写入的文件名：");
	scanf("%s",filename);
	fp=fopen(filename,"r+");
	if(!fp){
		printf("文件异常！\n");
		return;
	}
	scanf("%s",buf);
	fwrite(buf,1,strlen(buf)+1,fp);
	bufLength=strlen(buf);
	fclose(fp);
	WriteFileIndex(filename,flag);
}

void CopyFile(){
	ReadFileIndex();
	int flag=0,i,j;
	char copyname[filenameLength],pastename[filenameLength];
	//printf("请输入你要复制的文件名：");
	scanf("%s",copyname);
	//printf("请输入你要粘贴后的文件名：");
	scanf("%s",pastename);

	FILE *fpcopy;  // 指向要复制的文件
	FILE *fppaste;  // 指向复制后的文件
	FILE *in;
	int bufferLen=1024*4;  // 缓冲区长度
	char *buffer=(char*)malloc(bufferLen);  // 开辟缓存
	int readCount;  // 实际读取的字节数
	if((fpcopy=fopen(copyname,"rb"))==NULL||(fppaste=fopen(pastename,"wb"))==NULL){
 		printf("复制文件异常！\n");
		return;
	}
	// 不断从fileRead读取内容，放在缓冲区，再将缓冲区的内容写入fileWrite
	while((readCount=fread(buffer,1,bufferLen,fpcopy))>0){
		fwrite(buffer,readCount,1,fppaste);
	}
	free(buffer);
	fclose(fpcopy);
	fclose(fppaste);
	WriteFileIndex(pastename,flag);
	
	return;
}

void CutFile(){
	ReadFileIndex();
	int flag=0,i,j;
	char copyname[filenameLength],pastename[filenameLength];
	//printf("请输入你要复制的文件名：");
	scanf("%s",copyname);
	//printf("请输入你要粘贴后的文件名：");
	scanf("%s",pastename);

	FILE *fpcopy;  // 指向要复制的文件
	FILE *fppaste;  // 指向复制后的文件
	FILE *in;
	int bufferLen=1024*4;  // 缓冲区长度
	char *buffer=(char*)malloc(bufferLen);  // 开辟缓存
	int readCount;  // 实际读取的字节数
	if((fpcopy=fopen(copyname,"rb"))==NULL||(fppaste=fopen(pastename,"wb"))==NULL){
 		printf("复制文件异常！\n");
		return;
	}
	// 不断从fileRead读取内容，放在缓冲区，再将缓冲区的内容写入fileWrite
	while((readCount=fread(buffer,1,bufferLen,fpcopy))>0){
		fwrite(buffer,readCount,1,fppaste);
	}
	free(buffer);
	fclose(fpcopy);
	fclose(fppaste);

	if(remove(copyname)==0){
		printf("文件%s删除成功！\n",copyname);
		char *name=(char*)malloc(strlen(copyname)+INC);
		for(i=0;i<indexnum;i++){
			strcpy(name,ind[i].filename);
			if(strcmp(name,copyname)==0){
				//printf("%s;%s\n",name,copyname);
				for(j=i;j<indexnum;j++){
					ind[j]=ind[j+1];
				}
				break;
			}
		}
		in=fopen("index.txt","w");
		if(!in){
			printf("文件异常！\n");
			return;
		}
		for(i=0;i<indexnum-1;i++){
			fprintf(in,"%s %s %s\n",ind[i].filename,ind[i].createtime,ind[i].lasttime);
		}
		indexnum=indexnum-1;
		fclose(in);
	}else{
		printf("文件%s删除失败！\n",copyname);
	}
	WriteFileIndex(pastename,flag);

	return;
}

void Help(){
	printf("指令: \n\
	ll     ---  显示文件目录\n\
	crf    ---  创建文件\n\
	del    ---  删除文件\n\
	read   ---  读文件\n\
	write  ---  写文件\n\
	reads  ---  多条读文件#测试#\n\
	writes ---  多条写文件#测试#\n\
	copy   ---  复制文件\n\
	cut    ---  剪切文件\n\
	help   ---  帮助\n\
	helpall---  所有详细帮助\n\
	man    ---  指令帮助\n\
	exitf  ---  退出\n\
	详细指令请输入helpall\n");
}

void HelpAll(){
	printf("指令: \n\
	=====================\n\
	ll     ---  显示文件目录\n\
	=====================\n\
	crf    ---  创建文件\n\
	使用方法：crf + 文件名\n\
	=====================\n\
	del    ---  删除文件\n\
	使用方法：del + 文件名\n\
	=====================\n\
	read   ---  读文件\n\
	使用方法：read + 文件名\n\
	=====================\n\
	write  ---  写文件\n\
	使用方法：write + 文件名\n\
	=====================\n\
	reads  ---  多条读文件#测试#\n\
	使用方法：reads + 文件名\n\
	=====================\n\
	writes ---  多条写文件#测试#\n\
	使用方法：writes + 文件名 + 条数\n\
	=====================\n\
	copy   ---  复制文件\n\
	使用方法：copy + 新文件名 + 旧文件名\n\
	=====================\n\
	cut    ---   剪切文件\n\
	使用方法：cut + 新文件名 + 旧文件名\n\
	=====================\n\
	help   ---  帮助\n\
	=====================\n\
	helpall---  所有详细帮助\n\
	=====================\n\
	man    ---  指令帮助\n\
	使用方法：man + 指令\n\
	=====================\n\
	exitf  ---  退出\n\
	=====================\n");
}

void Man(){
	char name[filenameLength];
	scanf("%s",name);
	switch(Analyse(name)){
		case 0:
			printf("\n\
			=====================\n\
			ll     ---  显示文件目录\n\
			使用方法：直接输入\n\
			=====================\n");
			break;
		case 1:
			printf("\n\
			=====================\n\
			crf    ---  创建文件\n\
			使用方法：crf + 文件名\n\
			=====================\n");
			break;
		case 2:
			printf("\n\
			=====================\n\
			del    ---  删除文件\n\
			使用方法：del + 文件名\n\
			=====================\n");
			break;
		case 3:
			printf("\n\
			=====================\n\
			read   ---  读文件\n\
			使用方法：read + 文件名\n\
			=====================\n");
			break;
		case 4:
			printf("\n\
			=====================\n\
			write  ---  写文件\n\
			使用方法：write + 文件名\n\
			=====================\n");
			break;
		case 5:
			printf("\n\
			=====================\n\
			reads  ---  多条读文件#测试#\n\
			使用方法：reads + 文件名\n\
			=====================\n");
			break;
		case 6:
			printf("\n\
			=====================\n\
			writes ---  多条写文件#测试#\n\
			使用方法：writes + 文件名 + 条数\n\
			=====================\n");
			break;
		case 7:
			printf("\n\
			=====================\n\
			copy   ---  复制文件\n\
			使用方法：copy + 新文件名 + 旧文件名\n\
			=====================\n");
			break;
		case 8:
        	printf("\n\
			=====================\n\
			cut   ---   剪切文件\n\
			使用方法：cut + 新文件名 + 旧文件名\n\
			=====================\n");
        	break;
		case 9:
			printf("\n\
			=====================\n\
			help   ---  帮助\n\
			=====================\n");
			break;
		case 10:
			printf("\n\
			=====================\n\
			helpall   ---  所有详细帮助\n\
			=====================\n");
			break;
		case 11:
			printf("\n\
			=====================\n\
			man    ---  指令帮助\n\
			使用方法：man + 指令\n\
			=====================\n");
			break;
		case 12:
			printf("\n\
			=====================\n\
			exitf  ---  退出\n\
			=====================\n");
			break;
	}
	return;
}

int Analyse(char *str){
	int i;
	char temp[20];
	char *p_char;
	char *syscmd[]={"ll","crf","del","read","write","reads","writes","copy","cut","help","helpall","man","exitf"};
	argc=0;
	for(i=0,p_char=str;*p_char!='\0';p_char++){
		if(*p_char!=' '){
			while(*p_char!=' '&&(*p_char!='\0')){   //依次读入输进来的数
				temp[i++] = *p_char++;
			}
			argv[argc]=(char*)malloc(i+1);
			strncpy(argv[argc],temp,i);     //把temp所指向的字符串中以temp地址开始的前i个字节复制到argv[argc]所指的数组中，并返回被复制后的argv[argc]。
			argv[argc][i] ='\0';
			argc++;
			i=0;
			if(*p_char=='\0'){
				break;
			}
		}
	}
	if(argc!=0){
		for(i=0;(i<13)&&strcmp(argv[0],syscmd[i]);i++);
			return i;
	}
	else{
		return 13;
	}
	return 0;
}

int main(){
	char cmd[20];
	while(1){
		printf("root@localhost:#");
		scanf("%s",cmd);
		ReadFileIndex();
		switch(Analyse(cmd)){
			case 0:
				PrintfFileIndex();
				break;
			case 1:
				CreateFile();
				break;
			case 2:
				DeleteFile();
				break;
			case 3:
				ReadFile1();
				break;
			case 4:
				WriteFile1();
				break;
			case 5:
				ReadFile();
				break;
			case 6:
				WriteFile();
				break;
			case 7:
				CopyFile();
				break;
            case 8:
            	CutFile();
            	break;
			case 9:
				Help();
				break;
			case 10:
				HelpAll();
				break;
			case 11:
				Man();
				break;
			case 12:
				exit(0);
		}
	}
	return 0;
}
