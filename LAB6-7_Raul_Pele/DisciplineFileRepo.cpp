#include "DisciplineFileRepo.h"
#include "Errors.h"

#include <fstream>

DisciplineFileRepo::DisciplineFileRepo(string fileName): DisciplineRepo(), fileName(fileName) {
	this->loadFromFile();
}

void DisciplineFileRepo::loadFromFile() {

	//create file
	//ofstream fout(this->fileName);
	//fout.close();
	
	ifstream fin(this->fileName);
	
	if (!fin.is_open()) {
		throw FileError("Error opening file: " + this->fileName);
	}

	string name, type, teacher, hrsPerWeekStr;
	int hoursPerWeek;
	
	while (!fin.eof()) {
		getline(fin, name);
		if (fin.eof()) break;
		//fin >> type >> hoursPerWeek >> teacher;
		getline(fin, type);
		//fin >> hoursPerWeek;
		getline(fin, hrsPerWeekStr);
		hoursPerWeek = stoi(hrsPerWeekStr);
		getline(fin, teacher);

		Discipline disc{ name, type, hoursPerWeek, teacher };
		DisciplineRepo::addDiscipline(disc);
	}

	fin.close();
}

void DisciplineFileRepo::writeToFile() {
	ofstream fout(this->fileName);

	if (!fout.is_open()) {
		throw FileError("Error opening file: " + this->fileName);
	}

	for (const Discipline& disc : this->getAll()) {
		fout << disc.getName() << endl;
		fout << disc.getType() << endl;
		fout << disc.getHoursPerWeek() << endl;
		fout << disc.getTeacher() << endl;
	}

	fout.close();
}

void DisciplineFileRepo::addDiscipline(const Discipline& disc){
	DisciplineRepo::addDiscipline(disc);
	this->writeToFile();
}

void DisciplineFileRepo::removeDiscipline(const string& name, const string& type)  {
	DisciplineRepo::removeDiscipline(name, type);
	this->writeToFile();
}

//DisciplineFileRepo& DisciplineFileRepo::operator=(const DisciplineFileRepo& other) {
//	this->fileName = other.fileName;
//	return *this;
//	
//}