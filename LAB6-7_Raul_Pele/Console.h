#pragma once
#include "DisciplineService.h"
#include <vector>
#include <string>

class Console {
private:
	DisciplineService& discSrv;

public:
	Console(DisciplineService& discSrv): discSrv(discSrv){}

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
	void printDisciplines() const;

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
};