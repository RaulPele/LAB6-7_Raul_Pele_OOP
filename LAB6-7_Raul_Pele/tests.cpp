#include "tests.h"
#include "DisciplineRepo.h"
#include "DisciplineFileRepo.h"
#include "DisciplineService.h"
#include "Discipline.h"
#include "RepoLab.h"
#include "Errors.h"
#include "LinkedList.h"
#include "LIIterator.h"
#include "validators.h"
#include "Contract.h"

#include <vector>
#include <assert.h>
#include <fstream>

void testAddDiscRepo() {
	DisciplineRepo repo;
	Discipline d1{ "OOP", "Laborator", 2, "AB" };
	Discipline d2{ "A", "B", 300, "AB" };
	Discipline d3{ "A", "E", 300, "AE" };

	repo.addDiscipline(d1);
	repo.addDiscipline(d2);
	repo.addDiscipline(d3);

	const vector<Discipline>& disciplines = repo.getAll();
	assert(disciplines.at(0)== d1);
	assert(disciplines.at(1) == d2);
	assert(disciplines.at(2) == d3);

	try {
		repo.addDiscipline(d1);
	}
	catch (DiscExistsError& err) {
		assert(err.getMessage() == "Disciplina se afla deja in lista!");
	}

}

void testRemoveDiscRepo(){
	DisciplineRepo repo;
	Discipline d1{ "OOP", "Laborator", 2, "AB" };
	Discipline d2{ "LC", "Curs", 10, "E" };
	Discipline d3{ "A", "B", 3, "E" };
	Discipline d4{ "Q","W", 30, "Q" };

	repo.addDiscipline(d1);
	repo.addDiscipline(d2);
	repo.addDiscipline(d4);
	repo.addDiscipline(d3);
	

	repo.removeDiscipline("OOP", "Laborator");

	assert(repo.exists(d1) == false);
	assert(repo.exists(d2));
	assert(repo.exists(d3));

	repo.removeDiscipline("A", "B");
	assert(repo.exists(d3) == false);
	assert(repo.exists(d2));


	try {
		repo.removeDiscipline("OOP", "Laboorator");
	}
	catch (DiscNotFoundError& err) {
		assert(err.getMessage() == "Disciplina nu se afla in lista!");
	}
}

void testExistsRepo(){
	DisciplineRepo repo;
	Discipline d1{ "OOP", "Laborator", 2, "AB" };
	repo.addDiscipline(d1);

	assert(repo.exists(d1)== true);
	repo.removeDiscipline("OOP", "Laborator");

	assert(repo.exists(d1) == false);
}

void testsFindDiscRepo(){
	DisciplineRepo repo;
	Discipline d1{ "OOP", "Laborator", 2, "AB" };
	assert(d1.getName() == "OOP");
	repo.addDiscipline(d1);

	Discipline d2=repo.findDiscipline("OOP", "Laborator");
	assert(d2==d1);
	
	try {
		d2 = repo.findDiscipline("w", "Laborator");
	}
	catch (DiscNotFoundError& err) {
		assert(err.getMessage() == "Disciplina nu se afla in lista!");
	}
}

void testAddDiscSrv() {
	DisciplineRepo repo{};
	DisciplineValidator validator{};
	DisciplineService srv{ repo , validator};
	srv.addDiscipline("OOP", "Laborator", 2, "AB");

	Discipline d{ "OOP", "Laborator", 2,  "AB" };
	assert(repo.exists(d));

	try {
		srv.addDiscipline("OOP", "Laborator", 2, "AB");
	}
	catch (DiscExistsError& err) {
		assert(err.getMessage() == "Disciplina se afla deja in lista!");
	}

	try {
		srv.addDiscipline("12324", "123", -123, "123ewq");
		assert(false);
	}
	catch (InvalidDataError&) {
		assert(true);
	}
}

void testRemoveDiscSrv() {
	DisciplineRepo repo{};
	DisciplineValidator validator{};
	DisciplineService srv{ repo , validator };
	srv.addDiscipline("OOP", "Laborator", 2, "AB");

	srv.removeDiscipline("OOP", "Laborator");
	Discipline d{ "OOP", "Laborator", 2,  "AB" };

	assert(repo.exists(d) == false);

	try {
		srv.removeDiscipline("OOP", "Laborator");
		assert(false);
	}
	catch (DiscNotFoundError& err) {
		assert(err.getMessage() == "Disciplina nu se afla in lista!");
	}

	try {
		srv.removeDiscipline("123", "laborator");
		assert(false);
	}
	catch (InvalidDataError&) {
		assert(true);
	}
}

void testFindDiscSrv() {
	DisciplineRepo repo{};
	DisciplineValidator validator{};
	DisciplineService srv{ repo , validator };
	srv.addDiscipline("OOP", "Laborator", 2, "AB");
	
	Discipline d{ "OOP", "Laborator", 2,  "AB" };
	assert(srv.findDiscipline("OOP", "Laborator") == d);

	try {
		srv.findDiscipline("a", "b");
	}
	catch (DiscNotFoundError& err) {
		assert(err.getMessage() == "Disciplina nu se afla in lista!");

	}

	try {
		srv.findDiscipline("1203-", "/?e");
		assert(false);
	}
	catch (InvalidDataError&) {
		assert(true);
	}

}

void testGetAllSrv() {
	DisciplineRepo repo{};
	DisciplineValidator validator{};
	DisciplineService srv{ repo , validator };
	srv.addDiscipline("OOP", "Laborator", 2, "AB");

	vector<Discipline> result;
	result.push_back(Discipline{ "OOP", "Laborator", 2, "AB" });
	const vector<Discipline>& v = srv.getAll();
	assert(v == result);
}

void testModifyDiscSrv() {
	DisciplineRepo repo{};
	DisciplineValidator validator{};
	DisciplineService srv{ repo , validator };
	srv.addDiscipline("OOP", "Laborator", 2, "AB");
	

	string newName{ "A" }, newType, newTeacher;
	srv.modifyDiscipline("OOP", "Laborator", newName, newType, -1, newTeacher);
	assert(repo.getAll().at(0).getName() == "A");
	newName = "", newType = "A";

	srv.modifyDiscipline("A", "Laborator", newName, newType, -1, newTeacher);
	assert(repo.getAll().at(0).getType() == "A");

	newName = "", newType = "";
	srv.modifyDiscipline("A", "A", newName, newType, 2, newTeacher);
	assert(repo.getAll().at(0).getHoursPerWeek() == 2);

	newTeacher = "A";
	srv.modifyDiscipline("A", "A", newName, newType, -1, newTeacher);
	assert(repo.getAll().at(0).getTeacher() == "A");

	newName = "-123";
	try {
		srv.modifyDiscipline("A", "A", newName, newType, -1, newTeacher);
		assert(false);
	}
	catch (InvalidDataError&) {
		assert(true);
	}
}

void testDomain() {
	Discipline d{ "A", "B", 2, "C" };
	assert(d.getName() == "A");
	assert(d.getHoursPerWeek() == 2);
	assert(d.getTeacher() == "C");
	assert(d.getType() == "B");

	string result = "Nume: " + d.getName() + "\n" + \
		"Tip: " + d.getType() + "\n" + \
		"Ore pe saptamana: " + to_string(d.getHoursPerWeek()) + "\n" + \
		"Profesor: " + d.getTeacher() + "\n";
	assert(result == d.toString());
}

void testLinkedList(){
	LinkedList<Discipline> list{};
	Discipline d1{ "A", "B", 2, "C" };
	Discipline d2{ "C", "D", 3, "F" };
	assert(list.size() == 0);
	list.add(d1);
	list.add(d2);
	assert(list.size() == 2);
	LIIterator<Discipline> it = list.begin();
	assert(it.valid() == true);
	assert(it.value() == d1);
	it.next();
	assert(it.value() == d2);
	it.next();
	assert(it.valid() == false);
	
	LIIterator<Discipline> it2 = list.begin();
	list.remove(it2);
	list.remove(it2);
	assert(list.empty() == true);
	
}

void testValidateName() {
	DisciplineValidator validator;

	assert(validator.validateName("123ase") == false);
	assert(validator.validateName("asewqe") == true);

}

void testValidateHours() {
	DisciplineValidator validator;

	assert(validator.validateHoursPerWeek(-100) == false);
	assert(validator.validateHoursPerWeek(100) == true);
}

void testFilterDisciplines() {
	DisciplineRepo repo;
	DisciplineValidator validator;
	DisciplineService srv{ repo, validator};

	Discipline d1{ "A", "B", 2, "A" };
	Discipline d2{ "C", "D", 10, "A" };
	Discipline d3{ "E","F", 10, "B" };

	repo.addDiscipline(d1);
	repo.addDiscipline(d2);
	repo.addDiscipline(d3);

	vector<Discipline> filtered = srv.filterDisciplineByTeacher("A");

	vector<Discipline> results{ d1, d2 };
	assert(results == filtered);

	try {
		srv.filterDisciplineByTeacher("1239124sdfsdf");
		assert(false);
	}
	catch (InvalidDataError&) {
		assert(true);
	}

	filtered = srv.filterDisciplineByHours(10);
	results = { d2, d3 };
	
	assert(filtered == results);

	try {
		srv.filterDisciplineByHours(-123);
		assert(false);
	}
	catch (InvalidDataError&) {
		assert(true);
	}
}

void testSortDisciplines() {
	DisciplineRepo repo;
	DisciplineValidator validator;
	DisciplineService srv{ repo, validator };

	srv.sortDisciplinesByHours("C"); // this should do nothing - empty list

	Discipline d1{ "A", "B", 2, "A" };
	Discipline d2{ "C", "D", 100, "A" };
	Discipline d3{ "E","F", 10, "B" };

	repo.addDiscipline(d1);
	repo.addDiscipline(d2);
	repo.addDiscipline(d3);


	vector<Discipline> sorted = srv.sortDisciplinesByHours("C");
	vector<Discipline> results{ d1, d3, d2 };
	assert(sorted == results);

	sorted = srv.sortDisciplinesByHours("D");
	results = { d2, d3, d1 };
	assert(sorted == results);


	sorted = srv.sortDisciplinesByName("C");
	results = { d1, d2, d3 };
	assert(results == sorted);

	sorted = srv.sortDisciplinesByName("D");
	results = { d3, d2, d1 };
	assert(results == sorted);

	Discipline d4{ "A", "C", 3, "Q" };
	repo.addDiscipline(d4);

	sorted = srv.sortDisciplinesByTeacherAndType("D");
	results = { d4, d3, d2, d1 };
	assert(sorted == results);

	Discipline d5{ "A", "A", 3, "A" };
	Discipline d6{ "B", "B", 3, "B" };
	assert(cmpName(d5, d6) == true);
	assert(cmpTeacherAndType(d5, d6) == true);
}

void testAddToContractSrv() {
	DisciplineRepo repo;
	DisciplineValidator validator;
	DisciplineService srv{ repo, validator };

	Discipline d1{ "A", "B", 2, "A" };
	Discipline d2{ "C", "D", 100, "A" };
	Discipline d3{ "E","F", 10, "B" };

	repo.addDiscipline(d1);
	repo.addDiscipline(d2);
	repo.addDiscipline(d3);

	try {
		srv.addToContract("-3123", "qwe2");
		assert(false);
	}
	catch (InvalidDataError&) {
		assert(true);
	}

	try {
		srv.addToContract("Programare", "ASDASD");
		assert(false);
	}
	catch (DiscNotFoundError&) {
		assert(true);
	}

	srv.addToContract("A", "B");
	assert(srv.getContractDisciplines().at(0).getName() == d1.getName());

	try {
		srv.addToContract("A", "B");
		assert(false);
	}
	catch (DiscExistsError&) {
		assert(true);
	}

	srv.clearContract();
	assert(srv.getContractLength() == 0);

}

void testGenerateContractSrv() {
	DisciplineRepo repo;
	DisciplineValidator validator;
	DisciplineService srv{ repo, validator };

	Discipline d1{ "A", "B", 2, "A" };
	Discipline d2{ "C", "D", 100, "A" };
	Discipline d3{ "E","F", 10, "B" };

	repo.addDiscipline(d1);
	repo.addDiscipline(d2);
	repo.addDiscipline(d3);

	srv.generateContract(3);
	assert(srv.getContractLength() == 3);

	try {
		srv.generateContract(100);
		assert(false);
	}
	catch (OutOfBoundsError&) {
		assert(true);
	}

	try {
		srv.generateContract(-100);
		assert(false);
	}
	catch (InvalidDataError&) {
		assert(true);
	}
	Discipline d4{ "C", "B", 2, "A" };
	repo.addDiscipline(d4);

	srv.getUnique();

	Contract contract{repo};
	contract.add(d1.getName(), d1.getType());
	Contract contract2{ contract };
	assert(contract2.getAll() == contract.getAll());

}

void testCreateReportSrv() {
	DisciplineRepo repo;
	DisciplineValidator validator;
	DisciplineService srv{ repo, validator };

	Discipline d1{ "A", "B", 2, "A" };
	Discipline d2{ "C", "B", 100, "A" };
	Discipline d3{ "E","F", 10, "B" };

	repo.addDiscipline(d1);
	repo.addDiscipline(d2);
	repo.addDiscipline(d3);

	map<string, DisciplineCountDTO> a = srv.createReport();
	assert(a["B"].getCount() == 2);
	assert(a["F"].getCount() ==1);

}

void testFileRepo() {
	ofstream fout("tests.txt");
	fout.close();

	DisciplineFileRepo repo{ "tests.txt" };
	Discipline d1{ "A", "B", 2, "A" };
	

	repo.addDiscipline(d1);
	assert(repo.getAll().size() == 1);
	
	DisciplineFileRepo repo2{ "tests.txt" };
	assert(repo2.getAll().size() == 1);
	repo2.removeDiscipline(d1.getName(), d1.getType());

	DisciplineFileRepo repo3{ "tests.txt" };
	assert(repo3.getAll().size() == 0);

	remove("tests.txt");

}

void testUndo() {
	DisciplineRepo repo;
	Discipline d1{ "A", "B", 2, "A" };
	DisciplineService srv{ repo, DisciplineValidator() };
	string newName = "ASD", newTeacher = "", newType = "";
	int newHrs = -1;

	srv.addDiscipline(d1.getName(), d1.getType(), d1.getHoursPerWeek(), d1.getTeacher());
	srv.modifyDiscipline(d1.getName(), d1.getType(), newName, newType, newHrs, newTeacher);
	srv.removeDiscipline(newName, d1.getType());
	
	srv.undo();
	assert(srv.getAll().size() == 1);;
	srv.undo();
	assert(srv.getAll().at(0).getName() == "A");
	srv.undo();
	assert(srv.getAll().empty() == true);
	try {
		srv.undo();
		assert(false);
	}
	catch (ServiceError&) {
		assert(true);
	}
}

void testAddRepoLab() {
	float p = (float)0.6;
	RepoLab repo{p};
	Discipline d1{ "OOP", "Laborator", 2, "AB" };
	Discipline d2{ "A", "B", 300, "AB" };
	Discipline d3{ "A", "E", 300, "AE" };

	try {
		repo.addDiscipline(d1);
		repo.addDiscipline(d2);
		repo.addDiscipline(d3);
	}
	catch (ProbabilityError&) {
		assert(true);
		return;
	}

	const vector<Discipline>& disciplines = repo.getAll();
	assert(disciplines.at(0) == d1);
	assert(disciplines.at(1) == d2);
	assert(disciplines.at(2) == d3);

	try {
		repo.addDiscipline(d1);
	}
	catch (DiscExistsError& err) {
		assert(err.getMessage() == "Disciplina se afla deja in lista!");
	}
	catch (ProbabilityError& ) {
		assert(true);
	}
	
}

void testRemoveRepoLab() {
	float p = (float)0.6;
	RepoLab repo{ p };
	Discipline d1{ "OOP", "Laborator", 2, "AB" };
	Discipline d2{ "LC", "Curs", 10, "E" };
	Discipline d3{ "A", "B", 3, "E" };
	Discipline d4{ "Q","W", 30, "Q" };

	try {
		repo.addDiscipline(d1);
		repo.addDiscipline(d2);
		repo.addDiscipline(d4);
		repo.addDiscipline(d3);
	}
	catch (ProbabilityError&) {
		assert(true);
		return;
	}

	try {
		repo.removeDiscipline("OOP", "Laborator");
	}
	catch (ProbabilityError&) {
		assert(true);
		return;
	}

	try {
		assert(repo.exists(d1) == false);
		assert(repo.exists(d2));
		assert(repo.exists(d3));

		repo.removeDiscipline("A", "B");
		assert(repo.exists(d3) == false);
		assert(repo.exists(d2));
	}
	catch (ProbabilityError&) {
		assert(true);
		return;
	}


	try {
		repo.removeDiscipline("OOP", "Laboorator");
	}
	catch (DiscNotFoundError& err) {
		assert(err.getMessage() == "Disciplina nu se afla in lista!");
	}
	catch (ProbabilityError&) {
		assert(true);
		return;
	}
}

void runTests() {
	testAddDiscRepo();
	testRemoveDiscRepo();
	testExistsRepo();
	testsFindDiscRepo();
	testAddDiscSrv();
	testRemoveDiscSrv();
	testFindDiscSrv();
	testGetAllSrv();
	testModifyDiscSrv();
	testDomain();
	testLinkedList();
	testValidateHours();
	testValidateName();
	testFilterDisciplines();
	testSortDisciplines();
	testAddToContractSrv();
	testGenerateContractSrv();
	testCreateReportSrv();
	testFileRepo();
	testUndo();
	testAddRepoLab();
	testRemoveRepoLab();
}
