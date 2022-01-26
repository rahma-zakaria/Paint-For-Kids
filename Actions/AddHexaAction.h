#pragma once
#include "Action.h"
class AddHexaAction :public Action
{
	// add hexa class

private:
	// A Point For hexa Center
	Point P1, P2;
	// Object of Graphical Struct
	GfxInfo HexapseGfxInfo;

public:
	AddHexaAction(ApplicationManager* pApp);

	//Add H to the ApplicationManager
	virtual void Execute();
};



