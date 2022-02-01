#pragma once
#include "Action.h"
#include "..\Figures\CFigure.h"
class Send_To_Back :public Action

{
	CFigure* Selected;
public:
	Send_To_Back(ApplicationManager* pApp);

	virtual void ReadActionParameters();


	virtual void Execute();
};

