#pragma once

#include "UndoAction.h"
#include "Discipline.h"
#include "DisciplineRepo.h"

class UndoRemove : public UndoAction {
private:
	Discipline removed;
	Repo& repo;

public:
	UndoRemove(Repo& repo, const Discipline& disc) : removed(disc), repo(repo) {}
	void doUndo() override;
	virtual ~UndoRemove(){}
};