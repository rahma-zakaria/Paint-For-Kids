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
	
	ReadActionParameters();
	pManager->ClearSelectedFigs();
	ofstream MyFile;
	MyFile.open("tempSave.txt", ios::out);

	if(pManager->GetFigCount()!=0){
		pManager->SaveAll(MyFile);
	}
	MyFile.close();
}
