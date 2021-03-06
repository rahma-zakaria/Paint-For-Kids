#pragma once
#include "Action.h"

// add ellipse class
class AddElliAction :public Action
{
private:
	// A Point For Ellipse Center
	Point P1, P2;
	// Object of Graphical Struct
	GfxInfo EllipseGfxInfo;

public:
	AddElliAction(ApplicationManager* pApp);

	//Add Ellipse to the ApplicationManager
	virtual void Execute();
};

