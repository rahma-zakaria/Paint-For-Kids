#include "ChangeCDCAction.h"

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

	SelectedFigure = pManager->GetSelectedFigures();
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
	if (SelectedColorIndex == 18)
	{
		SelectedColor = BLACK;
		IsSelected = true;
		pGui->PrintMessage("Current Drawing Color changed to BLACK");
	}
	else if (SelectedColorIndex == 19)
	{
		SelectedColor = WHITE;
		IsSelected = true;
		pGui->PrintMessage("Current Drawing Color changed to WHITE");
	}
	else if (SelectedColorIndex == 20)
	{
		SelectedColor = RED;
		IsSelected = true;
		pGui->PrintMessage("Current Drawing Color changed to RED");
	}
	else if (SelectedColorIndex == 21)
	{
		SelectedColor = GREEN;
		IsSelected = true;
		pGui->PrintMessage("Current Drawing Color changed to GREEN");
	}
	else if (SelectedColorIndex == 22)
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
