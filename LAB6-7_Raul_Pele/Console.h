#pragma once
#include "DisciplineService.h"
#include <vector>
#include <string>

class Console {
private:
	DisciplineService& discSrv;

public:
	Console(DisciplineService& discSrv) noexcept : discSrv(discSrv) {}

	/*
	Adauga o disciplina in lista.
	*/
	void addDiscipline();

	/*
	Sterge o disciplina din lista.
	*/
	void removeDiscipline();

	/*
	Gaseste o disciplina din lista si o afiseaza.
	*/
	void findDiscipline() const;

	/*
	Afiseaza toate disciplinele listei.
	*/
	void printDisciplines(const vector<Discipline>& disciplines) const;

	/*
	Afiseaza meniul aplicatiei
	*/
	void displayMenu() const;

	/*
	Funcita principala care ruleaza programul.
	*/
	void run();

	/*
	Citeste o optiune de la utilizator si o returneaza.
	*/
	int readOption(const vector<string>& options) const;

	/*
	Afiseaza o disciplina primita ca parametru.
	*/
	void printDisc(const Discipline& disc) const;

	/*
	Modifica o disciplina din lista.
	*/
	void modifyDiscipline();

	/*
	Filtreaza disciplinele dupa un criteriu.
	*/
	void filterDisciplines();

	/*
	Filtreaza disciplinele dupa ore.
	*/
	void filterDisciplineByHours();
	
	/*
	Filtreaza disciplinele dupa profesor.
	*/
	void filterDisciplineByTeacher();

	/*
	Sorteaza disciplinele dupa un criteriu.
	*/
	void sortDisciplines();

	/*
	Adauga o disciplina la contractul de studiu.
	*/
	void addToContract();

	/*
	Genereaza un contract aleator.
	*/
	void generateContract();

	/*
	Exporta contractul in format html.
	*/
	void exportContract();

	/*Goleste contractul
	*/
	void clearContract();

	void createReport();

};