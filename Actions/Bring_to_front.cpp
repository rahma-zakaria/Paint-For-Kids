#include "Bring_to_front.h"
#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"

Bring_to_front::Bring_to_front(ApplicationManager* pApp) : Action(pApp)
{}

void Bring_to_front::ReadActionParameters()
{}

//Add Bring to front  to the ApplicationManager To Execute it 
void Bring_to_front::Execute()
{
	GUI* pGUI = pManager->GetGUI();
	if (Selected != NULL) {
		pManager->Bring_Front();
		pGUI->PrintMessage("Bring to front");

	}
	else {
		pGUI->PrintMessage("please select a figure");
	}

}