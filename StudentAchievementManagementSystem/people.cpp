#include <iostream>
#include <string>
#include<fstream>
#include <string.h>
#include "people.h"
using namespace std;

int people_num;

People::People(){
	
}

People::~People(){
	
}

void People::showAll(People *peo){
	cout<<"序号  "<<"姓名  "<<"密码  "<<endl;
	for(int i = 0;i < people_num;i++){
		cout<<peo[i].id<<" "<<peo[i].username<<" "<<peo[i].password<<endl;
	}
}

void People::readFile(string url,People *peo){
	fstream in;
	int i = 0,flag = 0;//i为读取文件行数记录
	string url_str = "../test/" + url + ".txt";//拼接相对路径
    char url_char[100];
    strcpy(url_char,url_str.c_str());
	in.open(url_char,ios::in);
	if(!in){
		ofstream fout(url_char);//没有文件时创建文件
		if(fout){
			fout.close();
			flag = 1;
		}
	}
	if(flag != 1){
		while(!in.eof() && flag != 1){
	        in>>peo[i].id>>peo[i].username>>peo[i].password;//依次读取txt文件中每行的数据
	        i++;
    }
		people_num = i;//记录管理员txt文件中行总数
	}
    in.close();
}

bool People::login(string username,string password,People *peo){
	for(int i = 0;i < people_num;i++){
		if(username == peo[i].username && password == peo[i].password){
			return true;
		}
	}
	return false;
}

/***************************管理员管理***************************/

Manager::Manager(){
	//cout<<"Manager已构造！"<<endl;
}

Manager::Manager(string username,string password){
	cout<<"Manager登录比对中。。。"<<endl;
}

Manager::~Manager(){
	//cout<<"Manager已析构！"<<endl;
}

void Manager::readFile(string url,Manager *man){
	People::readFile(url,man);
}

bool Manager::login(string username,string password,Manager *man){
	return People::login(username,password,man);
}

void Manager::showAll(Manager *man){
	People::showAll(man);
}

/***************************工作人员管理***************************/

Worker::Worker(){
	//cout<<"Worker已构造！"<<endl;
}

Worker::Worker(string username,string password){
	cout<<"Worker登录比对中。。。"<<endl;
}

Worker::~Worker(){
	//cout<<"Worker已析构！"<<endl;
}

void Worker::readFile(string url,Worker *wo){
	People::readFile(url,wo);
}

bool Worker::login(string username,string password,Worker *wo){
	return People::login(username,password,wo);
}

void Worker::showAll(Worker *wo){
	People::showAll(wo);
}
