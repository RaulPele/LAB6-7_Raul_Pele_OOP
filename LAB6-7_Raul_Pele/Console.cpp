#include "Console.h"
#include "Errors.h"
#include <string>
#include<iostream>
#include <vector>

using namespace std;

void Console::printDisc(const Discipline& disc) const{
	cout << "Nume: " << disc.getName() << endl;
	cout << "Tip: " << disc.getType() << endl;
	cout << "Ore pe saptamana: " << disc.getHoursPerWeek() << endl;
	cout << "Profesor: " << disc.getTeacher() << endl;
	cout << endl;
}

void Console::printDisciplines() const {
	const vector<Discipline>& disciplines = this->discSrv.getAll();
	for (auto i = disciplines.begin(); i < disciplines.end(); i++) {
		printDisc(*i);
	}
}

void Console::addDiscipline() {
	string name, type, teacher;
	int hoursPerWeek;

	cout << "Dati numele disciplinei: \n";
	getline(cin, name);

	cout << "Dati tipul disciplinei: \n";
	getline(cin, type);

	cout << "Dati numarul de ore pe saptamana: \n";
	cin >> hoursPerWeek;

	cout << "Dati profesorul: \n";
	cin >> teacher;
	getline(cin, teacher);


	try {
		this->discSrv.addDiscipline(name, type, hoursPerWeek, teacher);
	}
	catch (DiscExistsError& err) {
		cout << err.getMessage() << "\n";
	}
	
}
void Console::removeDiscipline(){
	string name, type;

	cout << "Dati numele disciplinei: \n";
	getline(cin, name);

	cout << "Dati tipul disciplinei: \n";
	getline(cin, type);

	try {
		this->discSrv.removeDiscipline(name, type);
	}
	catch (DiscNotFoundError& err) {
		cout << err.getMessage() << "\n";
	}
}

void Console::findDiscipline() const{
	string name, type;

	cout << "Dati numele disciplinei: \n";
	getline(cin, name);

	cout << "Dati tipul disciplinei: \n";
	getline(cin, type);

	try {
		 const Discipline& disc = this->discSrv.findDiscipline(name, type);
		 printDisc(disc);
	}
	catch (DiscNotFoundError& err) {
		cout << err.getMessage() << "\n";
	}
}

void Console::modifyDiscipline() {
	string name, type, newName, newType, newTeacher, field;
	int newHours = -1;

	cout << "Dati numele disciplinei care se modifica: \n";
	getline(cin, name);

	cout << "Dati tipul disciplinei care se modifica: \n";
	getline(cin, type);

	cout << "Dati campul care se modifica (nume, tip, ore, profesor): \n";
	getline(cin, field);
	
	if (field == "nume") {
		cout << "Dati numele nou: \n";
		getline(cin, newName);
	}
	else if (field == "tip") {
		cout << "Dati tipul nou: \n";
		getline(cin, newType);
	}
	else if (field == "ore") {
		cout << "Dati numarul de ore pe saptamana: \n";
		cin >> newHours;
	}
	else if (field == "profesor") {
		cout << "Dati profesorul nou: \n";
		getline(cin, newTeacher);
	}
	
	try {
		this->discSrv.modifyDiscipline(name, type, newName, newType, newHours, newTeacher);
	}
	catch (DiscNotFoundError& err) {
		cout << err.getMessage() << endl;
	}
	catch (DiscExistsError& err) {
		cout << err.getMessage() << endl;
	}

}


void Console::displayMenu() const {  
	cout << "1. Adaugati disciplina\n";
	cout << "2. Stergeti disciplina\n";
	cout << "3. Cautare disciplina\n";
	cout << "4. Modificare disciplina\n";
	cout << "5. Afisare discipline\n";
	cout << "0. Iesire...\n\n";
};

int Console::readOption(const vector<string>& options) const{
	string opStr;
	bool found = false;
	while (true) {
		cout << "Dati o optiune: \n";
		getline(cin, opStr);
		for (string c : options) {
			if (opStr == c) {
				found = true;
				break;
			}
		}

		if (found) {
			break;
		}
		cout << "Optiune invalida!\n";
		cout << "Optiunea trebuie sa fie din multimea: ";
		for (unsigned int i = 0; i < options.size(); i++)
			cout << options[i] << ' ';
		cout << endl;
	}

	return stoi(opStr);
}


void Console::run() {
	/*void (Console:: * funct[4])() const= { &Console::addDiscipline, &Console::removeDiscipline,
								& Console::findDiscipline,& Console::printDisciplines };*/
	vector<string> options = { "1", "2", "3", "4", "5", "0"};
	int op;

	while (true) {
		displayMenu();
		op = readOption(options);

		
		switch (op) {
		case 0:
			return;
		case 1:
			this->addDiscipline();
			break;
		case 2:
			this->removeDiscipline();
			break;

		case 3:
			this->findDiscipline();
			break;

		case 4:
			this->modifyDiscipline();
			break;

		case 5:
			this->printDisciplines();
			break;
		}

	}
}