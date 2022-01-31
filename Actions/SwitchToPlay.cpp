#include "SwitchToPlay.h"
#include "..\GUI\GUI.h"
#include "..\ApplicationManager.h"

#include <fstream>

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

	if(pManager->GetFigCount()!=0){
		pManager->ClearSelectedFigs();

		ofstream MyFile;
		MyFile.open("tempSave.txt", ios::out | ios::trunc);
		pManager->SaveAll(MyFile);
		MyFile.close();
	}
}
