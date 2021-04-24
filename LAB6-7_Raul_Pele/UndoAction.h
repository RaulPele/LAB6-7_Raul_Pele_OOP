#pragma once
class UndoAction {
public:
	virtual void doUndo() = 0;
	virtual ~UndoAction(){}
};