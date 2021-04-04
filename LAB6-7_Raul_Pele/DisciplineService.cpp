#include "DisciplineService.h"
#include <string>
#include <vector>
#include "Discipline.h"
#include "Errors.h"
#include<iostream>

using namespace std;

void DisciplineService::addDiscipline(const string& name, const string& type, const int hoursPerWeek, const string& teacher) {
	//TODO: validate  data
	const Discipline& discipline{ name, type, hoursPerWeek, teacher };
	//std::cout << discipline.getTeacher() << "<- profesor\n";
	this->discRepo.addDiscipline(discipline);
	
}

void DisciplineService::removeDiscipline(const string& name, const string& type) {
	//TODO: validate data
	this->discRepo.removeDiscipline(name, type);
}

const vector<Discipline>& DisciplineService::getAll() const {
	return this->discRepo.getAll();
}

const Discipline& DisciplineService::findDiscipline(const string& name, const string& type) {
	//todo: validate
	const Discipline& disc = this->discRepo.findDiscipline(name, type);
	return disc;
}

void DisciplineService::modifyDiscipline(const string& name, const string& type, string& newName, string& newType, int newHours, string& newTeacher) {
	const Discipline& disc = this->discRepo.findDiscipline(name, type);
	if (newName == "") {
		newName = disc.getName();
	}
	
	if (newType == "") {
		newType = disc.getType();
	}

	if (newHours == -1) {
		newHours = disc.getHoursPerWeek();
	}

	if (newTeacher == "") {
		newTeacher = disc.getTeacher();
	}

	const Discipline& newDisc{ newName, newType, newHours, newTeacher };
	this->discRepo.removeDiscipline(name, type);
	this->discRepo.addDiscipline(newDisc);
	
}