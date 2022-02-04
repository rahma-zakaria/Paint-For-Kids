#include "ActionLoad.h"
#include "../ApplicationManager.h"

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
		filename = Name;
	}
}
//Execute the action
void ActionLoad::Execute() {
	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();

	pGUI->PrintMessage("You want to save your graph before Load ? if yes then write Y");
	string userChoose = pGUI->GetSrting();
	if (userChoose == "Y" || userChoose == "y")
	{
		Action* saveAct = new ActionSave(pManager);
		pManager->ExecuteAction(saveAct);
	}

	pGUI->PrintMessage("load");

	ReadActionParameters();
	if (filename.empty()) {
		pGUI->PrintMessage("no file selected ");
	}
	else {
		pGUI->PrintMessage("Load Succesfull From " + filename);

		ifstream MyFile;
		MyFile.open(filename, ios::app);
		// Read from the text file
		pManager->LoadAll(MyFile);
		MyFile.close();
	}
	pGUI->PrintMessage("");
}


