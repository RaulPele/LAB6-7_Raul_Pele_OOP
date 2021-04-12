#pragma once

#include <vector>
#include <string>

#include "Discipline.h"
#include "DisciplineRepo.h"
using namespace std;

class Contract {
private:
	vector<Discipline> disciplines;
	DisciplineRepo& discRepo;
public:
	//constructors
	Contract(DisciplineRepo& repo): discRepo(repo){};
	Contract(const Contract& other);

	//operators
	Contract& operator= (const Contract& other);

	//interface
	/*
	* preconditii: name - const string& numele disciplinei care se adauga in contract
	*				type - const string& tipul disciplinei care se adauga in contract
	* postconditii: lista de discipline se actualizeaza
	* 
	* adauga o disciplina in contract
	* throw DiscNotFoundError daca disciplina nu exista in repo
	* throw DiscExistsError daca disciplina se afla deja in contract
	*/
	void add(const string& name, const string& type);
	
	/*
	* postconditii: se goleste lista disciplinelor din contract
	* 
	* Sterge toate disciplinele din contract.
	*/
	void clear();

	/*
	* precoditii: destFile - const string& numele fisierului in care se salveaza
	* postconditii: se creaza un fisier HTML continand contractul
	* 
	* Exporta un contract in fisier HTML.
	*/
	void exportContract(const string& destFile);

	vector<Discipline>& getAll();

};