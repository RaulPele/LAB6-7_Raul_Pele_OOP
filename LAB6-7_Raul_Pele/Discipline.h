#pragma once
#include<string>
#include<iostream>
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
	Discipline(const Discipline& discipline) {
		this->name = discipline.getName();
		this->type = discipline.getType();
		this->teacher = discipline.getTeacher();
		this->hoursPerWeek = discipline.getHoursPerWeek();
		cout << "Copy constructor called!\n";
		
	}
	string getName() const;
	string getType() const;
	string getTeacher() const;
	int getHoursPerWeek() const;
	bool operator==(const Discipline& a) const;

};