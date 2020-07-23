#include <iostream>
#include <string>
#include<fstream>
#include "student.h"
using namespace std;

int student_num;
const char student_url[100] = "../test/student.txt";//student学生表相对路径

Student::Student(){
	//cout<<"Student已构造！"<<endl;
}

Student::~Student(){
	//cout<<"Student已析构！"<<endl;
}

void Student::readFile(Student *stu){
	fstream in;
	int i = 0,flag = 0;
	in.open(student_url,ios::in);
	if(!in){
		ofstream fout(student_url);//没有文件时创建文件
		if(fout){
			fout.close();
			flag = 1;
		}
	}
	if(flag != 1){
		while(!in.eof() && flag != 1){
	        in>>stu[i].id>>stu[i].name>>stu[i].sex>>stu[i].age;//依次读取txt文件中每行的数据
	        i++;
	    }
	    student_num = i - 1;//记录管理员txt文件中行总数（空格也算一行所以要-1）
	}
    in.close();
}

void Student::showAll(Student *stu){
	cout<<"学号  "<<"姓名  "<<"性别  "<<"年龄  "<<endl;
	for(int i = 0;i < student_num;i++){
		cout<<stu[i].id<<" "<<stu[i].name<<" "<<stu[i].sex<<" "<<stu[i].age<<endl;
	}
	cout<<"学生为："<<student_num<<"个"<<endl;
}

void Student::showOneStudent(string id,Student *stu){
	for(int i = 0;i < student_num;i++){
		if(id == stu[i].id){
			cout<<"学号："<<stu[i].id<<"\n姓名："<<stu[i].name<<"\n性别："<<stu[i].sex<<"\n年龄："<<stu[i].age<<endl;
		}
	}
}


/***************************学生管理***************************/

ManageStudent::ManageStudent(){
	//cout<<"ManageStudent已构造！"<<endl;
}

ManageStudent::~ManageStudent(){
	//cout<<"ManageStudent已析构！"<<endl;
}
void ManageStudent::insertStudent(string id,string name,string sex,int age,Student *stu){
	//将学生信息放入stu中
	int flag = 0;//学生是否存在标记位
	for(int i = 0;i < student_num;i++){
		if(id == stu[i].id){
			flag = 1;
		}
	}
	if(flag == 0){
		stu[student_num].id = id;
		stu[student_num].name = name;
		stu[student_num].sex = sex;
		stu[student_num].age = age;
		fstream out;
		out.open(student_url,ios_base::out);
		for(int i = 0;i < student_num + 1;i++){
			out<<stu[i].id<<" "<<stu[i].name<<" "<<stu[i].sex<<" "<<stu[i].age<<"\n";
		}
		out.close();
		cout<<"学生增加成功！"<<endl;
		student_num = student_num + 1;
		cout<<"学生为："<<student_num<<"个"<<endl;
	}else{
		cout<<"学生存在，增加失败！"<<endl;
	}
	
}

void ManageStudent::deleteStudent(string id,Student *stu){
	int flag = 0;//删除成功失败标记位
	cout<<"学生为："<<student_num<<"个"<<endl;
	for(int i = 0;i < student_num;i++){
		if(id == stu[i].id){
			for(int j = i;j<student_num;j++){
				stu[j] = stu[j+1];
			}
			flag = 1;
		}
	}
	if(flag == 1){
		fstream out;
		out.open(student_url,ios_base::out);
		student_num = student_num - 1;
		for(int i = 0;i < student_num;i++){
			out<<stu[i].id<<" "<<stu[i].name<<" "<<stu[i].sex<<" "<<stu[i].age<<"\n";
		}
		out.close();
		cout<<"学生删除成功！"<<endl;
		cout<<"学生为："<<student_num<<"个"<<endl;
	}else{
		cout<<"学生删除失败！"<<endl;
	}
}

void ManageStudent::updateStudent(string id,string name,string sex,int age,Student *stu){
	int flag = 0;//更新成功失败标记位
	for(int i = 0;i < student_num;i++){
		if(id == stu[i].id){
			stu[i].id = id;
			stu[i].name = name;
			stu[i].sex = sex;
			stu[i].age = age;
			flag = 1;
		}
	}
	if(flag == 1){
		fstream out;
		out.open(student_url,ios_base::out);
		for(int i = 0;i<student_num;i++){
			out<<stu[i].id<<" "<<stu[i].name<<" "<<stu[i].sex<<" "<<stu[i].age<<"\n";
		}
		out.close();
		cout<<"学生更新成功！"<<endl;
	}else{
		cout<<"学生更新失败！"<<endl;
	}
}

