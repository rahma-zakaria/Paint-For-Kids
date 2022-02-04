#include "AddElliAction.h"
#include "..\ApplicationManager.h"

AddElliAction::AddElliAction(ApplicationManager* pApp) :Action(pApp)
{
	P1.x = 0;
	P1.y = 0;
	P2.x = 0;
	P2.y = 0;
}

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
	EllipseGfxInfo.isFilled = UI.FillFigures;

	 //Step 1 - Read Ellipse data from the user

	 pGUI->PrintMessage("New Ellipse: Click at the first point of ellipse");

	 //Read center and store in point C
	 pGUI->GetPointClicked(P1.x, P1.y);

	 if (P1.y < UI.StatusBarHeight || P1.y > UI.height - UI.StatusBarHeight)
	 {
		 bool flag = 0; //false as long as the click is in wrong place
		 pGUI->PrintMessage("Please, Choose a valid place");
		 while (!flag)
		 {
			 pGUI->GetPointClicked(P1.x, P1.y); //Get Pasting Point
			 if (!(P1.y < UI.StatusBarHeight || P1.y > UI.height - UI.StatusBarHeight))
				 flag = 1;
		 }
	 }

	 pGUI->ClearStatusBar();

	 pGUI->PrintMessage("New Ellipse: Click at the second point of ellipse");

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
	 double startAngle = 0;
	 double endAngle = 360;
	 //Step 2 - Create a Ellipse with the parameters read from the user
	 CEllipse* E = new CEllipse(P1, P2, startAngle, endAngle,EllipseGfxInfo);

	 //Step 3 - Add the Ellipse to the list of figures
	 pManager->AddFigure(E);

}
