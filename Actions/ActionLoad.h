#pragma once
#include "Action.h"
class ActionLoad : public Action
{
private:
	string filename;
public:
	ActionLoad(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
};

