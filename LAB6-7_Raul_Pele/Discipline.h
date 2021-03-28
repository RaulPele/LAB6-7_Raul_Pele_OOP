#pragma once
#include<string>
using namespace std;

class Discipline {
private:
	string name;
	string type;
	string teacher;
	int hoursPerWeek;

	

public:
	Discipline(string name, string type, int hoursPerWeek, string teacher): name(name), type(type), teacher(teacher), 
																			hoursPerWeek(hoursPerWeek){}
	string getName() const;
	string getType() const;
	string getTeacher() const;
	int getHoursPerWeek() const;
	bool operator==(const Discipline& a) const;

};