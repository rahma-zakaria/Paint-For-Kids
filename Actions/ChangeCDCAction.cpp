#include "ChangeCDCAction.h"
#include <iostream>
#include "..\Figures\CEllipse.h"
#include "..\Figures\CHexagon.h"
#include "..\Figures\CSquare.h"

#include "../GUI/GUI.h"

#include "..\ApplicationManager.h"



ChangeCDCAction::ChangeCDCAction(ApplicationManager* pApp) :Action(pApp)
{
	IsSelected = false;
}

void ChangeCDCAction::ReadActionParameters()
{
	////Get a Pointer to the Input / Output Interfaces
	//Output* pOut = pManager->GetOutput();
	//Input* pIn = pManager->GetInput();

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
	if (SelectedColorIndex == 27)
	{
		SelectedColor = BLACK;
		IsSelected = true;
		pGui->PrintMessage("Current Drawing Color changed to BLACK");
	}
	else if (SelectedColorIndex == 28)
	{
		SelectedColor = WHITE;
		IsSelected = true;
		pGui->PrintMessage("Current Drawing Color changed to WHITE");
	}
	else if (SelectedColorIndex == 29)
	{
		SelectedColor = RED;
		IsSelected = true;
		pGui->PrintMessage("Current Drawing Color changed to RED");
	}
	else if (SelectedColorIndex == 30)
	{
		SelectedColor = GREEN;
		IsSelected = true;
		pGui->PrintMessage("Current Drawing Color changed to GREEN");
	}
	else if (SelectedColorIndex == 31)
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
