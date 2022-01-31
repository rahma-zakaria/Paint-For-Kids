#include "SwitchToPlay.h"
#include "..\ApplicationManager.h"

SwitchToPlay::SwitchToPlay(ApplicationManager * pApp):Action(pApp)
{}

void SwitchToPlay::ReadActionParameters()
{	
	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();

	if(pManager->GetFigCount()!=0)
		pGUI->PrintMessage("Welcome To PlayMode");
	else pGUI->PrintMessage("No Figer To Play");
}

void SwitchToPlay::Execute()
{
	GUI* pGUI = pManager->GetGUI();
	pManager->ClearSelectedFigs();

	ReadActionParameters();

	if(pManager->GetFigCount()!=0){
		ofstream MyFile;
		MyFile.open("tempSave.txt", ios::out);
		pManager->SaveAll(MyFile);
		MyFile.close();
	}
}
