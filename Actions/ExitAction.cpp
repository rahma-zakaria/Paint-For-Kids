#include "ExitAction.h"
#include "ActionSave.h"
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
	pGui->PrintMessage("Sure! ? You want to save your graph before exit ? if yes then write Y or any key to exit");
	string userChoose = pGui->GetSrting();
	if (userChoose == "Y" || userChoose == "y")
	{
		Action* saveAct = new ActionSave(pManager);
		pManager->ExecuteAction(saveAct);
	}
	pManager->ClearAllFig();
	ReadActionParameters();
}
