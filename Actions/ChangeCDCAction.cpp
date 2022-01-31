#include "ChangeCDCAction.h"
#include <iostream>
#include "../Figures/CEllipse.h"
#include "../Figures/CHexagon.h"
#include "../Figures/CSquare.h"

#include "../ApplicationManager.h"

#include "../GUI/GUI.h"


ChangeCDCAction::ChangeCDCAction(ApplicationManager* pApp) :Action(pApp)
{
	IsSelected = false;
}

void ChangeCDCAction::ReadActionParameters()
{

	GUI* pGui = pManager->GetGUI();

	SelectedFigure = pManager->getSelectedFig();
	if (SelectedFigure == NULL)
	{
		pGui->PrintMessage("Select Color to Change Current Drawing Color");
		
	}
	else
	{
		pGui->PrintMessage("Select Color to Change Drawing Color of Selected Figure");
	}
	SelectedColorIndex = pManager->GetUserAction();
	pGui->ClearStatusBar();
}

void ChangeCDCAction::Execute()
{
	GUI* pGui = pManager->GetGUI();
	ReadActionParameters();
	std::cout << SelectedColorIndex;
	if (SelectedColorIndex == COLOR_BLACK)
	{
		SelectedColor = BLACK;
		IsSelected = true;
		pGui->PrintMessage("Current Drawing Color changed to BLACK");

	}
	else if (SelectedColorIndex == COLOR_WHITE)
	{
		SelectedColor = WHITE;
		IsSelected = true;
		pGui->PrintMessage("Current Drawing Color changed to WHITE");
	}
	else if (SelectedColorIndex == COLOR_RED)
	{
		SelectedColor = RED;
		IsSelected = true;
		pGui->PrintMessage("Current Drawing Color changed to RED");
	}
	else if (SelectedColorIndex == COLOR_GREEN)
	{
		SelectedColor = GREEN;
		IsSelected = true;
		pGui->PrintMessage("Current Drawing Color changed to GREEN");
	}
	else if (SelectedColorIndex == COLOR_BLUE)
	{
		SelectedColor = BLUE;
		IsSelected = true;
		pGui->PrintMessage("Current Drawing Color changed to BLUE");
	}
	else
	{
		pGui->PrintMessage("No Color has been selected");
	}

	if (SelectedFigure == NULL)
	{
		if (IsSelected)
		{
			pManager->ChangeCDrawingColor(SelectedColor);
		}
	}
	else
	{
		pManager->ChangeSDrawingColor(SelectedColor);
	}
}
