#ifndef EXIT_ACTION_H
#define EXIT_ACTION_H

#include "Action.h"

class ExitAction : public Action
{
public:
	ExitAction(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
};

#endif