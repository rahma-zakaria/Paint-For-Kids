#include "RezizeAction.h"
#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"


RezizeAction::RezizeAction(ApplicationManager* pApp) :Action(pApp)
{}

void RezizeAction::Execute()
{
	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();
	pGUI->CreateSizeToolBar();
}
