#ifndef STUDENT_H
#define STUDENT_H
#include <string>
using namespace std;

class Student{
	public:
		string id;
		string name;
		string sex;
		int age;
		Student();
		~Student();
		void showOneStudent(string id,Student *stu);
		void readFile(Student *stu);
		void showAll(Student *stu);
};

class ManageStudent:public Student{
	public:
		ManageStudent();
		~ManageStudent();
		void insertStudent(string id,string name,string sex,int age,Student *stu);
		void deleteStudent(string id,Student *stu);
		void updateStudent(string id,string name,string sex,int age,Student *stu);
};

#endif
