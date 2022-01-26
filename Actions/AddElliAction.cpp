#include "AddElliAction.h"

#include "..\Figures\CEllipse.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"


AddElliAction::AddElliAction(ApplicationManager* pApp) :Action(pApp)
{}

//Execute the action
void AddElliAction::Execute()
{
	//Get a Pointer to the Interface
	 GUI* pGUI = pManager->GetGUI();

	
	 EllipseGfxInfo.isFilled = false;	//default is not filled
	 //get drawing, filling colors and pen width from the interface
	 EllipseGfxInfo.DrawClr = pGUI->getCrntDrawColor();
	 EllipseGfxInfo.FillClr = pGUI->getCrntFillColor();
	 EllipseGfxInfo.BorderWdth = pGUI->getCrntPenWidth();

	 //Step 1 - Read Ellipse data from the user

	 pGUI->PrintMessage("New Ellipse: Click at the center");

	 //Read center and store in point C
	 pGUI->GetPointClicked(C.x, C.y);

	 if (C.y < UI.StatusBarHeight || C.y > UI.height - UI.StatusBarHeight)
	 {
		 bool flag = 0; //false as long as the click is in wrong place
		 pGUI->PrintMessage("Please, Choose a valid place");
		 while (!flag)
		 {
			 pGUI->GetPointClicked(C.x, C.y); //Get Pasting Point
			 if (!(C.y < UI.StatusBarHeight || C.y > UI.height - UI.StatusBarHeight))
				 flag = 1;
		 }
	 }

	 pGUI->ClearStatusBar();

	 //Step 2 - Create a Ellipse with the parameters read from the user
	 CEllipse* E = new CEllipse(C, EllipseGfxInfo);

	 //Step 3 - Add the Ellipse to the list of figures
	 pManager->AddFigure(E);

}
