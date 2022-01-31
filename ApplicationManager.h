#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "DEFS.h"
#include "GUI\GUI.h"
#include "Figures\CFigure.h"
#include "Actions\ActionAddSquare.h"
#include "Actions\AddElliAction.h"
#include "Actions\AddHexaAction.h"
#include "Actions\SelectAction.h"
#include "Actions\ActionSave.h"
#include "Actions\ActionLoad.h"
#include "Actions\RezizeAction.h"
#include "Actions\SwitchToDraw.h"
#include "Actions\SwitchToPlay.h"
#include "Figures\CSquare.h"
#include "Figures\CHexagon.h"
#include "Figures\CEllipse.h"

#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <Commdlg.h>

class Action;	//Forward Declaration


//Main class that manages everything in the application.
class ApplicationManager
{
	enum { MaxFigCount = 200 };	//Max no of figures

private:
	int mode;
	int FigCount;		//Actual number of figures
	CFigure* FigList[MaxFigCount];	//List of all figures (Array of pointers)

	CFigure* SelectedFigs[MaxFigCount]; //array of pointers to the selected figures
	//Rahma
	int selectedCount;			//Number of selected figures


	//Pointers to Input and Output classes
	GUI* pGUI;
	

public:	
	ApplicationManager(); 
	~ApplicationManager();

	void Run();		//to run the application
	
	ActionType GetUserAction() const;

	// -- Action-Related Functions
	Action* CreateAction(ActionType);
	void ExecuteAction(Action*&) ; //Execute an action
	
	// -- Figures Management Functions
	void AddFigure(CFigure* pFig); //Adds a new figure to the FigList
	CFigure *GetFigure(int x, int y) const; //Search for a figure given a point inside the figure
	int GetFigCount();
	
		//Rahma 
	// -- Select Functions -- //
	//error prone area !  // compiler issues 
	int GetSelectedCount() const;					//Returns the number of selected figures
	void AddSelectedFigure(CFigure*);				//Adds a figure to the SelectedFigs array
	void RemoveSelectedFigure(CFigure*);			//Removes a figure from the SelectedFigs array
	CFigure* const* GetSelectedFigures() const;		//Returns a pointer to the SelectedFigs array
	void ClearSelectedFigs();                       //Cleares the SelectedFig array


	// -- Interface Management Functions	
	GUI *GetGUI() const; //Return pointer to the interface
	void UpdateInterface() const;	//Redraws all the drawing window	

	// --Save And Load 
	void SaveAll(ofstream& fileName);//Save all figures in figure list
	void LoadAll(ifstream& fileName);//Load all figures in figure list

	void ClearAllFig();
	void ChangeCDrawingColor(color SelectedColor);
	void ChangeSDrawingColor(color SelectedColor);
	void ChangeCFillColor(color SelectedColor);
	void ChangeSFillColor(color SelectedColor);
	CFigure* getSelectedFig();
};

#endif