#include "DisciplineRepo.h"
#include "Discipline.h"
#include "Errors.h"
#include "LIIterator.h"
#include <algorithm>
using namespace std;

const vector<Discipline>& DisciplineRepo::getAll() const{
	return this->disciplines;
}

const Discipline& DisciplineRepo::findDiscipline(const string& name, const string& type) const{

	auto it = find_if(this->disciplines.begin(), this->disciplines.end(),
		[name, type](const Discipline& disc) {
			return disc.getName() == name && disc.getType() == type;
		});

	if (it == this->disciplines.end()) {
		throw DiscNotFoundError("Disciplina nu se afla in lista!");
	}
	return *it;
}

bool DisciplineRepo::exists(const Discipline& discipline) const{
	try {
		findDiscipline(discipline.getName(), discipline.getType());
		return true;
	}
	catch (DiscNotFoundError&) {
		return false;
	}
}

void DisciplineRepo::addDiscipline(const Discipline& discipline) {
	if (exists(discipline)) {
		throw DiscExistsError("Disciplina se afla deja in lista!");
	}

	this->disciplines.push_back(discipline);
}

void DisciplineRepo::removeDiscipline(const string& name, const string& type) {

	auto it = find_if(this->disciplines.begin(), this->disciplines.end(), [name, type](const Discipline& disc) {
		return disc.getName() == name && disc.getType() == type;
		});

	if (it == this->disciplines.end()) {
		throw DiscNotFoundError("Disciplina nu se afla in lista!");
	}
	this->disciplines.erase(it);
}

//DisciplineRepo& DisciplineRepo::operator=(const DisciplineRepo& other) {
//	this->disciplines = other.disciplines;
//	return *this;
//}