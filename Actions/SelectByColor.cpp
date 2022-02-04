#include "SelectByColor.h"

#include <iostream>
using namespace std;

SelectByColor::SelectByColor(ApplicationManager* pApp) :Action(pApp)
{
	do
	{
		shapeColor = pManager->getColorInPlayMode();
	} while (shapeColor=="none");
	pGUI = pManager->GetGUI();
}

void SelectByColor::ReadActionParameters()
{
	SelectAction* select = new SelectAction(pManager);
	pGUI->PrintMessage("Select All " + shapeColor + " Shapes");
	select->Execute();
	picky = select->getSelectedFigure();
	if (picky == NULL) {
		return;
	}
	if (picky->getFigureColor() == shapeColor) {
		rightScore++;
	}
	else {
		wrongScore++;
	}
	pManager->deleteSelectedFigure(picky);
	pManager->UpdateInterface();
	endGame = !pManager->isFigureColorExists(shapeColor);
}

void SelectByColor::Execute()
{
	while (endGame == false && pManager->GetFigCount() != 0)
		ReadActionParameters();
	pGUI->PrintMessage("Correct Answers: " + to_string(rightScore) + ", Wrong Answers: " + to_string(wrongScore));
}
SelectByColor::~SelectByColor()
{
	delete picky;
}