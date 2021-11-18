#include <iostream>
#include <string>
#include<fstream>
#include "grade.h"
using namespace std;

int grade_num;
const char grade_url[100] = "../test/grade.txt";//grade成绩表相对路径

Grade::Grade(){
	//cout<<"Grade已构造！"<<endl;
}

Grade::~Grade(){
	//cout<<"Grade已析构！"<<endl;
}

void Grade::readFile(Grade *gra){
	fstream in;
	int i = 0,flag = 0;
	in.open(grade_url,ios::in);
	if(!in){
		ofstream fout(grade_url);//没有文件时创建文件
		if(fout){
			fout.close();
			flag = 1;
		}
	}
	if(flag != 1){
		while(!in.eof() && flag != 1){
	        in>>gra[i].id>>gra[i].name>>gra[i].subject>>gra[i].grade;//依次读取txt文件中每行的数据
	        i++;
	    }
		grade_num = i - 1;//记录管理员txt文件中行总数
	}
    in.close();
}

void Grade::showAll(Grade *gra){
	cout<<"学号  "<<"姓名  "<<"科目  "<<"成绩  "<<endl;
	for(int i = 0;i<grade_num;i++){
		cout<<gra[i].id<<" "<<gra[i].name<<" "<<gra[i].subject<<" "<<gra[i].grade<<endl;
	}
}

void Grade::showOneStudentGrade(string id,Grade *gra){
	for(int i = 0;i<grade_num;i++){
		if(id == gra[i].id){
			cout<<"学号："<<gra[i].id<<"\n姓名："<<gra[i].name<<"\n科目："<<gra[i].subject<<"\n成绩："<<gra[i].grade<<endl;
		}
	}
}

/***************************成绩管理***************************/

ManageGrade::ManageGrade(){
	//cout<<"ManageStudent已构造！"<<endl;
}

ManageGrade::~ManageGrade(){
	//cout<<"ManageStudent已析构！"<<endl;
}
void ManageGrade::insertGrade(string id,string name,string subject,int grade,Grade *gra){
	int flag = 0;//成绩是否存在标记位
	for(int i = 0;i < grade_num;i++){
		if(id == gra[i].id && subject == gra[i].subject){
			flag = 1;
		}
	}
	if(flag == 0){
		//将id name sbject grade放入stu中
	 	gra[grade_num].id = id;
		gra[grade_num].name = name;
		gra[grade_num].subject = subject;
		gra[grade_num].grade = grade;
		fstream out;
		out.open(grade_url,ios_base::out);
		for(int i = 0;i < grade_num + 1;i++){
			out<<gra[i].id<<" "<<gra[i].name<<" "<<gra[i].subject<<" "<<gra[i].grade<<"\n";
		}
		out.close();
		cout<<"学生成绩增加成功！"<<endl;
		grade_num = grade_num + 1;
		cout<<"学生成绩为："<<grade_num<<"个"<<endl;
	}else{
		cout<<"学号为"<<id<<"的学生："<<name<<"成绩存在！成绩为："<<grade<<endl;
	}
}

void ManageGrade::deleteGrade(string id,string subject,Grade *gra){
	int flag = 0;//1为成功 0为失败
	cout<<"学生成绩为："<<grade_num<<"个"<<endl;
	for(int i = 0;i<grade_num;i++){
		if(id == gra[i].id && subject == gra[i].subject){
			flag = 1;//查找成功
			for(int j = i;j<grade_num;j++){
				gra[j] = gra[j+1];//后方的一次向前移动一个
			}
		}
	}
	if(flag == 1){
		fstream out;
		out.open(grade_url,ios_base::out);
		grade_num = grade_num - 1;
		for(int i = 0;i<grade_num;i++){
			out<<gra[i].id<<" "<<gra[i].name<<" "<<gra[i].subject<<" "<<gra[i].grade<<"\n";
		}
		cout<<"学生成绩删除成功！"<<endl;
		cout<<"学生成绩为："<<grade_num<<"个"<<endl;
		out.close();
	}else{
		cout<<"学生成绩删除失败！"<<endl;
	}
}

void ManageGrade::updateGrade(string id,string name,string subject,int grade,Grade *gra){
	int flag = 0;//更新成功失败标记位
	for(int i = 0;i < grade_num;i++){
		if(id == gra[i].id && subject == gra[i].subject){//此处自动寻找科目
			gra[i].id = id;
			gra[i].name = name;
			gra[i].subject = subject;
			gra[i].grade = grade;
			flag = 1;
		}
	}
	if(flag == 1){
		fstream out;
		out.open(grade_url,ios_base::out);
		for(int i = 0;i < grade_num;i++){
			out<<gra[i].id<<" "<<gra[i].name<<" "<<gra[i].subject<<" "<<gra[i].grade<<"\n";
		}
		out.close();
		cout<<"学生成绩更新成功！"<<endl;
	}else{
		cout<<"学生成绩更新失败！"<<endl;
	}
}

void ManageGrade::sortStudentByGrade(string subject,Grade *gra,const int NUM){
	int flag = 0;//学科是否存在标记位
	Grade gra_new[NUM];//初始化一个新的对象数组，以保证排序时不会覆盖原对象数组
	int gra_new_num = 0;
	for(int n = 0;n < grade_num;n++){
		if(subject == gra[n].subject){
			gra_new[gra_new_num] = gra[n];//将gra对象数组中的subject数据循环放入gra_new中,这样不用改变gra对象数组数据位置和重新读取原txt文件
			gra_new_num++;
			flag = 1;
		}
	}
	if(flag == 1){
		//gra_new_num - 1轮比较
		for(int i = 0;i < gra_new_num - 1;i++){
			int max = i;
			for(int j = i + 1;j < gra_new_num;j++){
				if(gra_new[j].grade > gra_new[max].grade){
					max = j;
				}
			}
			//将找到的最小值和i位置所在的值进行交换
			if(i != max){
				Grade gra_temp = gra_new[i];
				gra_new[i] = gra_new[max];
				gra_new[max] = gra_temp;
			}
		}
		//循环遍历gra_new对象数组
		cout<<subject<<"学科从大到小排序为："<<endl;
		for(int i = 0;i < gra_new_num;i++){
			cout<<gra_new[i].id<<" "<<gra_new[i].name<<" "<<gra_new[i].subject<<" "<<gra_new[i].grade<<endl;
		}
	}else{
		cout<<subject<<"学科不存在！"<<endl;
	}
}

string ManageGrade::compareGrade(string id1,string id2,string name1,string name2,string subject,Grade *gra){
	string str;//用于返回比较后成绩高者
	int comp1 = -1, comp2 = -1;//使用两个int类型记住成员位置
	for(int i = 0;i < grade_num;i++){
		if(id1 == gra[i].id && subject == gra[i].subject){
			comp1 = i;
		}else if(id2 == gra[i].id && subject == gra[i].subject){
			comp2 = i;
		}
	}
	if(comp1 == -1 && comp2 != -1){
		str = "输入的学号" + id1 + "成绩不存在！";
	}else if(comp1 != -1 && comp2 == -1){
		str = "输入的学号" + id2 + "成绩不存在！";
	}else if(comp1 == comp2 == -1){
		str = "输入的两学号" + id1 + "," + id2 + "成绩均不存在！";
	}else{
		if(gra[comp1].grade > gra[comp2].grade){
			str = "成绩高者姓名为：" + name1;
		}else if(gra[comp1].grade < gra[comp2].grade){
			str = "成绩高者姓名为：" + name2;
		}else{
			str = "成绩相同";
		}
	}
	return str;
}

string ManageGrade::compareGrade(string id1,string id2,int grade1,int grade2,string subject,Grade *gra){
	string name1,name2,str;
	int flag1 = 0,flag2 = 0;//标记位
	if(grade1 > grade2){
		flag1 = 1;
	}else if(grade1 < grade2){
		flag2 = 1;
	}else{
		flag1 = flag2 = 1;
	}
	for(int i = 0;i < grade_num;i++){
		if(id1 == gra[i].id && subject == gra[i].subject && flag1 == 1){
			name1 = gra[i].name;
			str = "成绩高者姓名为：" + name1;
		}else if(id2 == gra[i].id && subject == gra[i].subject && flag2 == 1){
			name2 = gra[i].name;
			str = "成绩高者姓名为：" + name2;
		}
	}
	if(flag1 == flag2 == 1){
		str = name1 + "，" + name2 + "成绩相同";
	}
	return str;
}
	
