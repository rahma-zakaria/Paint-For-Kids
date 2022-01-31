#include "ExitAction.h"

#include "..\ApplicationManager.h"

#include "./../GUI/GUI.h"

ExitAction::ExitAction(ApplicationManager* pApp) :Action(pApp)
{}

void ExitAction::ReadActionParameters()
{
	GUI* pGui = pManager->GetGUI();
	pGui->PrintMessage("EXIT");
	pGui->ClearStatusBar();
}

void ExitAction::Execute()
{
	GUI* pGui = pManager->GetGUI();
	pManager->ClearAllFig();
	ReadActionParameters();
}
