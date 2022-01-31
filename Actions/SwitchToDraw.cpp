#include "SwitchToDraw.h"
#include "..\ApplicationManager.h"

SwitchToDraw::SwitchToDraw(ApplicationManager * pApp):Action(pApp)
{}

void SwitchToDraw::ReadActionParameters()
{	
	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();
	pGUI->PrintMessage("Back To DrawMode");
}

void SwitchToDraw::Execute()
{
	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();

	ReadActionParameters();

	ifstream MyFile;
	MyFile.open("tempSave.txt", ios::app);

	// Read from the text file
	pManager->LoadAll(MyFile);
	MyFile.close();
}
