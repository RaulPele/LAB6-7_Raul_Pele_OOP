#include "UndoRemove.h"

void UndoRemove::doUndo() {
	this->repo.addDiscipline(this->removed);
}