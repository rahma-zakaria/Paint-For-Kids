#include "ApplicationManager.h"
#include "Actions\ActionAddSquare.h"
#include "Actions\AddElliAction.h"
#include "Actions\AddHexaAction.h"
#include "Actions\ActionSave.h"
#include "Actions\ActionLoad.h"
#include "Actions\RezizeAction.h"
#include<iostream>
#include <fstream>


//Constructor
ApplicationManager::ApplicationManager()
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
		case RESIZE:
			newAct = new RezizeAction(this);
			break;
		case SAVE:
			newAct = new ActionSave(this);
			break;

		case LOAD:
			pGUI->PrintMessage("load");
			//newAct = new ActionLoad(this);
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
	for(int i=0; i<FigCount; i++)
		FigList[i]->DrawMe(pGUI);		//Call Draw function (virtual member fn)
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
		printf("%d", i);
	}
}

void ApplicationManager::LoadAll(ifstream& fileName)
{}