#include "Console.h"
#include "Errors.h"
#include <string>
#include<iostream>
#include <vector>
#include"LIIterator.h"
#include <algorithm>

using namespace std;

void Console::printDisc(const Discipline& disc) const{
	cout << "Nume: " << disc.getName() << endl;
	cout << "Tip: " << disc.getType() << endl;
	cout << "Ore pe saptamana: " << disc.getHoursPerWeek() << endl;
	cout << "Profesor: " << disc.getTeacher() << endl;
	cout << endl;
}

void Console::printDisciplines(const vector<Discipline>& disciplines) const {
	if (disciplines.empty()) {
		cout << "Lista este goala!\n\n";
		return;
	}

	for (const Discipline& disc : disciplines) {
		printDisc(disc);
	}
}

bool validateIntStr(const string& hoursStr) {
	if (hoursStr.size() == 0) {
		return false;
	}
	for (const char c : hoursStr) {
		if (!isdigit(c)) {
			return false;
		}
	}
	return true;
}

void Console::addDiscipline() {
	string name, type, teacher, hrsStr;
	int hoursPerWeek=0;

	printDisciplines(this->discSrv.getAll());

	cout << "Dati numele disciplinei: \n";
	getline(cin, name);
	cout << "\n";

	cout << "Dati tipul disciplinei: \n";
	getline(cin, type);
	cout << "\n";

	cout << "Dati numarul de ore pe saptamana: \n";
	getline(cin, hrsStr);
	cout << "\n";

	if (validateIntStr(hrsStr) == false) {
		cout << "Datele sunt invalide!\n";
		return;
	}

	cout << "Dati profesorul: \n";
	getline(cin, teacher);
	cout << "\n";

	hoursPerWeek = stoi(hrsStr);

	try {
		this->discSrv.addDiscipline(name, type, hoursPerWeek, teacher);
	}
	catch (Error& err) {
		cout << err.getMessage() << "\n";
	}
	
}
void Console::removeDiscipline(){
	string name, type;

	printDisciplines(this->discSrv.getAll());


	cout << "Dati numele disciplinei: \n";
	getline(cin, name);
	cout << "\n";

	cout << "Dati tipul disciplinei: \n";
	getline(cin, type);
	cout << "\n";

	try {
		this->discSrv.removeDiscipline(name, type);
	}
	catch (Error& err) {
		cout << err.getMessage() << "\n";
	}
}

void Console::findDiscipline() const{
	string name, type;

	cout << "Dati numele disciplinei: \n";
	getline(cin, name);
	cout << "\n";

	cout << "Dati tipul disciplinei: \n";
	getline(cin, type);
	cout << "\n";

	try {
		 const Discipline& disc = this->discSrv.findDiscipline(name, type);
		 printDisc(disc);
	}
	catch (Error& err) {
		cout << err.getMessage() << "\n";
	}
}

void Console::modifyDiscipline() {
	string name, type, newName, newType, newTeacher, field;
	int newHours = -1;

	if (this->discSrv.getAll().empty()) {
		cout << "Lista este goala!\n\n";
		return;
	}

	printDisciplines(this->discSrv.getAll());


	cout << "Dati numele disciplinei care se modifica: \n";
	getline(cin, name);
	cout << "\n";

	cout << "Dati tipul disciplinei care se modifica: \n";
	getline(cin, type);
	cout << "\n";

	cout << "Dati campul care se modifica (nume, tip, ore, profesor): \n";
	getline(cin, field);
	cout << "\n";
	
	if (field == "nume") {
		cout << "Dati numele nou: \n";
		getline(cin, newName);
		cout << "\n";
	}
	else if (field == "tip") {
		cout << "Dati tipul nou: \n";
		getline(cin, newType);
		cout << "\n";
	}
	else if (field == "ore") {
		cout << "Dati numarul de ore pe saptamana: \n";
		cin >> newHours;
		getchar();
		cout << "\n";
	}
	else if (field == "profesor") {
		cout << "Dati profesorul nou: \n";
		getline(cin, newTeacher);
		cout << "\n";
	}
	
	try {
		this->discSrv.modifyDiscipline(name, type, newName, newType, newHours, newTeacher);
	}
	catch (Error& err) {
		cout << err.getMessage() << endl;
	}
}


void Console::displayMenu() const {  
	cout << "1. Adaugati disciplina\n";
	cout << "2. Stergeti disciplina\n";
	cout << "3. Cautare disciplina\n";
	cout << "4. Modificare disciplina\n";
	cout << "5. Afisare discipline\n";
	cout << "6. Filtrare discipline\n";
	cout << "7. Sortare discipline\n";
	cout << "8. Adauga la contract\n";
	cout << "9. Generare contract aleator\n";
	cout << "10. Exporta contractul\n";
	cout << "11. Goleste contractul\n";
	cout << "12. Creaza raport\n";
	cout << "13. Undo\n";
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
			cout << options.at(i) << ' ';
		cout << endl;
	}

	return stoi(opStr);
}

void Console::filterDisciplineByHours() {
	cout << "Dati numarul de ore dupa care se face filtrarea: \n";
	string hrsStr;
	int hoursPerWeek=0;

	getline(cin, hrsStr);
	cout << "\n";

	if (validateIntStr(hrsStr) == false) {
		cout << "Date invalide!\n";
		return;
	}
	hoursPerWeek = stoi(hrsStr);

	try {
		const vector<Discipline> filtered = this->discSrv.filterDisciplineByHours(hoursPerWeek);

		if (filtered.empty()) {
			cout << "Lista este goala!\n\n";
		}
		else {
			cout << "Disciplinele filtrate dupa ore:\n";
			for (const Discipline& discipline : filtered) {
				printDisc(discipline);
			}
		}
	}
	catch (Error& err) {
		cout << err.getMessage() << endl;
	}
}

void Console::filterDisciplineByTeacher() {
	cout << "Dati numele profesorului dupa care se face filtrarea: \n";
	string teacher;
	getline(cin, teacher);

	try {
		const vector<Discipline> filtered = this->discSrv.filterDisciplineByTeacher(teacher);
		if (filtered.empty()) {
			cout << "Lista este goala!\n\n";
		}
		else {
			cout << "Disciplinele filtrate dupa profesor: \n";
			for (const Discipline& discipline : filtered) {
				printDisc(discipline);
			}
		}
	}
	catch (Error& err) {
		cout << err.getMessage() << endl;
	}
}

void Console::filterDisciplines() {
	string field;

	if (this->discSrv.getAll().empty()) {
		cout << "Lista este goala!\n\n";
		return;
	}

	printDisciplines(this->discSrv.getAll());
	cout << "Filtrare dupa ore / profesor: \n";

	getline(cin, field);
	cout << "\n";

	if (field == "ore") {
		this->filterDisciplineByHours();
	}
	else if (field == "profesor") {
		this->filterDisciplineByTeacher();
	}
	else {
		cout << "Camp invalid!\n";
	}
}

void Console::sortDisciplines() {
	vector<Discipline> sorted;
	string field, mode;

	if (this->discSrv.getAll().empty()) {
		cout << "Lista este goala!\n\n";
		return;
	}

	printDisciplines(this->discSrv.getAll());

	cout << "Sortare dupa nume/ore/profesor+tip: \n";
	getline(cin, field);

	while (true) {
		cout << "Mod crescator (C)/ descrescator(D): \n";
		getline(cin, mode);
		if (mode == "C" || mode == "D") {
			break;
		}
	}

	if (field == "nume") {
		sorted = this->discSrv.sortDisciplinesByName(mode);
	}
	else if (field == "ore") {
		sorted = this->discSrv.sortDisciplinesByHours(mode);
	}
	else if (field == "profesor+tip") {
		sorted = this->discSrv.sortDisciplinesByTeacherAndType(mode);
	}
	else {
		cout << "Campul este invalid!\n";
		return;
	}
	cout << "Disciplinele sortate: \n";
	printDisciplines(sorted);
}


void Console::addToContract() {
	const vector<Discipline>& disciplines = this->discSrv.getAll();

	if (disciplines.empty()) {
		cout << "Lista este goala!\n\n";
	}
	string name, type{"type"};

	while (true && !disciplines.empty()) {
		printDisciplines(disciplines);
		cout << "Daca doriti sa iesiti apasati 0 \n";
		cout << "Dati numele disciplinei care se adauga in contract: \n";
		getline(cin, name);

		if (name == "0") {
			break;
		}

		//cout << "Dati tipul disciplinei care se adauga in contract: \n";
		//getline(cin, type);

		try {
			this->discSrv.addToContract(name, type);
		}
		catch (Error& err) {
			cout << err.getMessage() << "\n\n";
		}
	}

	cout << "Numarul disciplinelor din contract este: " << this->discSrv.getContractLength() << "\n\n";
}

void Console::generateContract() {
	if (this -> discSrv.getAll().empty()) {
		cout << "Lista este goala!\n\n";
		return;
	}
	string nrOfDiscStr;
	 int nrOfDisc=0;

	cout << "Dati numarul de discipline pe care il va contine contractul: \n";
	getline(cin, nrOfDiscStr);

	if (validateIntStr(nrOfDiscStr) == false) {
		cout << "Numarul introdus este invalid!\n";
		return;
	}
	nrOfDisc = stoi(nrOfDiscStr);

	try {
		this->discSrv.generateContract(nrOfDisc);
	}
	catch (Error& err) {
		cout << err.getMessage() << "\n";
	}
	cout << "Numarul disciplinelor din contract este: " << this->discSrv.getContractLength() << "\n\n";

}


void Console::exportContract() {
	if (this->discSrv.getContractLength() == 0) {
		cout << "Contractul este gol!\n\n";
		return;
	}

	string destFile;
	cout << "Dati numele fisierului in care se exporta contractul (fara extensie): ";
	getline(cin, destFile);

	this->discSrv.exportContract(destFile);
	cout << "Numarul disciplinelor din contract este: " << this->discSrv.getContractLength() << "\n\n";

}

void Console::clearContract() {
	this->discSrv.clearContract();
	cout << "Numarul disciplinelor din contract este: " << this->discSrv.getContractLength() << "\n\n";

}

void Console::createReport() {
	if (this->discSrv.getAll().empty()) {
		cout << "Lista este goala!\n\n";
		return;
	}
	printDisciplines(this->discSrv.getAll());

	map<string, DisciplineCountDTO> report = this->discSrv.createReport();
	for (auto a : report) {
		cout << a.first << " : " << a.second.getCount() << "\n";
	}
}

void Console::undo() {
	try {
		this->discSrv.undo();
	}
	catch (Error& e) {
		cout << e.getMessage() << endl;
	}
}

void Console::run() {
	/*void (Console:: * funct[4])() const= { &Console::addDiscipline, &Console::removeDiscipline,
								& Console::findDiscipline,& Console::printDisciplines };*/
	vector<string> options = { "1", "2", "3", "4", "5", "6", "7","8","9","10", "11","12","13", "0"};
	int op = 0;

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
			this->printDisciplines(this->discSrv.getAll());
			break;

		case 6:
			this->filterDisciplines();
			break;

		case 7:
			this->sortDisciplines();
			break;

		case 8:
			this->addToContract();
			break;

		case 9:
			this->generateContract();
			break;

		case 10:
			this->exportContract();
			break;

		case 11:
			this->clearContract();
			break;
			
		case 12:
			this->createReport();
			break;

		case 13:
			this->undo();
			break;


		default:
			break;
		}
	}
}