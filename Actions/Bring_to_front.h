#pragma once
#include "Action.h"
#include "..\Figures\CFigure.h"
class Bring_to_front :public Action
{
	CFigure* Selected;
public:
	Bring_to_front(ApplicationManager* pApp);

	virtual void ReadActionParameters();


	virtual void Execute();

};

