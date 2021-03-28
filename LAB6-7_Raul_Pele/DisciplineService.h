#pragma once
#include "DisciplineRepo.h"
#include <string>
#include <vector>
using namespace std;

class DisciplineService {
private:
	DisciplineRepo& discRepo;

public:
	DisciplineService(DisciplineRepo& discRepo) : discRepo(discRepo) {};

	/*
	preconditii:  name - const string& name -> numele disciplinei care se adauga
				 type - const string& type -> tipul disciplinei care se adauga
				 hoursPerWeek -const int -> numarul de ore pe saptamana a discipplinei care se adauga
				 teacher - const string& -> profesorul disciplinei care se adauga

	Adauga disciplina la lista de discipline.
	throw DiscExistsError - daca disciplina exista deja in lista
	*/
	void addDiscipline(const string& name, const string& type, const int hoursPerWeek, const string& teacher);

	/*
	preconditii:  name - const string& name -> numele disciplinei care se sterge
				 type - const string& type -> tipul disciplinei care se sterge
				 hoursPerWeek -const int -> numarul de ore pe saptamana a discipplinei care se sterge
				 teacher - const string& -> profesorul disciplinei care se sterge

	Sterge disciplina cu numele name si tipul type din lista.
	throw DiscNotFoundError - daca disciplina nu se afla in lista
	*/
	void removeDiscipline(const string& name, const string& type);

	/*
	preconditii:  name - const string& name -> numele disciplinei care se modifica
				 type - const string& type -> tipul disciplinei care se modifica
				 newName - string& -> noul nume al disciplinei - "" daca nu se modifica
				 newType - string& -> noul tip al disciplinei - "" daca nu se modifica
				 newHours - int -> nr nou de ore pe sapt - -1 daca nu se modifica
				 newTeacher - string& -> noul profesor al disciplinei - "" daca nu se modifica


	Modifica o disciplina din lista.
	throw DiscNotFoundError - daca disciplina nu se afla in lista
	*/
	void modifyDiscipline(const string& name, const string& type,  string& newName,  string& newType,  int newHours,  string& newTeacher);
	
	/*
	Returneaza referinta constnata la lista de discipline.
	*/
	const vector<Discipline>& getAll() const;

	/*
	preconditii: name - const string& -> referinta la numele disciplinei care se cauta
				type - const string& -> referinta la tipul disciplinei care se cauta
	postconditii: return discipline - const Discipline& -> disciplina gasita, daca se afla in lista
	throw DiscNotFoundError - in cazul in care disciplina nu se afla in lista
	*/
	const Discipline& findDiscipline(const string& name, const string& type);
	
};