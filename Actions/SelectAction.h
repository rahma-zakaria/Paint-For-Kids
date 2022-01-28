#pragma once
#include "Action.h"
#include "./../GUI/GUI.h"


class SelectAction : public Action 
{
public:
	SelectAction(ApplicationManager* pApp);
	GUI* pGUI;
	ApplicationManager *pApp;
	virtual void Execute();
};