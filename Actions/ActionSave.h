#ifndef ACTION_SAVE_H
#define ACTION_SAVE_H

#include "Action.h"

//SAVE SQUARE Action class
class ActionSave : public Action
{
	string filename;
public:
	ActionSave(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
};

#endif