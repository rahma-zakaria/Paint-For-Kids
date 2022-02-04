#include "ApplicationManager.h"
#include "Actions\ActionAddSquare.h"
#include "Actions\AddElliAction.h"
#include "Actions\AddHexaAction.h"
#include "Actions\SelectAction.h"
#include "Actions\ActionSave.h"
#include "Actions\ActionLoad.h"
#include "Actions\ChangeCFCAction.h"
#include "Actions\ChangeCDCAction.h"
#include "Actions\ActionChangeBgColor.h"
#include "Actions\ExitAction.h"
#include "Actions\RezizeAction.h"
#include "Actions\SwitchToDraw.h"
#include "Actions\SwitchToPlay.h"
#include "Actions\Bring_to_front.h"
#include "Actions\Send_To_Back.h"
#include "Actions\SelectByShape.h"
#include "Actions\SelectByColor.h"
#include "Actions\SelectByBoth.h"
#include "Figures\CSquare.h"
#include "Figures\CHexagon.h"
#include "Figures\CEllipse.h"

#include<iostream>
#include <fstream>
#include <string>
using namespace std;



//Constructor
ApplicationManager::ApplicationManager() : mode(0)
{
	//Create Input and output
	pGUI = new GUI;
	
	FigCount = 0;
		
	// Rahma
	////and intialise SelectedFigs array to NULL
	for (int i = 0; i < MaxFigCount; i++) {
		FigList[i] = NULL;
		//Rahma
		SelectedFigs[i] = NULL;
		

	}
	//initialise selectedCount to 0
	selectedCount = 0;

	pGUI->PrintMessage("Welcome to a world of wonders ! (i.e colors and stuff)");
}

void ApplicationManager::Run()
{
	ActionType ActType;
	do
	{		
		//1- Read user action
		ActType = pGUI->MapInputToActionType();

		//2- Create the corresponding Action
		Action *pAct = CreateAction(ActType);
		
		//3- Execute the action
		ExecuteAction(pAct);

		//4- Update the interface
		UpdateInterface();	

	}while(ActType != EXIT);
	
}


//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//
ActionType ApplicationManager::GetUserAction() const
{
	//Ask the input to get the action from the user.
	return pGUI->MapInputToActionType();
}
////////////////////////////////////////////////////////////////////////////////////
//Creates an action
Action* ApplicationManager::CreateAction(ActionType ActType) 
{

	Action* newAct = NULL;
	bool isThereColoredFig = false;
	
	//According to Action Type, create the corresponding action object
	switch (ActType)
	{
		case DRAW_SQUARE:
			newAct = new ActionAddSquare(this);
			break;

		case DRAW_ELPS:
			newAct = new AddElliAction(this);
			break;

		case DRAW_HEX:
			newAct = new AddHexaAction(this);
			break;
	
			//case select Action
		case SELECT:
			newAct = new SelectAction(this);
			break;
		case DRAWING_AREA:
			//if (mode == 2) {
				return new SelectAction(this);
			//}
			break;

			/*case RESIZE:
			newAct = new RezizeAction(this);
			break;*/

		case CHNG_DRAW_CLR:
			newAct = new ChangeCDCAction(this);
			break;
		case CHNG_FILL_CLR:
			newAct = new ChangeCFCAction(this);
			break;
		case RESIZE:
			mode = 1;
			newAct = new RezizeAction(this, SelectedFigs[selectedCount-1]);
			break;
		case SAVE:
			newAct = new ActionSave(this);
			break;
		case LOAD:
			newAct = new ActionLoad(this);
			break;
		case TO_SIZE:
			mode = 1;
			break;
		case BACK: 
			mode = 0;
			break;
		case UNDO:
			
			break;
		case REDO:

			break;
		case MOVE:
			newAct = new ActionMove(this);
			break;
		case TO_PLAY:
			configureAllPlayModeData();
			newAct = new SwitchToPlay(this);
			break;
		case TO_DRAW:
			configureAllDrawModeData();
			newAct = new SwitchToDraw(this);
			break;
		case TO_PLAY_SELECT_BY_SHAPE:
			newAct = playMode(TO_PLAY_SELECT_BY_SHAPE);
			if (newAct == NULL)
				return newAct;
			break;
		case TO_PLAY_SELECT_BY_COLOR:
			newAct = playMode(TO_PLAY_SELECT_BY_COLOR);
			if (newAct == NULL)
				return newAct;
			break;
		case TO_PLAY_SELECT_BY_BOTH:
			newAct = playMode(TO_PLAY_SELECT_BY_BOTH);
			if (newAct == NULL)
				return newAct;
			break;
		case CHNG_BK_CLR:
			newAct = new ActionChangeBgColor(this);
			break;
		case SEND_BACK:
			newAct = new Send_To_Back(this);
			break;
		case BRNG_FRNT:
			newAct = new Bring_to_front(this);
			break;
		case EXIT:
			///create ExitAction here
			newAct = new ExitAction(this);
			break;
		
		case STATUS:	//a click on the status bar ==> no action
			return NULL;
			break;
	}	
	return newAct;
}
//////////////////////////////////////////////////////////////////////
//Executes the created Action
void ApplicationManager::ExecuteAction(Action* &pAct) 
{	
	//Execute the created action
	if(pAct != NULL)
	{
		pAct->Execute();//Execute
		delete pAct;	//Action is not needed any more ==> delete it
		pAct = NULL;
	}
}
//==================================================================================//
//						Figures Management Functions								//
//==================================================================================//

//Add a figure to the list of figures
void ApplicationManager::AddFigure(CFigure* pFig)
{
	if(FigCount < MaxFigCount )
		FigList[FigCount++] = pFig;	
}
////////////////////////////////////////////////////////////////////////////////////
CFigure *ApplicationManager::GetFigure(int x, int y) const
{
	//If a figure is found return a pointer to it.
	//if this point (x,y) does not belong to any figure return NULL
	for (int i = FigCount - 1; i >= 0; i--)
	{
		if (FigList[i]->PointInShape(x, y))
			return FigList[i];
	}

	///Add your code here to search for a figure given a point x,y	

	return NULL;
}

int ApplicationManager::GetFigCount() { return FigCount; }

//==================================================================================//
//							Select Functions										//
//==================================================================================//

//Returns the number of selected figures
int ApplicationManager::GetSelectedCount() const {
	return selectedCount;
}
////////////////////////////////////////////////////////////////////////////////////
//Returns a pointer to SelectedFigs array
CFigure* const* ApplicationManager::GetSelectedFigures() const {
	return SelectedFigs;
}
///////////////////////////////////////////////////////////////////////////////////
//Adds a figure to the SelectedFigs array
void ApplicationManager::AddSelectedFigure(CFigure* sf) {

	SelectedFigs[selectedCount] = sf;
	selectedCount++;
}
////////////////////////////////////////////////////////////////////////////////////
//Removes a figure from the SelectedFigs array
void ApplicationManager::RemoveSelectedFigure(CFigure* sf) {

	for (int i = 0; i < selectedCount; i++) {
		if (SelectedFigs[i] == sf) {
			SelectedFigs[i] = SelectedFigs[selectedCount - 1];
			SelectedFigs[selectedCount - 1] = NULL;
			selectedCount--;
			return;
		}
	}
}

void ApplicationManager::SelectFigure(Point clickedPoint) //Select a figure given last clicked point
{
	for (int i = FigCount - 1; i >= 0; i--) { // from front to back
		if (FigList[i]->PointInShape(clickedPoint.x, clickedPoint.y)) {
			// Select/Unselect
			FigList[i]->SetSelected(!FigList[i]->IsSelected());
			// Print figure info if figure is selected
			if (FigList[i]->IsSelected()) {
				//pGUI->PrintMessage(FigList[i]->FigureInfo());
				CFigure* SelectedFig;
				SelectedFig = GetFigure(clickedPoint.x, clickedPoint.y);
				AddSelectedFigure(SelectedFig);
			}
			break;
		}
	}
}

void ApplicationManager::ClearSelectedFigs() {
	for (int i = 0; i < selectedCount; i++)
	{
		SelectedFigs[i]->SetSelected(false);
		SelectedFigs[i] = NULL;
	}
	selectedCount = 0;
}

//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{	
	pGUI->ClearDrawArea();
	for(int i=0; i<FigCount; i++)
		FigList[i]->DrawMe(pGUI);		//Call Draw function (virtual member fn)

	if (mode == 0)
		pGUI->CreateDrawToolBar();
	else if (mode == 1)
		pGUI->CreateSizeToolBar();
	else if (mode == 2)
		pGUI->CreatePlayToolBar();
}

void ApplicationManager::updateMoveInterface() {

	pGUI->ClearDrawArea();

	for (int i = 0; i < FigCount; i++)
	{
		FigList[i]->DrawMe(pGUI); //Call Draw function (virtual member fn)
	}
	// Uses a whole picture to reduce lagging effect
	pGUI->CreateDrawToolBar();
	//pGUI->CreateSizeToolBar();
	//pGUI->pWind->SetPen(RED, 3);
	//pGUI->pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);

}
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the interface
GUI *ApplicationManager::GetGUI() const
{	return pGUI; }
////////////////////////////////////////////////////////////////////////////////////
//Destructor
ApplicationManager::~ApplicationManager()
{
	for(int i=0; i<FigCount; i++)
		delete FigList[i];
	delete pGUI;
	
}



//==================================================================================//
//							Save And Load Functions							//
//==================================================================================//

void ApplicationManager::SaveAll(ofstream& fileName)
{
	// DrawColor	FillColor	BkGrndColor
	fileName << pGUI->ColorToString(pGUI->getCrntDrawColor()) << "\t" << pGUI->ColorToString(pGUI->getCrntFillColor()) << "\t" << "white" << endl;
	// FigCount
	fileName << to_string(FigCount) << endl;

	for (int i = 0; i < FigCount; i++)
	{
		FigList[i]->Save(fileName, pGUI);
	}
}

void ApplicationManager::LoadAll(ifstream& fileName)
{
	//GUI* pGUI = pManager->GetGUI();
	ClearAllFig();
	pGUI->ClearDrawArea();
	int FigNumbers;
	string draw, fill, back, FigureType;
	CFigure* LoadedFig;

	fileName >> draw >> fill >> back;
	fileName >> FigNumbers;

	while (FigNumbers) {
		fileName >> FigureType;
		if (FigureType == "SQR") {
			LoadedFig = new CSquare;
		}
		else if (FigureType == "ELPS") {
			LoadedFig = new CEllipse;
		}
		else if (FigureType == "HEXA") {
			LoadedFig = new CHexagon;
		}
		LoadedFig->Load(fileName, pGUI);
		AddFigure(LoadedFig);
		FigNumbers--;
	}
	UpdateInterface();

}


//==================================================================================//
//						 Bring_to_front,send_to_back functions						//
//==================================================================================//

void ApplicationManager::Bring_Front()
{
	CFigure* temp = SelectedFigs[selectedCount - 1];
	int Swapped_index;
	for (int i = 0; i < FigCount; i++)
		if (SelectedFigs[selectedCount - 1] == FigList[i])
			Swapped_index = i;

	for (int i = Swapped_index; i < FigCount - 1; i++)
		FigList[i] = FigList[i + 1];
	FigList[FigCount - 1] = temp;
}

void ApplicationManager::Send_Back()
{
	
	CFigure* temp = SelectedFigs[selectedCount-1];
	int Swapped_index;
	for (int i = 0; i < FigCount; i++)
		if (SelectedFigs[selectedCount - 1] == FigList[i])
		{
			Swapped_index = i;
			break;
		}

	for (int i = Swapped_index; i > 0; i--)
		FigList[i] = FigList[i - 1];
	FigList[0] = temp;
}


void ApplicationManager::ClearAllFig()
{
	for (int i = 0; i < FigCount; i++)
	{
		delete FigList[i];
		FigList[i] = NULL;
	}
	FigCount = 0;
}

void ApplicationManager::ChangeCDrawingColor(color selectedColor)
{
	pGUI->changeCrntDrawColor(selectedColor);
}

void ApplicationManager::ChangeSDrawingColor(color selectedColor)
{
	for (int i = 0; i < selectedCount; i++)
	{
		SelectedFigs[i]->ChngDrawClr(selectedColor);
	}
}

void ApplicationManager::ChangeCFillColor(color SelectedColor)
{
	
		UI.FillFigures = 1;
		pGUI->changeCrntFillColor(SelectedColor);
	
}

void ApplicationManager::ChangeSFillColor(color SelectedColor)
{
	for (int i = 0; i < selectedCount; i++)
	{
		SelectedFigs[i]->ChngFillClr(SelectedColor);
	}
}

CFigure* ApplicationManager::getSelectedFig()
{
	return SelectedFigs[0];
}

Action* ApplicationManager::playMode(ActionType gameModeType) {
	configureAllDrawModeData();
	configureAllPlayModeData();
	if (FigCount == 0)
		return NULL;
	Action *action;
	if (gameModeType == TO_PLAY_SELECT_BY_SHAPE) {
		action=new SelectByShape(this);
	}
	else if (gameModeType == TO_PLAY_SELECT_BY_COLOR) {
		action=new SelectByColor(this);
	}
	else{
		action=new SelectByBoth(this);
	}
	return action;
}

string ApplicationManager::getShapeInPlayMode() {
	int randomShape = rand() % FigCount;
	return FigList[randomShape]->getFigureName();
}

string ApplicationManager::getColorInPlayMode() {
	int randomShape = rand() % FigCount;
	return FigList[randomShape]->getFigureColor();
}

CFigure* ApplicationManager::getColoredFigure() {
	CFigure *result;
	do
	{
		int randomShape = rand() % FigCount;
		result=FigList[randomShape];
	} while (result->getFigureColor() == "none");
	return result;
}

void ApplicationManager::deleteSelectedFigure(CFigure* figure) {
	int index;
	for (int i = 0; i < FigCount; i++) {
		if (FigList[i]->getID() == figure->getID()) {
			index = i;
		}
	}
	for (int i = index; i < FigCount; i++) {
		FigList[i] = FigList[i + 1];
	}
	FigCount--;
}
//moves selected figures from point p to pMoveTo
bool ApplicationManager::MoveSelected(Point p, Point pMoveTo)
{
	bool success = 1;//returns 1 if move is successful and 0 if not
	CFigure* pFig;
	for (int i = 0; i < FigCount; i++)
	{
		pFig = FigList[i];
		if (pFig->IsSelected())
		{
			pFig->Move(p, pMoveTo);
			//makes sure figure is inside borders
			/*
			if (!pFig->IsFigInsideBorders(0, UI.width - 10, UI.ToolBarHeight, UI.height - UI.StatusBarHeight + 3))
			{
				//if figure is outside borders, move it back to point p
				pGUI->PrintMessage("Cannot drag figure beyond Drawing Area borders.");
				pFig->Move(pMoveTo, p);
				success = 0;
			}
			*/
			SetGraphSaved(false);
		}
	}
	return success;
}

void ApplicationManager::SetGraphSaved(bool s) {
	saved = s;
}

int ApplicationManager::getMode() {
	return mode;
}

bool ApplicationManager::isFigureExists(string figureName) {
	for (int i = 0; i < FigCount; i++) {
		if (FigList[i]->getFigureName() == figureName)
			return true;
	}
	return false;
}

bool ApplicationManager::isFigureColorExists(string figureColor) {
	for (int i = 0; i < FigCount; i++) {
		if (FigList[i]->getFigureColor() == figureColor)
			return true;
	}
	return false;
}

bool ApplicationManager::isColoredFiguresExists(CFigure* figure) {
	for (int i = 0; i < FigCount; i++) {
		if (FigList[i]->getFigureColor() == figure->getFigureColor()&&FigList[i]->getFigureName()==figure->getFigureName())
			return true;
	}
	return false;
}

void ApplicationManager::configureAllPlayModeData() {
	ClearSelectedFigs();
	restoreDataCount = FigCount;
	for (int i = 0; i < FigCount; i++) {
		FigList[i]->SetSelected(false);
		restoreData[i] = FigList[i];
	}
	mode = 2;
}
void ApplicationManager::configureAllDrawModeData() {
	ClearSelectedFigs();
	for (int i = 0; i < restoreDataCount; i++) {
		restoreData[i]->SetSelected(false);
		FigList[i] = restoreData[i];
	}
	FigCount = restoreDataCount;
	UpdateInterface();
	mode = 0;
}