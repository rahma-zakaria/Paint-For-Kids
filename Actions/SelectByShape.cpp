#include "SelectByShape.h"

SelectByShape::SelectByShape(ApplicationManager* pApp) :Action(pApp)
{
	shapeName = pManager->getShapeInPlayMode();
	pGUI = pManager->GetGUI();
}

void SelectByShape::ReadActionParameters()
{
	SelectAction* select = new SelectAction(pManager);
	pGUI->PrintMessage("Select All " + shapeName + " Shapes");
	select->Execute();
	picky = select->getSelectedFigure();
	if (picky == NULL) {
		return;
	}
	if (picky->getFigureName() == shapeName) {
		rightScore++;
	}
	else {
		wrongScore++;
	}
	pManager->deleteSelectedFigure(picky);
	pManager->UpdateInterface();
	endGame = !pManager->isFigureExists(shapeName);
}

void SelectByShape::Execute()
{
	while (endGame == false && pManager->GetFigCount() != 0)
		ReadActionParameters();
	pGUI->PrintMessage("Correct Answers: " + to_string(rightScore) + ", Wrong Answers: " + to_string(wrongScore));
}
SelectByShape::~SelectByShape()
{
	delete picky;
}
