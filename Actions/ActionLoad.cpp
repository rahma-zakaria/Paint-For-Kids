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
void ActionLoad::Execute() {
	OPENFILENAME ofn;
	char szFile[100];

	// open a file name
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = "Text\0*.TXT\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	//********************************************************
	// Read from the text file
	std::cout << (ofn.lpstrFile) << endl;

	if (GetOpenFileName(&ofn)) {
		printf("\nIn file open\n");
	}
	else {
		std::cout << "no file selected ";
	}
}


