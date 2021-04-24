#include "UndoAdd.h"

void UndoAdd::doUndo() {
	this->repo.removeDiscipline(this->added.getName(), this->added.getType());
}