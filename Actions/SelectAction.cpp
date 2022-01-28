#include "SelectAction.h"
#include "./../Figures/CSquare.h"
#include "./../Figures/CEllipse.h"
#include "./../Figures/CHexagon.h"
#include "./../Figures/CFigure.h"
#include "./../ApplicationManager.h"

SelectAction::SelectAction(ApplicationManager* pApp): Action(pApp)
{
	this->pApp = pApp
}

void SelectAction::Execute()
{
	
}
