#include "ActionLoad.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "../Figures/CSquare.h"
#include "../GUI/GUI.h"
#include "../ApplicationManager.h"
#include "../CMUgraphicsLib/colors.h"
#include <windows.h>
#include <Commdlg.h>


ActionLoad::ActionLoad(ApplicationManager* pApp) :Action(pApp) {

}
void ActionLoad::ReadActionParameters()
{
	OPENFILENAME ofn;
	char szFile[100];

	// open a file name
	char* Name = NULL;
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFile;
	Name = new char[MAX_PATH];
	Name[0] = 0;
	ofn.lpstrFile = Name;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = "Text\0*.TXT\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn)) {
		printf("\nIn file open\n");
		filename = Name;
	}
	else {
		std::cout << "no file selected ";
	}

}
//Execute the action
void ActionLoad::Execute() {
	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();
	pGUI->PrintMessage("load");
	ReadActionParameters();
	
	pGUI->PrintMessage("Load succesfull to " + filename);

	ifstream MyFile;
	MyFile.open(filename, ios::app);

	// Read from the text file
	pManager->LoadAll(MyFile);

	MyFile.close();

}


