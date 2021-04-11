#include "tests.h"
#include "DisciplineRepo.h"
#include "DisciplineService.h"
#include "Discipline.h"
#include "Errors.h"
#include "LinkedList.h"
#include "LIIterator.h"
#include "validators.h"
#include <assert.h>

void testAddDiscRepo() {
	DisciplineRepo repo;
	Discipline d1{ "OOP", "Laborator", 2, "AB" };
	Discipline d2{ "A", "B", 300, "AB" };
	Discipline d3{ "A", "E", 300, "AE" };

	repo.addDiscipline(d1);
	repo.addDiscipline(d2);
	repo.addDiscipline(d3);

	LIIterator<Discipline> it = repo.getAll().begin();
	assert( it.value()== d1);
	it.next();
	assert(it.value() == d2);
	it.next();
	assert(it.value() == d3);

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

	const LinkedList<Discipline>& v = srv.getAll();
	LIIterator<Discipline> itV = v.begin();

	LIIterator<Discipline> itRep = repo.getAll().begin();


	assert(v.size() == repo.getAll().size());
	for (unsigned int i = 0; i < v.size(); i++) {
		assert(itV.value() == itRep.value());
		itV.next();
		itRep.next();
	}
	assert(itV.valid() == false);
	assert(itRep.valid() == false);
}

void testModifyDiscSrv() {
	DisciplineRepo repo{};
	DisciplineValidator validator{};
	DisciplineService srv{ repo , validator };
	srv.addDiscipline("OOP", "Laborator", 2, "AB");
	

	string newName{ "A" }, newType, newTeacher;
	srv.modifyDiscipline("OOP", "Laborator", newName, newType, -1, newTeacher);
	LIIterator<Discipline> it = repo.getAll().begin();
	assert(it.value().getName() == "A");
	newName = "", newType = "A";

	srv.modifyDiscipline("A", "Laborator", newName, newType, -1, newTeacher);
	LIIterator<Discipline> it2 = repo.getAll().begin();
	assert(it2.value().getType() == "A");

	newName = "", newType = "";
	srv.modifyDiscipline("A", "A", newName, newType, 2, newTeacher);
	LIIterator<Discipline> it3 = repo.getAll().begin();
	assert(it3.value().getHoursPerWeek() == 2);

	newTeacher = "A";
	srv.modifyDiscipline("A", "A", newName, newType, -1, newTeacher);
	LIIterator<Discipline> it4 = repo.getAll().begin();
	assert(it4.value().getTeacher() == "A");

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

	LinkedList<Discipline> filtered = srv.filterDisciplineByTeacher("A");

	LIIterator<Discipline> it = filtered.begin();
	assert(it.value() == d1);
	it.next();
	assert(it.value() == d2);

	try {
		srv.filterDisciplineByTeacher("1239124sdfsdf");
		assert(false);
	}
	catch (InvalidDataError&) {
		assert(true);
	}

	filtered = srv.filterDisciplineByHours(10);
	auto it2 = filtered.begin();
	assert(it2.value() == d2);
	it2.next();
	assert(it2.value() == d3);

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


	LinkedList<Discipline> sorted = srv.sortDisciplinesByHours("C");
	auto it = sorted.begin();
	assert(it.value() == d1);
	it.next();
	assert(it.value() == d3);
	it.next();
	assert(it.value() == d2);

	sorted = srv.sortDisciplinesByHours("D");
	auto it2 = sorted.begin();
	assert(it2.value() == d2);
	it2.next();
	assert(it2.value() == d3);
	it2.next();
	assert(it2.value() == d1);


	sorted = srv.sortDisciplinesByName("C");
	auto it3 = sorted.begin();
	assert(it3.value() == d1);
	it3.next();
	assert(it3.value() == d2);
	it3.next();
	assert(it3.value() == d3);

	sorted = srv.sortDisciplinesByName("D");
	auto it4 = sorted.begin();
	assert(it4.value().getName() == "E");
	it4.next();
	assert(it4.value().getName() == "C");
	it4.next();
	assert(it4.value().getName() == "A");

	Discipline d4{ "A", "C", 3, "Q" };
	repo.addDiscipline(d4);

	sorted = srv.sortDisciplinesByTeacherAndType("D");
	auto it5 = sorted.begin();

	assert(it5.value().getTeacher() == "Q");
	assert(it5.value().getType() == "C");
	it5.next();

	assert(it5.value().getTeacher() == "B");
	assert(it5.value().getType() == "F");
	it5.next();


	assert(it5.value().getTeacher() == "A");
	assert(it5.value().getType() == "D");
	it5.next();

	assert(it5.value().getTeacher() == "A");
	assert(it5.value().getType() == "B");
	it5.next();

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
}