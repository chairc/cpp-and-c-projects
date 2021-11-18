#include <iostream>
#include <string>

#include "student.h"
#include "grade.h"
#include "people.h"

using namespace std;

/*
1.登录界面（while循环）
    （1）首先将输入的登录人员进行判断（if）使用管理员类还是工作人员类【1为管理员   2为工作人员】
    （2）将选择的表（txt文件）调入内存
    （3）将用户名及密码进行比对
    （4）成功后进行操作
    
*/

int main(int argc, char** argv) {
	//简单登录界面
	string username,password,id,name,sex,subject,id1,id2,name1,name2,str;
	int login_type,select_type,age,subject_grade,case7select_type,subject_grade1,subject_grade2;
	int flag = 1;//循环标志位（用于退出内循环）
	const int NUM = 100;
	while(flag == 1){
		Manager manager;//生成管理员类，调用管理员类中读取文件到内存的方法
		Student student;
		Grade grade;
		ManageStudent ms;
		ManageGrade mg;
		Worker worker;
		//初始化对象数组
		Manager *man = new Manager[NUM];
		Worker *wo = new Worker[NUM];
		Student *stu = new Student[NUM];
		Grade *gra = new Grade[NUM];
		manager.readFile("manager",man);
		worker.readFile("worker",wo);
		student.readFile(stu);
		grade.readFile(gra);
		cout<<"欢迎来到简单学生管理系统"<<endl;
		cout<<"（1）登录"<<endl;
		cout<<"（0）退出"<<endl;
		cout<<"请选择操作：";
		cin>>select_type;
		system("cls");
		switch(select_type){
			case 1:
				cout<<"请输入账号：";
				cin>>username;
				cout<<"请输入密码：";
				cin>>password;
				cout<<"请输入登录方式为（1）管理员/（2）工作人员：";
				cin>>login_type;
				if(login_type == 1){//此处为管理员登录
					system("cls");
					flag = 2;
					if(manager.login(username,password,man)){
						cout<<"Manager登录成功"<<endl;
						while(flag == 2){
							cout<<"欢迎管理员"<<username<<endl;
							cout<<"（1） 学生信息显示 "<<"（8） 学生成绩录入"<<endl;
							cout<<"（2） 学生信息录入 "<<"（9） 学生成绩更改"<<endl;
							cout<<"（3） 学生信息更改 "<<"（10）学生成绩删除"<<endl;
							cout<<"（4） 学生信息删除 "<<"（11）管理员信息显示"<<endl;
							cout<<"（5） 学生成绩显示 "<<"（12）工作人员信息显示"<<endl;
							cout<<"（6） 学生成绩排序 "<<"（0） 注销账户"<<endl;
							cout<<"（7） 学生成绩比较 "<<endl;
							cout<<"您要进行的操作为：";
							cin>>select_type;
							system("cls");
							switch(select_type){
								case 1:
									student.showAll(stu);
									break;
								case 2:
									cout<<"请依次输入学生学号，姓名，性别，年龄"<<endl;
									cin>>id>>name>>sex>>age;
									ms.insertStudent(id,name,sex,age,stu);
									break;
								case 3:
									cout<<"请输入需要修改的学生学号：";
									cin>>id;
									cout<<"当前信息为："<<endl;
									student.showOneStudent(id,stu);
									cout<<"信息修改为（依次输入学生学号，姓名，性别，年龄）：";
									cin>>id>>name>>sex>>age;
									ms.updateStudent(id,name,sex,age,stu);
									break;
								case 4:
									cout<<"请输入需要删除信息的学生学号：";
									cin>>id;
									ms.deleteStudent(id,stu);
									break;
								case 5:
									grade.showAll(gra);
									break;
								case 6:
									cout<<"请输入排序科目：";
									cin>>subject;
									mg.sortStudentByGrade(subject,gra,NUM);
									break;
								case 7:
									grade.showAll(gra);
									cout<<"（1）按学号查询比较 （2）按成绩查询比较"<<endl;
									cout<<"请选择比较方式：";
									cin>>case7select_type;
									if(case7select_type == 1){
										cout<<"请依次输入比较的学号1，学号2，姓名1，姓名2，比较科目：";
										cin>>id1>>id2>>name1>>name2>>subject;
										str = mg.compareGrade(id1,id2,name1,name2,subject,gra);
									}else if(case7select_type == 2){
										cout<<"请依次输入比较的学号1，学号2，成绩1，成绩2，比较科目：";
										cin>>id1>>id2>>subject_grade1>>subject_grade2>>subject;
										str = mg.compareGrade(id1,id2,subject_grade1,subject_grade2,subject,gra);
									}else{
										cout<<"输入值非法！";
									}
									cout<<"比较结果为："<<str<<endl;
									break;
								case 8:
									cout<<"请依次输入学生学号，姓名，学科，成绩"<<endl;
									cin>>id>>name>>subject>>subject_grade;
									mg.insertGrade(id,name,subject,subject_grade,gra);
									break;
								case 9:
									cout<<"请输入需要修改的学生学号：";
									cin>>id;
									cout<<"当前信息为："<<endl;
									grade.showOneStudentGrade(id,gra);
									cout<<"信息修改为（依次输入学生学号，姓名，学科，成绩）：";
									cin>>id>>name>>subject>>subject_grade;
									mg.updateGrade(id,name,subject,subject_grade,gra);
									break;
								case 10:
									cout<<"请依次输入需要删除信息的学生学号和学科：";
									cin>>id>>subject;
									mg.deleteGrade(id,subject,gra);
									break;
								case 11:
									manager.showAll(man);
									break;
								case 12:
									worker.showAll(wo);
									break;
								case 0:
									flag = 1;
									break;
							}
							if(select_type != 0){
								system("pause");
							}
							system("cls");
						}
					}else{
						cout<<"Manager登录失败"<<endl;
						flag = 1;
					}
				}else if(login_type == 2){//此处为工作人员登录
					system("cls");
					flag = 2;
					if(worker.login(username,password,wo)){
						cout<<"Worker登录成功"<<endl;
						while(flag ==2){
							cout<<"欢迎工作人员"<<username<<endl;
							cout<<"（1） 学生信息显示 "<<"（5） 学生成绩录入"<<endl;
							cout<<"（2） 学生成绩显示 "<<"（6） 学生成绩更改"<<endl;
							cout<<"（3） 学生成绩排序 "<<"（7） 学生成绩删除"<<endl;
							cout<<"（4） 学生成绩比较 "<<"（0） 注销账户"<<endl;
							cout<<"您要进行的操作为：";
							cin>>select_type;
							system("cls");
							switch(select_type){
								case 1:
									student.showAll(stu);
									break;
								case 2:
									grade.showAll(gra);
									break;
								case 3:
									cout<<"请输入排序科目：";
									cin>>subject;
									mg.sortStudentByGrade(subject,gra,NUM);
									break;
								case 4:
									grade.showAll(gra);
									cout<<"（1）按学号查询比较 （2）按成绩查询比较"<<endl;
									cout<<"请选择比较方式：";
									cin>>case7select_type;
									if(case7select_type == 1){
										cout<<"请依次输入比较的学号1，学号2，姓名1，姓名2，比较科目：";
										cin>>id1>>id2>>name1>>name2>>subject;
										str = mg.compareGrade(id1,id2,name1,name2,subject,gra);
									}else if(case7select_type == 2){
										cout<<"请依次输入比较的学号1，学号2，成绩1，成绩2，比较科目：";
										cin>>id1>>id2>>subject_grade1>>subject_grade2>>subject;
										str = mg.compareGrade(id1,id2,subject_grade1,subject_grade2,subject,gra);
									}else{
										cout<<"输入值非法！";
									}
									cout<<"比较结果为："<<str<<endl;
									break;
								case 5:
									cout<<"请依次输入学生学号，姓名，学科，成绩"<<endl;
									cin>>id>>name>>subject>>subject_grade;
									mg.insertGrade(id,name,subject,subject_grade,gra);
									break;
								case 6:
									cout<<"请输入需要修改的学生学号：";
									cin>>id;
									cout<<"当前信息为："<<endl;
									grade.showOneStudentGrade(id,gra);
									cout<<"信息修改为（依次输入学生学号，姓名，学科，成绩）：";
									cin>>id>>name>>subject>>subject_grade;
									mg.updateGrade(id,name,subject,subject_grade,gra);
									break;
								case 7:
									cout<<"请依次输入需要删除信息的学生学号和学科：";
									cin>>id>>subject;
									mg.deleteGrade(id,subject,gra);
									break;
								case 0:
									flag = 1;
									break;
							}
							if(select_type != 0){
								system("pause");
							}
							system("cls");
						}
					}else{
						cout<<"Worker登录失败"<<endl;
						flag = 1;
					}
				}else{//此处为非法字符
					cout<<"非法字符，登录失败"<<endl;
					flag = 1;
				}
				system("pause");
				system("cls");
				break;
			case 0:
				exit(0);
			default:
				cout<<"非法字符！"<<endl;
				system("pause");
				system("cls");
				break;
		}
	}
	return 0;
}
