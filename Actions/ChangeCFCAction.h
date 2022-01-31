#ifndef CHANGE_C_F_C_ACTION_H
#define CHANGE_C_F_C_ACTION_H

#include "Action.h"
#include "..\CMUgraphicsLib\colors.h"
#include "..\Figures\CFigure.h"

class ChangeCFCAction : public Action
{
	int SelectedColorIndex;
	color SelectedColor;
	bool IsSelected;
	CFigure* SelectedFigure;
public:
	ChangeCFCAction(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
};

#endif