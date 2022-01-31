#include "ChangeCFCAction.h"

#include "../Figures/CEllipse.h"
#include "../Figures/CHexagon.h"
#include "../Figures/CSquare.h"

#include "../ApplicationManager.h"

#include "../GUI/GUI.h"

ChangeCFCAction::ChangeCFCAction(ApplicationManager* pApp) :Action(pApp)
{
	IsSelected = false;
}

void ChangeCFCAction::ReadActionParameters()
{
	//Get a Pointer to the GUI  Interfaces
	GUI * pGui = pManager->GetGUI();

	SelectedFigure = pManager->getSelectedFig();
	if (SelectedFigure == NULL)
	{
		pGui->PrintMessage("Select Color to Change Current Fill Color");
	}
	else
	{
		pGui->PrintMessage("Select Color to Change Fill Color of Selected Figure");
	}
	SelectedColorIndex = pManager->GetUserAction();
	pGui->ClearStatusBar();
}

void ChangeCFCAction::Execute()
{
	GUI * pOut = pManager->GetGUI();
	ReadActionParameters();


	if (SelectedColorIndex == COLOR_BLACK)
	{
		SelectedColor = BLACK;
		IsSelected = true;
		if (SelectedFigure == NULL) pOut->PrintMessage("Fill Color changed to BLACK");
	}
	else if (SelectedColorIndex == COLOR_WHITE)
	{
		SelectedColor = WHITE;
		IsSelected = true;
		if (SelectedFigure == NULL) pOut->PrintMessage("Fill Color changed to WHITE");
	}
	else if (SelectedColorIndex == COLOR_RED)
	{
		SelectedColor = RED;
		IsSelected = true;
		if (SelectedFigure == NULL) pOut->PrintMessage("Fill Color changed to RED");
	}
	else if (SelectedColorIndex == COLOR_GREEN)
	{
		SelectedColor = GREEN;
		IsSelected = true;
		if (SelectedFigure == NULL) pOut->PrintMessage("Fill Color changed to GREEN");
	}
	else if (SelectedColorIndex == COLOR_BLUE)
	{
		SelectedColor = BLUE;
		IsSelected = true;
		if (SelectedFigure == NULL) pOut->PrintMessage("Fill Color changed to BLUE");
	}
	else
	{
		pOut->PrintMessage("No Color has been selected");
	}
	if (SelectedFigure == NULL)
	{
		if (IsSelected)
		{
			pManager->ChangeCFillColor(SelectedColor);
			if (!UI.FillFigures) pOut->PrintMessage("Current Fill Color changed to No Fill");
		}
	}
	else
	{
		pManager->ChangeSFillColor(SelectedColor);

	}

}
