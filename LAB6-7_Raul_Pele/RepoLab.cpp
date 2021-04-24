#include "RepoLab.h"
#include "Discipline.h"
#include "Errors.h"

#include <vector>
using namespace std;

const vector<Discipline> RepoLab::getAll() const {
	vector<Discipline> discVector;
	for (auto pair : this->disciplines) {
		discVector.push_back(pair.second);
	}
	return discVector;
}

const Discipline& RepoLab::findDiscipline(const string& name, const string& type) const {
	//for (auto pair : this->disciplines) {
	//	if (pair.second.getName() == name && pair.second.getType() == type) {
	//		return pair.second;
	//	}
	//}
	//throw DiscNotFoundError("Disciplina nu se afla in lista!");
	float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	if (r < this->probability) {
		throw ProbabilityError{ "Eroare probabilitate" };
	}

	auto it = find_if(this->disciplines.begin(), this->disciplines.end(),
		[name, type](auto pair) {
			return pair.second.getName() == name && pair.second.getType() == type;
		});

	if (it == this->disciplines.end()) {
		throw DiscNotFoundError("Disciplina nu se afla in lista!");
	}
	return it->second;
}

bool RepoLab::exists(const Discipline& discipline) const {
	float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	if (r < this->probability) {
		throw ProbabilityError{ "Eroare probabilitate" };
	}

	try {
		findDiscipline(discipline.getName(), discipline.getType());
		return true;
	}
	catch (DiscNotFoundError&) {
		return false;
	}
}

void RepoLab::addDiscipline(const Discipline& discipline) {
	float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	if (r < this->probability) {
		throw ProbabilityError{ "Eroare probabilitate" };
	}

	if (exists(discipline)) {
		throw DiscExistsError("Disciplina se afla deja in lista!");
	}

	this->disciplines[this->disciplines.size()] = discipline;
}

void RepoLab::removeDiscipline(const string& name, const string& type) {
	float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	if (r < this->probability) {
		throw ProbabilityError{ "Eroare probabilitate" };
	}

	auto it = find_if(this->disciplines.begin(), this->disciplines.end(), [name, type](auto pair) {
		return pair.second.getName() == name && pair.second.getType() == type;
		});

	if (it == this->disciplines.end()) {
		throw DiscNotFoundError("Disciplina nu se afla in lista!");
	}
	this->disciplines.erase(it);
}

