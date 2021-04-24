#pragma once
#include "Discipline.h"
#include <vector>
#include <map>
using namespace std;


class Repo {
private:
	
public:

/*
Returneaza o referinta const la lista de discipline.
*/

	virtual const vector<Discipline> getAll() const = 0;

	/*
	preconditii: name - const string& -> referinta la numele disciplinei care se cauta
				type - const string& -> referinta la tipul disciplinei care se cauta
	postconditii: return discipline - const Discipline& -> disciplina gasita, daca se afla in lista
	throw DiscNotFoundError - in cazul in care disciplina nu se afla in lista
	*/
	virtual const Discipline& findDiscipline(const string& name, const string& type) const= 0;

	/*
	preconditii: discipline - const Discipline& -> disciplina care se adauga
	Adauga disciplina la lista de discipline.
	throw DiscExistsError - daca disciplina exista deja in lista
	*/
	virtual void addDiscipline(const Discipline& discipline)=0;

	/*
	preconditii: name - const string& -> referinta la numele disciplinei care se sterge
				type - const string& -> referinta la tipul disciplinei care se sterge
	Sterge disciplina cu numele name si tipul type din lista.
	throw DiscNotFoundError - daca disciplina nu se afla in lista
	*/
	virtual void removeDiscipline(const string& name, const string& type)=0;

	/*
	preconditii: discipline - const Discipline& -> disciplina pentru care se face cautarea
	postconditii: return true- daca disciplina se afla in lista
						false - altfel

	Verifica daca o disciplina se afla in lista.
	*/
	virtual bool exists(const Discipline& discipline) const=0;
};