#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <random>

#include "Discipline.h"
#include "Contract.h"
#include "Errors.h"
#include "DisciplineService.h"
#include "LIIterator.h"
#include "validators.h"
#include "compare.h"
#include "UndoAdd.h"
#include "UndoRemove.h"
#include "UndoModify.h"

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
	
	//add to undo list
	//UndoAdd action{ this->discRepo, discipline };
	UndoAdd* action = new UndoAdd{ this->discRepo, discipline };
	this->undoList.push_back(action);
}

void DisciplineService::removeDiscipline(const string& name, const string& type) {
	if (this->validator.validateName(name) == false)
	{
		throw InvalidDataError("Datele sunt invalide!\n");
	}

	const Discipline removed = this->discRepo.findDiscipline(name, type);
	this->discRepo.removeDiscipline(name, type);


	UndoRemove* action = new UndoRemove{ this->discRepo, removed };
	this->undoList.push_back(action);

}

const vector<Discipline> DisciplineService::getAll() const {
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
	
	const Discipline disc = this->discRepo.findDiscipline(name, type);
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

	
	UndoModify* action = new UndoModify{ this->discRepo, disc, newDisc };
	this->undoList.push_back(action);
}

const vector<Discipline> DisciplineService::filterDisciplineByTeacher(const string& teacher) {
	if (this->validator.validateTeacher(teacher) == false) {
		throw InvalidDataError("Datele sunt invalide!\n");
	}

	const vector<Discipline>& disciplines = this->getAll();
	vector<Discipline> filtered{ disciplines.size()};

	auto last = copy_if(disciplines.begin(), disciplines.end(), filtered.begin(),
		[teacher](const Discipline& disc) {
			return disc.getTeacher() == teacher;
		});
	filtered.resize(distance(filtered.begin(), last));

	return filtered;
}

const vector<Discipline> DisciplineService::filterDisciplineByHours(const int hoursPerWeek) {
	if (this->validator.validateHoursPerWeek(hoursPerWeek) == false) {
		throw InvalidDataError("Datele sunt invalide!\n");
	}
	
	const vector<Discipline>& disciplines = this->getAll();
	vector<Discipline> filtered{ disciplines.size() };

	auto last =copy_if(disciplines.begin(), disciplines.end(), filtered.begin(),
		[hoursPerWeek](const Discipline& disc) {
			return disc.getHoursPerWeek() == hoursPerWeek;
		});
	filtered.resize(distance(filtered.begin(), last));

	return filtered;
}

const vector<Discipline> DisciplineService::sortDisciplinesByHours(string mode) {
	vector<Discipline> sorted{ this->discRepo.getAll() };
	sort(sorted.begin(), sorted.end(), cmpOre);

	if (mode == "D") {
		reverse(sorted.begin(), sorted.end());
	}

	return sorted;
}

const vector<Discipline> DisciplineService::sortDisciplinesByName(string mode) {
	vector<Discipline> sorted{ this->discRepo.getAll() };
	sort(sorted.begin(), sorted.end(), cmpName);

	if (mode == "D") {
		reverse(sorted.begin(), sorted.end());
	}
	return sorted;
}

const vector<Discipline> DisciplineService::sortDisciplinesByTeacherAndType(string mode) {
	vector<Discipline> sorted{ this->discRepo.getAll() };
	sort(sorted.begin(), sorted.end(), cmpTeacherAndType);

	if (mode == "D") {
		reverse(sorted.begin(), sorted.end());
	}
	return sorted;
}

void DisciplineService::addToContract(const string& name, const string& type) {
	if (this->validator.validateName(name) == false) {
		throw InvalidDataError("Datele introduse sunt invalide!\n");
	}

	this->contract.add(name, type);

	//vector<Discipline>& contractDisc = this->contract.getAll();
	//vector<Discipline> available{ contractDisc.size() };

	/*copy_if(contractDisc.begin(), contractDisc.end(), available.begin(),
		[contractDisc](const Discipline& disc) {
			auto it = find_if(contractDisc.begin(), contractDisc.end(), )
		});*/
}

vector<Discipline> DisciplineService::getUnique() {
	const vector<Discipline> disciplines = this->getAll();
	bool unique = true;
	vector<Discipline> uniqueDiscs;

	//int count = 0;

	for (const Discipline& d : disciplines) {
		unique = true;
		for (const Discipline& a  : uniqueDiscs) {
			if (a.getName() == d.getName()) {
				unique = false;
				break;
			}
		}
		if (unique) {
			//count++;
			//names.push_back(d.getName());
			uniqueDiscs.push_back(d);
		}
	}
	return uniqueDiscs;
}

void DisciplineService::generateContract(int nrOfDisc) {

	if (this->validator.validateHoursPerWeek(nrOfDisc) == false) {
		throw InvalidDataError("Datele introduse sunt invalide!");
	}

	//vector<Discipline> disciplines = this->getAll();
	vector<Discipline> disciplines = this->getUnique();
	if ((unsigned int) nrOfDisc > disciplines.size()) { //disciplines.size()
		throw OutOfBoundsError("Numarul introdus este mai mare decat numarul disciplinelor!");
	}

	//vector<Discipline> available{ disciplines.size() };
	//copy(disciplines.begin(), disciplines.end(), available.begin());

	int k = nrOfDisc;
	this->contract.clear();

	while (k != 0) {
		mt19937 mt{ random_device{}() };
		uniform_int_distribution<> dist(0, disciplines.size() - 1);
		int nr = dist(mt);

		this->contract.add(disciplines.at(nr).getName(), disciplines.at(nr).getType());

		disciplines.erase(disciplines.begin() + nr);
		k--;
	}
}

void DisciplineService::clearContract() {
	this->contract.clear();
}

void DisciplineService::exportContract(const string& destFile) {
	this->contract.exportContract(destFile);
}

int DisciplineService::getContractLength() {
	return this->contract.getAll().size();
}

vector<Discipline>& DisciplineService::getContractDisciplines() {
	return this->contract.getAll();
}

bool isUnique(const string& type, map<string, DisciplineCountDTO> report) {
	for (auto a : report) {
		if (a.first == type) {
			return false;
		}
	}
	return true;
}

map<string, DisciplineCountDTO> DisciplineService::createReport() {
	const vector<Discipline> disciplines = this->getAll();
	map<string, DisciplineCountDTO> report;
	
	for (const Discipline& d : disciplines) {
		if (isUnique(d.getType(), report)) {
			DisciplineCountDTO dto{ d.getType() };
			report[d.getType()] = dto;
		}
		else {
			report[d.getType()].setCount(report[d.getType()].getCount() + 1);
		}
	}
	return report;
}

void DisciplineService::undo() {
	if (this->undoList.empty()) {
		throw ServiceError("Nu mai exista operatii!");
	}
	
	UndoAction* act = this->undoList.back();
	act->doUndo();
	this->undoList.pop_back();
	delete act;

}

DisciplineService::~DisciplineService() {
	for (UndoAction* act : this->undoList) {
		delete act;
	}
}