#pragma once
#include "Discipline.h"
#include "Repo.h"

#include<map>
using namespace std;

class RepoLab : public Repo {
private:
	map<int, Discipline> disciplines;
	float probability;

public:

	RepoLab(float probability): probability(probability){}
/*
Returneaza o referinta const la lista de discipline.
*/

	const vector<Discipline> getAll() const;

	/*
	preconditii: name - const string& -> referinta la numele disciplinei care se cauta
				type - const string& -> referinta la tipul disciplinei care se cauta
	postconditii: return discipline - const Discipline& -> disciplina gasita, daca se afla in lista
	throw DiscNotFoundError - in cazul in care disciplina nu se afla in lista
	*/
	const Discipline& findDiscipline(const string& name, const string& type) const;

	/*
	preconditii: discipline - const Discipline& -> disciplina care se adauga
	Adauga disciplina la lista de discipline.
	throw DiscExistsError - daca disciplina exista deja in lista
	*/
	 void addDiscipline(const Discipline& discipline);

	/*
	preconditii: name - const string& -> referinta la numele disciplinei care se sterge
				type - const string& -> referinta la tipul disciplinei care se sterge
	Sterge disciplina cu numele name si tipul type din lista.
	throw DiscNotFoundError - daca disciplina nu se afla in lista
	*/
	void removeDiscipline(const string& name, const string& type);

	/*
	preconditii: discipline - const Discipline& -> disciplina pentru care se face cautarea
	postconditii: return true- daca disciplina se afla in lista
						false - altfel

	Verifica daca o disciplina se afla in lista.
	*/
	bool exists(const Discipline& discipline) const;
};