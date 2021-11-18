#ifndef GRADE_H
#define GRADE_H
#include <string>
using namespace std;

class Grade{
	public:
		string id;
		string name;
		string subject;
		int grade;
		Grade();
		~Grade();
		void readFile(Grade *gra);
		void showAll(Grade *gra);
		void showOneStudentGrade(string id,Grade *gra);
};

class ManageGrade:public Grade{
	public:
		ManageGrade();
		~ManageGrade();
		void insertGrade(string id,string name,string subject,int grade,Grade *gra);
		void deleteGrade(string id,string subject,Grade *gra);
		void updateGrade(string id,string name,string subject,int grade,Grade *gra);
		void sortStudentByGrade(string subject,Grade *gra,const int NUM);
		//函数重载
		string compareGrade(string id1,string id2,string name1,string name2,string subject,Grade *gra);
		string compareGrade(string id1,string id2,int grade1,int grade2,string subject,Grade *gra);
};

#endif
