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

string Discipline::toString() const {
	string output;
	output.append("Nume: " + this->getName() + "\n"+ \
		"Tip: " + this->getType() + "\n" + \
		"Ore pe saptamana: " + to_string(this->getHoursPerWeek()) + "\n" + \
		"Profesor: " + this->getTeacher()+ "\n");
	return output;
}
