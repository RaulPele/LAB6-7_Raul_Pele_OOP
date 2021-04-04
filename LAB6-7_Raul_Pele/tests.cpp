#include "tests.h"
#include "DisciplineRepo.h"
#include "DisciplineService.h"
#include "Discipline.h"
#include "Errors.h"
#include <assert.h>

void testAddDiscRepo() {
	DisciplineRepo repo;
	Discipline d1 = Discipline("OOP", "Laborator", 2, "AB");
	repo.addDiscipline(d1);
	assert(repo.getAll().at(0) == d1);
	try {
		repo.addDiscipline(d1);
	}
	catch (DiscExistsError& err) {
		assert(err.getMessage() == "Disciplina se afla deja in lista!");
	}
}

void testRemoveDiscRepo(){
	DisciplineRepo repo;
	Discipline d1 = Discipline("OOP", "Laborator", 2, "AB");
	repo.addDiscipline(d1);
	
	repo.removeDiscipline("OOP", "Laborator");

	assert(repo.getAll().size() == 0);

	try {
		repo.removeDiscipline("OOP", "Laboorator");
	}
	catch (DiscNotFoundError& err) {
		assert(err.getMessage() == "Disciplina nu se afla in lista!");
	}
}

void testExistsRepo(){
	DisciplineRepo repo;
	Discipline d1 = Discipline("OOP", "Laborator", 2, "AB");
	repo.addDiscipline(d1);

	assert(repo.exists(d1)== true);
	repo.removeDiscipline("OOP", "Laborator");

	assert(repo.exists(d1) == false);
}

void testsFindDiscRepo(){
	DisciplineRepo repo;
	Discipline d1 = Discipline("OOP", "Laborator", 2, "AB");
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
	DisciplineService srv{ repo };
	srv.addDiscipline("OOP", "Laborator", 2, "AB");

	Discipline d{ "OOP", "Laborator", 2,  "AB" };
	assert(repo.exists(d));

	try {
		srv.addDiscipline("OOP", "Laborator", 2, "AB");
	}
	catch (DiscExistsError& err) {
		assert(err.getMessage() == "Disciplina se afla deja in lista!");
	}
}

void testRemoveDiscSrv() {
	DisciplineRepo repo{};
	DisciplineService srv{ repo };
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
}

void testFindDiscSrv() {
	DisciplineRepo repo{};
	DisciplineService srv{ repo };
	srv.addDiscipline("OOP", "Laborator", 2, "AB");
	
	Discipline d{ "OOP", "Laborator", 2,  "AB" };
	assert(srv.findDiscipline("OOP", "Laborator") == d);

	try {
		srv.findDiscipline("a", "b");
	}
	catch (DiscNotFoundError& err) {
		assert(err.getMessage() == "Disciplina nu se afla in lista!");

	}

}

void testGetAllSrv() {
	DisciplineRepo repo{};
	DisciplineService srv{ repo };
	srv.addDiscipline("OOP", "Laborator", 2, "AB");

	const vector<Discipline>& v = srv.getAll();

	assert(v.size() == repo.getAll().size());
	for (unsigned int i = 0; i < v.size(); i++) {
		assert(v.at(i) == repo.getAll().at(i));
	}
}

void testModifyDiscSrv() {
	DisciplineRepo repo{};
	DisciplineService srv{ repo };
	srv.addDiscipline("OOP", "Laborator", 2, "AB");

	string newName{ "A" }, newType, newTeacher;
	srv.modifyDiscipline("OOP", "Laborator", newName, newType, -1, newTeacher);
	assert(srv.getAll().at(0).getName() == "A");
	newName = "", newType = "A";

	srv.modifyDiscipline("A", "Laborator", newName, newType, -1, newTeacher);
	assert(srv.getAll().at(0).getType() == "A");

	newName = "", newType = "";
	srv.modifyDiscipline("A", "A", newName, newType, 2, newTeacher);
	assert(srv.getAll().at(0).getHoursPerWeek() == 2);

	newTeacher = "A";
	srv.modifyDiscipline("A", "A", newName, newType, -1, newTeacher);
	assert(srv.getAll().at(0).getTeacher() == "A");
}

void testDomain() {
	Discipline d{ "A", "B", 2, "C" };
	assert(d.getName() == "A");
	assert(d.getHoursPerWeek() == 2);
	assert(d.getTeacher() == "C");
	assert(d.getType() == "B");
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
}