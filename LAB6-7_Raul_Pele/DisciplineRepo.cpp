#include "DisciplineRepo.h"
#include "Discipline.h"
#include "Errors.h"
using namespace std;

const vector<Discipline>& DisciplineRepo::getAll() const{
	return this->disciplines;
}

const Discipline& DisciplineRepo::findDiscipline(const string& name, const string& type) const{
	for (const auto& discipline : this->disciplines) {
		if (discipline.getName() == name && discipline.getType() == type) {
			return discipline;
		}
	}
	throw DiscNotFoundError("Disciplina nu se afla in lista!");
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
	const Discipline& discipline = this->findDiscipline(name, type);

	for (auto i = this->disciplines.begin(); i < this->disciplines.end(); i++) {
		if (*i == discipline) {
			this->disciplines.erase(i);
			return;
		}
	}
}
