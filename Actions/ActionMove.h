#pragma once
#include "Action.h"

class ActionMove : public Action
{
public:
	ActionMove(ApplicationManager *pApp);
	virtual void Execute();
};
