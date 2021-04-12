#include "Contract.h"
#include "Errors.h"

#include <fstream>
using namespace std;

Contract::Contract(const Contract& other) : discRepo(other.discRepo), disciplines(other.disciplines) {}


void Contract::add(const string& name, const string& type) {
	auto it = find_if(this->disciplines.begin(), this->disciplines.end(),
		[name, type](const Discipline& disc) {
			return disc.getName() == name;//&& disc.getType() == type;
		});

	if (it != this->disciplines.end()) {
		throw DiscExistsError("Disciplina se afla deja in contract!");
	}

	//const Discipline& disc = this->discRepo.findDiscipline(name, type);
	const vector<Discipline>& allDisc= this->discRepo.getAll();
	auto it2 = find_if(allDisc.begin(), allDisc.end(), [name](const Discipline& disc) {
		return disc.getName() == name;
		});
	if (it2 == allDisc.end())
		throw DiscNotFoundError("Disciplina nu se afla in lista!");

	Discipline newDisc{ name, "TBD", 0, "TBD"};
	this->disciplines.push_back(newDisc);
}

void Contract::clear() {
	this->disciplines.clear();
}

vector<Discipline>& Contract::getAll() {
	return this->disciplines;
}

void Contract::exportContract(const string& destFile) {
	ofstream file;
	file.open(destFile + ".html");

	file << "<!DOCTYPE html><html>\n<head></head>\n<body>";

	for (const Discipline& d : this->disciplines) {
		file <<"Disciplina: "<< d.getName() << "<br>";
	}

	file << "</body>\n</html>";
}

