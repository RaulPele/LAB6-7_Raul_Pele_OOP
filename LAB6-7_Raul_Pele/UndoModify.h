#pragma once

#include "UndoAction.h"
#include "Discipline.h"
#include "DisciplineRepo.h"

class UndoModify : public UndoAction {
private:
	Discipline modified, old;
	Repo& repo;

public:
	UndoModify(Repo& repo, const Discipline& old, const Discipline& modified) : modified(modified), repo(repo),
						old(old){}
	void doUndo() override;
	virtual ~UndoModify()
	{}
};