#pragma once
#include "Action.h"
#include "..\Figures\CFigure.h"
#include "SelectAction.h"
class RezizeAction :public Action
{
	CFigure* Selected;
public:
	RezizeAction(ApplicationManager* pApp,CFigure*);

	//Add rsize action to the ApplicationManager
	virtual void Execute();
};

