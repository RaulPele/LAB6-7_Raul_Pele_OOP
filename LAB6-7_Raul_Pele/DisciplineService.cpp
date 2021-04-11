#include "DisciplineService.h"
#include <string>
#include <vector>
#include "Discipline.h"
#include "Errors.h"
#include<iostream>
#include "LinkedList.h"
#include "LIIterator.h"
#include "validators.h"
#include "compare.h"

using namespace std;

void DisciplineService::addDiscipline(const string& name, const string& type, const int hoursPerWeek, const string& teacher) {
	if (this->validator.validateName(name) == false || \
		this->validator.validateTeacher(teacher) == false || \
		this->validator.validateHoursPerWeek(hoursPerWeek) == false) 
	{
		throw InvalidDataError("Datele sunt invalide!\n");
	}

	const Discipline& discipline{ name, type, hoursPerWeek, teacher };
	this->discRepo.addDiscipline(discipline);
}

void DisciplineService::removeDiscipline(const string& name, const string& type) {
	if (this->validator.validateName(name) == false)
	{
		throw InvalidDataError("Datele sunt invalide!\n");
	}

	this->discRepo.removeDiscipline(name, type);
}

const LinkedList<Discipline>& DisciplineService::getAll() const {
	return this->discRepo.getAll();
}

const Discipline& DisciplineService::findDiscipline(const string& name, const string& type) {
	if (this->validator.validateName(name) == false )
	{
		throw InvalidDataError("Datele sunt invalide!\n");
	}

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

	if (this->validator.validateName(name) == false || \
		this->validator.validateHoursPerWeek(newHours) == false || \
		this->validator.validateName(newName) == false || \
		this->validator.validateTeacher(newTeacher) == false)
	{
		throw InvalidDataError("Datele sunt invalide!\n");
	}

	const Discipline& newDisc{ newName, newType, newHours, newTeacher };
	this->discRepo.removeDiscipline(name, type);
	this->discRepo.addDiscipline(newDisc);
}

const LinkedList<Discipline> DisciplineService::filterDisciplineByTeacher(const string& teacher) {
	if (this->validator.validateTeacher(teacher) == false) {
		throw InvalidDataError("Datele sunt invalide!\n");
	}
	LinkedList<Discipline> filtered;

	for (const Discipline& discipline : this->getAll()) {
		if (discipline.getTeacher() == teacher) {
			filtered.add(Discipline{ discipline });
		}
	}
	return filtered;
}

const LinkedList<Discipline> DisciplineService::filterDisciplineByHours(const int hoursPerWeek) {
	if (this->validator.validateHoursPerWeek(hoursPerWeek) == false) {
		throw InvalidDataError("Datele sunt invalide!\n");
	}
	LinkedList<Discipline> filtered;

	for (const Discipline& discipline : this->getAll()) {
		if (discipline.getHoursPerWeek() == hoursPerWeek) {
			filtered.add(Discipline{ discipline });
		}
	}
	return filtered;
}

const LinkedList<Discipline> DisciplineService::sortDisciplinesByHours(string mode) {
	LinkedList<Discipline> sorted{ this->discRepo.getAll() };
	bool reversed = false;
	if (mode == "D") {
		reversed = true;
	}
	sorted.sort(cmpOre, reversed);
	return sorted;
}
const LinkedList<Discipline> DisciplineService::sortDisciplinesByName(string mode) {
	LinkedList<Discipline> sorted{ this->discRepo.getAll() };
	bool reversed = false;
	if (mode == "D") {
		reversed = true;
	}
	sorted.sort(cmpName, reversed);
	return sorted;
}

const LinkedList<Discipline> DisciplineService::sortDisciplinesByTeacherAndType(string mode) {
	LinkedList<Discipline> sorted{ this->discRepo.getAll() };
	bool reversed = false;
	if (mode == "D") {
		reversed = true;
	}
	sorted.sort(cmpTeacherAndType, reversed);
	return sorted;
}