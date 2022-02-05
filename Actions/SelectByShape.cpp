#include "SelectByShape.h"

SelectByShape::SelectByShape(ApplicationManager* pApp) :Action(pApp)
{
	shapeName = pManager->getShapeInPlayMode();
	pGUI = pManager->GetGUI();
}

void SelectByShape::selectByShapePlayMode()
{
	pGUI->PrintMessage("Select All " + shapeName + " Shapes");
	getUserAction();
	if (isGameSwitched)
		return;
	SelectAction* select = new SelectAction(pManager);
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
	pManager->hideSelectedFigure(picky);
	pManager->UpdateInterface();
	endGame = !pManager->isFigureExists(shapeName);
}

void SelectByShape::getUserAction()
{
	ActionType action= pGUI->MapInputToActionType();
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

void SelectByShape::Execute()
{
	while (endGame == false && pManager->GetFigCount() != 0&&isGameSwitched==false)
		selectByShapePlayMode();

	if(isGameSwitched==false)
		pGUI->PrintMessage("Correct Answers: " + to_string(rightScore) + ", Wrong Answers: " + to_string(wrongScore));
}
SelectByShape::~SelectByShape()
{
	delete pGUI;
	delete picky;
	delete pGUI;
}
