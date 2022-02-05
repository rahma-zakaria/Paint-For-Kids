#include "SelectByColor.h"

#include <iostream>
using namespace std;

SelectByColor::SelectByColor(ApplicationManager* pApp) :Action(pApp)
{
	pGUI = pManager->GetGUI();
	if (!pManager->isThereAColoredShapes()) {
		Action* pAct = pManager->CreateAction(TO_DRAW);
		pManager->ExecuteAction(pAct);
		pManager->UpdateInterface();
		isColoredShapeExists = false;
	}
	else {
		do
		{
			shapeColor = pManager->getColorInPlayMode();
		} while (shapeColor == "none");
	}
}

void SelectByColor::ReadActionParameters()
{
	pGUI->PrintMessage("Select All " + shapeColor + " Shapes");
	getUserAction();
	if (isGameSwitched)
		return;
	SelectAction* select = new SelectAction(pManager);
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
	pManager->hideSelectedFigure(picky);
	pManager->UpdateInterface();
	endGame = !pManager->isFigureColorExists(shapeColor);
}

void SelectByColor::getUserAction()
{
	ActionType action = pGUI->MapInputToActionType();
	Action* pAct;
	switch (action)
	{
	case TO_DRAW:
		pAct = pManager->CreateAction(action);
		pManager->ExecuteAction(pAct);
		pManager->UpdateInterface();
		isGameSwitched = true;
		break;
	case TO_PLAY_SELECT_BY_SHAPE:
		pAct = pManager->CreateAction(action);
		pManager->ExecuteAction(pAct);
		pManager->UpdateInterface();
		isGameSwitched = true;
		break;
	case TO_PLAY_SELECT_BY_COLOR:
		pAct = pManager->CreateAction(action);
		pManager->ExecuteAction(pAct);
		pManager->UpdateInterface();
		isGameSwitched = true;
		break;
	case TO_PLAY_SELECT_BY_BOTH:
		pAct = pManager->CreateAction(action);
		pManager->ExecuteAction(pAct);
		pManager->UpdateInterface();
		isGameSwitched = true;
		break;
	default:
		break;
	}
}

void SelectByColor::Execute()
{
	if (!isColoredShapeExists) {
		pGUI->PrintMessage("There's no colored shape to play with go and create some!!!");
		return;
	}
	while (endGame == false && pManager->GetFigCount() != 0&&isGameSwitched==false)
		ReadActionParameters();

	if (isGameSwitched == false)
		pGUI->PrintMessage("Correct Answers: " + to_string(rightScore) + ", Wrong Answers: " + to_string(wrongScore));
}
SelectByColor::~SelectByColor()
{
	delete picky;
}