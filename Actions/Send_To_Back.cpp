#include "Send_To_Back.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"

Send_To_Back::Send_To_Back(ApplicationManager* pApp) :Action(pApp)
{}

void Send_To_Back::ReadActionParameters()
{}

//Add Bring to front  to the ApplicationManager To Execute it 
void Send_To_Back::Execute()
{
	GUI* pGUI = pManager->GetGUI();
	if (Selected != NULL) {
		pManager->Send_Back();
		pGUI->PrintMessage("Bring to front");

	}
	else {
		pGUI->PrintMessage("please select a figure");
	}

}