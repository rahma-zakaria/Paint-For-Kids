#include "ActionChangeBgColor.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"
#include <iostream>

ActionChangeBgColor::ActionChangeBgColor(ApplicationManager* pApp) : Action(pApp)
{}

void ActionChangeBgColor::ReadActionParameters()
{
	//Get a Pointer to the GUI  Interfaces
	GUI * pGui = pManager->GetGUI();

	pGui->PrintMessage("Select Color to Change Background Color");

	SelectedColorIndex = pManager->GetUserAction();
	pGui->ClearStatusBar();
}

//Execute the action
void ActionChangeBgColor::Execute()
{
    GUI* pOut = pManager->GetGUI();
    ReadActionParameters();

    pOut->PrintMessage("Select a Background color");
	if (SelectedColorIndex == COLOR_BLACK)
	{
		SelectedColor = BLACK;
		if (SelectedFigure == NULL) pOut->PrintMessage("Background Color changed to BLACK");
	}
	else if (SelectedColorIndex == COLOR_WHITE)
	{
		SelectedColor = WHITE;
		if (SelectedFigure == NULL) pOut->PrintMessage("Background Color changed to WHITE");
	}
	else if (SelectedColorIndex == COLOR_RED)
	{
		SelectedColor = RED;
		if (SelectedFigure == NULL) pOut->PrintMessage("Background Color changed to RED");
	}
	else if (SelectedColorIndex == COLOR_GREEN)
	{
		SelectedColor = GREEN;
		if (SelectedFigure == NULL) pOut->PrintMessage("Background Color changed to GREEN");
	}
	else if (SelectedColorIndex == COLOR_BLUE)
	{
		SelectedColor = BLUE;
		if (SelectedFigure == NULL) pOut->PrintMessage("Background Color changed to BLUE");
	}
	else
	{
		pOut->PrintMessage("No Color has been selected");
	}

	pOut->setCrntBackgroundColor(SelectedColor);
}