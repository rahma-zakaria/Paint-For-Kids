#include "ApplicationManager.h"
#include "Actions\ActionAddSquare.h"
#include "Actions\AddElliAction.h"
#include "Actions\AddHexaAction.h"
#include "Actions\ActionSave.h"
#include "Actions\ActionLoad.h"
#include "Actions\RezizeAction.h"
#include "Figures\CSquare.h"
#include "Figures\CHexagon.h"
#include "Figures\CEllipse.h"
#include<iostream>
#include <fstream>
#include <string>


//Constructor
ApplicationManager::ApplicationManager() : mode(0)
{
	//Create Input and output
	pGUI = new GUI;
	
	FigCount = 0;
		
	//Create an array of figure pointers and set them to NULL		
	for(int i=0; i<MaxFigCount; i++)
		FigList[i] = NULL;	
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
//Creates an action
Action* ApplicationManager::CreateAction(ActionType ActType) 
{

	//for selecting purpose variable
	int x, y;
	CFigure* whichFigSelected;
	POINT p1, p2;
	int numberOfFiguresSelected = 0, previousFigure = 0;
	int length;
	bool isFigureSelected = false;
	string figureName;
	// end for selecting purpose

	Action* newAct = NULL;
	
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
		/*case RESIZE:
			newAct = new RezizeAction(this);
			break;*/
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

		case DRAWING_AREA:
			pGUI->GetPointClicked(x, y);
			if (FigCount == 0) {
				pGUI->PrintMessage("no figures drawing");
			}
			else {
				for (int i = 0; i < FigCount; i++)
				{
					whichFigSelected = FigList[i];
					length = whichFigSelected->getFigureData(p1, p2);

					if (x >= p1.x && x <= p2.x && y >= p1.y && y <= p2.y)
					{
						isFigureSelected = whichFigSelected->IsSelected();
						numberOfFiguresSelected++;
						figureName = whichFigSelected->getFigureName();
						isFigureSelected ? pGUI->CreateStatusBar() : pGUI->PrintMessage(figureName);
						isFigureSelected ? whichFigSelected->SetSelected(false) : whichFigSelected->SetSelected(true);
					}
					else {
						whichFigSelected->SetSelected(false);
					}
					if (numberOfFiguresSelected == 1 && previousFigure == 0) {
						previousFigure = i;
					}
					else if (numberOfFiguresSelected > 1) {
						CFigure* t = FigList[previousFigure];
						t->SetSelected(false);
						previousFigure = i;
					}
				}
			}
			break;

		case EXIT:
			///create ExitAction here
			
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


	///Add your code here to search for a figure given a point x,y	

	return NULL;
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
	//fileName << to_string(DrawColor)<<"\t"<< to_string(FillColor)<< "\t" << to_string(BkGrndColor) << endl;
	fileName << "blue" << "\t" << "white" << "\t" << "white" << endl;

	// FigCount
	fileName << to_string(FigCount) << endl;

	for (int i = 0; i < FigCount; i++)
	{
		FigList[i]->Save(fileName);
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
		std::cout << FigureType << " ";
		if (FigureType == "SQR") {
			LoadedFig = new CSquare;
		}
		else if (FigureType == "ELPS") {
			LoadedFig = new CEllipse;
		}
		else if (FigureType == "HEXA") {
			LoadedFig = new CHexagon;
		}
		LoadedFig->Load(fileName);
		AddFigure(LoadedFig);
		FigNumbers--;
	}

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