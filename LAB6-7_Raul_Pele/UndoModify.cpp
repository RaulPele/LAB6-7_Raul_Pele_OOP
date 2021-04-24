#include "UndoModify.h"

void UndoModify::doUndo() {
	this->repo.removeDiscipline(modified.getName(), modified.getType());
	this->repo.addDiscipline(old);
}