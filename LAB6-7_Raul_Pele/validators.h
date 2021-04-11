#pragma once
#include<string>
using namespace std;


class DisciplineValidator {
public:
	bool validateName(const string& name) const;
	bool validateType(const string& type) const;
	bool validateHoursPerWeek(const int hoursPerWeek) const;
	bool validateTeacher(const string& teacher) const;
};