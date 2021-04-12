#pragma once
#include "DisciplineRepo.h"
#include "Contract.h"
#include "validators.h"
#include "DisciplineCountDTO.h"

#include <string>
#include <vector>
#include <map>
using namespace std;


class DisciplineService {
private:
	DisciplineRepo& discRepo;
	Contract contract;
	const DisciplineValidator& validator;

public:
	//DisciplineService(DisciplineRepo& discRepo) : discRepo(discRepo){};
	DisciplineService(DisciplineRepo& discRepo, const DisciplineValidator& validator) : discRepo(discRepo), validator(validator),
									contract(discRepo){};

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
	
	/*
	preconditii: teacher - const string&  -> referinta la numele profesorului dupa care se filtreaza
	postconditii: returneaza o lista de discipline avand profesorul teacher
	*/
	const vector<Discipline> filterDisciplineByTeacher(const string& teacher);

	/*
	preconditii: hoursPerWeek - const int  -> numarul de ore pe saptamana dupa care se filtreaza
	postconditii: returneaza o lista de discipline avand numarul de ore pe saptamana hoursPerWeek
	*/
	const vector<Discipline> filterDisciplineByHours(const int hoursPerWeek);

	/*
	preconditii: mode - string modul in care se face sortarea
	postconditii: return sorted - const vector<Discipline> contine disciplinele sortate dupa nume

	Sorteaza disciplinele dupa nume si returneaza rezultatul.
	*/
	const vector<Discipline> sortDisciplinesByName(string mode);

	/*
	preconditii: mode - string modul in care se face sortarea
	postconditii: return sorted - const vector<Discipline> contine disciplinele sortate dupa numarul de ore pe saptamana

	Sorteaza disciplinele dupa numarul de ore pe saptamana si returneaza rezultatul.
	*/
	const vector<Discipline> sortDisciplinesByHours(string mode);

	/*
	preconditii: mode - string modul in care se face sortarea
	postconditii: return sorted - const vector<Discipline> contine disciplinele sortate dupa profesor si tip

	Sorteaza disciplinele dupa profesor si tip si returneaza rezultatul.
	*/
	const vector<Discipline> sortDisciplinesByTeacherAndType(string mode);

	
	/*
	* preconditii: name - const string& numele disciplinei care se adauga in contract
	*				type - const string& tipul disciplinei care se adauga in contract
	* postconditii: lista de discipline se actualizeaza. returneaza disciplinele ramase disponibile de a fi adaugate in contract
	* 
	* adauga o disciplina in contract
	* throw DiscNotFoundError daca disciplina nu exista in repo
	* throw DiscExistsError daca disciplina se afla deja in contract
	*/
	void addToContract(const string& name, const string& type);

	/*
	Genereaza un contract cu discipline aleatorii.
	*/
	void generateContract(int nrOfDisc);

	/*
	Goleste contractul.
	*/
	void clearContract();

	/*
	Exporta contractul in format html.
	*/
	void exportContract(const string& destFile);

	int getContractLength();

	vector<Discipline>& getContractDisciplines();

	vector<Discipline> getUnique();

	map<string, DisciplineCountDTO> createReport();

};