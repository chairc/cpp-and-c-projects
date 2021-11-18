#ifndef PEOPLE_H
#define PEOPLE_H
#include <string>
using namespace std;

//继承与派生
class People{
	private:
		string id;
		string username;
		string password;
	public:
		People();
		~People();
		bool login(string username,string password,People *peo);
		void readFile(string url,People *peo);
		void showAll(People *peo);
};

class Manager:public People{
	public:
		Manager();
		Manager(string username,string password);
		~Manager();
		bool login(string username,string password,Manager *man);
		void readFile(string url,Manager *man);
		void showAll(Manager *man);
};

class Worker:public People{
	public:
		Worker();
		Worker(string username,string password);
		~Worker();
		bool login(string username,string password,Worker *wo);
		void readFile(string url,Worker *wo);
		void showAll(Worker *wo);
};

#endif
