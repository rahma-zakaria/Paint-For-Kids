#include "SelectByBoth.h"

#include <iostream>
using namespace std;

SelectByBoth::SelectByBoth(ApplicationManager* pApp) :Action(pApp)
{
	shape = pManager->getColoredFigure();
	pGUI = pManager->GetGUI();
}

void SelectByBoth::ReadActionParameters()
{
	SelectAction* select = new SelectAction(pManager);
	pGUI->PrintMessage("Select All " + shape->getFigureColor() +" "+shape->getFigureName() + " Shapes");
	select->Execute();
	picky = select->getSelectedFigure();
	if (picky == NULL) {
		return;
	}
	if (picky->getFigureColor() == shape->getFigureColor() && picky->getFigureName() == shape->getFigureName()) {
		rightScore++;
	}
	else {
		wrongScore++;
	}
	pManager->deleteSelectedFigure(picky);
	pManager->UpdateInterface();
	endGame = !pManager->isColoredFiguresExists(shape);
}

void SelectByBoth::Execute()
{
	while (endGame == false && pManager->GetFigCount() != 0)
		ReadActionParameters();
	pGUI->PrintMessage("Correct Answers: " + to_string(rightScore) + ", Wrong Answers: " + to_string(wrongScore));
}
SelectByBoth::~SelectByBoth()
{
	delete picky;
}