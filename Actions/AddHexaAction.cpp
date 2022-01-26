#include "AddHexaAction.h"
#include "..\Figures\CHexagon.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"
AddHexaAction::AddHexaAction(ApplicationManager* pApp) :Action(pApp)
{}


//Execute the action
void AddHexaAction::Execute()
{
	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();


	HexapseGfxInfo.isFilled = false;	//default is not filled
	//get drawing, filling colors and pen width from the interface
	HexapseGfxInfo.DrawClr = pGUI->getCrntDrawColor();
	HexapseGfxInfo.FillClr = pGUI->getCrntFillColor();
	HexapseGfxInfo.BorderWdth = pGUI->getCrntPenWidth();

	//Step 1 - Read Hexa data from the user

	pGUI->PrintMessage("New Hexa: Click at the center");

	//Read center and store in point C
	pGUI->GetPointClicked(P1.x, P1.y);

	if (P1.y < UI.StatusBarHeight || P1.y > UI.height - UI.StatusBarHeight)
	{
		bool flag = 0; //false as long as the click is in wrong place
		pGUI->PrintMessage("Please, Choose a valid place");
		while (!flag)
		{
			pGUI->GetPointClicked(P1.x, P1.y); //Get Pasting Point
			if (!(P2.y < UI.StatusBarHeight || P2.y > UI.height - UI.StatusBarHeight))
				flag = 1;
		}
	}

	pGUI->ClearStatusBar();

	pGUI->PrintMessage("New Hexa: Click at any hexa vertices");

	//Read center and store in point C
	pGUI->GetPointClicked(P2.x, P2.y);

	if (P2.y < UI.StatusBarHeight || P2.y > UI.height - UI.StatusBarHeight)
	{
		bool flag = 0; //false as long as the click is in wrong place
		pGUI->PrintMessage("Please, Choose a valid place");
		while (!flag)
		{
			pGUI->GetPointClicked(P2.x, P2.y); //Get Pasting Point
			if (!(P2.y < UI.StatusBarHeight || P2.y > UI.height - UI.StatusBarHeight))
				flag = 1;
		}
	}

	pGUI->ClearStatusBar();
	//Step 2 - Create a Ellipse with the parameters read from the user
	CHexagon* H = new CHexagon(P1, P2, HexapseGfxInfo);

	//Step 3 - Add the Ellipse to the list of figures
	pManager->AddFigure(H);

}