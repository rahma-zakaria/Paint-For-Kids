#pragma once
#pragma once
#include "..\Figures\CFigure.h"
#include "..\ApplicationManager.h"

class DeleteAction : public Action 
{
	CFigure* picky;
	

public:
	DeleteAction(ApplicationManager*);
	void ReadActionParameters();
	virtual void Execute();



	////To undo this action (code depends on action type)
	//virtual void Undo();

	////To redo this action (code depends on action type)
	//virtual void Redo();

	//virtual bool CanUndo() const;
};