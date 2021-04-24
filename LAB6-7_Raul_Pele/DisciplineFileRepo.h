#pragma once
#include "DisciplineRepo.h"
#include "Discipline.h"

#include <string>

class DisciplineFileRepo : public DisciplineRepo {
private:
	void writeToFile();
	void loadFromFile();

public:
	string fileName;

	DisciplineFileRepo(string fileName);
	virtual ~DisciplineFileRepo(){}
	// DisciplineFileRepo& operator=(const DisciplineFileRepo& other) override;

	 void addDiscipline(const Discipline& disc) override;
	 void removeDiscipline(const string& name, const string& type) override;
};