#include "RezizeAction.h"
#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"


RezizeAction::RezizeAction(ApplicationManager* pApp, CFigure* selected) :Action(pApp), Selected(selected)
{}

void RezizeAction::Execute()
{
	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();
	pGUI->CreateSizeToolBar();

	if (Selected != NULL) {
	     ActionType pAct = pGUI->MapInputToActionType();
		if (pAct == QUARTER) {
			Selected->setSize(.25);
			Selected->Resize(.25);
			pManager->UpdateInterface();
			pGUI->ClearStatusBar();
			Execute();
		}
		else if (pAct == HALF) {
			Selected->setSize(.5);
			Selected->Resize(.5);
			pManager->UpdateInterface();
			pGUI->ClearStatusBar();
			Execute();
		}
		else if (pAct == DOUBLE1) {
			Selected->setSize(2);
			Selected->Resize(2);
			pManager->UpdateInterface();
			pGUI->ClearStatusBar();
			Execute();
		}
		else if (pAct == QUADRUPLE) {
			Selected->setSize(4);
			Selected->Resize(4);
			pManager->UpdateInterface();
			pGUI->ClearStatusBar();
			Execute();
		}
		else if (pAct == BACK) {
			
		}
	}
	else
		pGUI->PrintMessage("Firstly, Select a fig");
}
