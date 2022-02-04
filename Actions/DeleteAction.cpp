#include "DeleteAction.h"
#include "..\ApplicationManager.h"
#include "./../GUI/GUI.h"

DeleteAction::DeleteAction(ApplicationManager * pApp):Action(pApp)
{
	
}

void DeleteAction::ReadActionParameters()
{
	//SelectAction* select = new SelectAction(pManager);

	//select->Execute();
	//picky = select->getSelectedFigure();
	pManager->DeleteMF();
	pManager->UpdateInterface();
	
}

void DeleteAction::Execute()
{
	
	ReadActionParameters();

}
