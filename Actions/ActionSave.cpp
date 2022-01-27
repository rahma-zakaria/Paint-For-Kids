#include "ActionSave.h"
#include "..\GUI\GUI.h"
#include "..\ApplicationManager.h"
#include <iostream>
#include <string>
#include <fstream>
#include <Commdlg.h>


ActionSave::ActionSave(ApplicationManager* pApp) :Action(pApp) {}

void ActionSave::ReadActionParameters()
{
	char* Name = NULL;
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(OPENFILENAME);
	Name = new char[MAX_PATH];
	Name[0] = 0;
	ofn.lpstrFile = Name;
	ofn.hwndOwner = NULL;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrFilter = "Text\0*.TXT\0";
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = "conf";
	if (GetSaveFileName(&ofn)) {
		filename = Name;
		//ofstream fout(Name, ios::out);
	}
	else {
		printf("No Name");
	};
	delete[] Name;
	Name = NULL;

}
//Execute the action
void ActionSave::Execute()
{
	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();

	pGUI->PrintMessage("Save");
	ReadActionParameters();
	//ofstream fout(filename, ios::out);
	pGUI->PrintMessage("Save succesfull to " + filename);

	ofstream MyFile;
	MyFile.open(filename, ios::out | ios::trunc);

	pManager->SaveAll(MyFile);

	MyFile.close();
}