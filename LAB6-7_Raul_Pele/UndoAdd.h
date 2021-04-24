#pragma once
#include "UndoAction.h"
#include "Discipline.h"
#include "DisciplineRepo.h"

class UndoAdd : public UndoAction {
private:
	Discipline added;
	Repo& repo;

public:
	UndoAdd(Repo& repo, const Discipline& disc): added(disc), repo(repo){}
	
	void doUndo() override;
	virtual ~UndoAdd(){}
};