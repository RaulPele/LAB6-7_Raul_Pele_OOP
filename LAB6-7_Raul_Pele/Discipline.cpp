#include "Discipline.h"

string Discipline::getName() const  {
	return this->name;
}

string Discipline::getTeacher() const  {
	return this->teacher;
}

string Discipline::getType() const  {
	return this->type;
}

int Discipline::getHoursPerWeek() const {
	return this->hoursPerWeek;
}

bool Discipline::operator==(const Discipline& a) const{
	return this->name == a.name && this->type == a.type && this->hoursPerWeek == a.hoursPerWeek && \
		this->teacher == a.teacher;
}
