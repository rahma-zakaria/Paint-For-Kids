#pragma once
#include "Action.h"
class RezizeAction :public Action
{
public:
	RezizeAction(ApplicationManager* pApp);

	//Add rsize action to the ApplicationManager
	virtual void Execute();
};

