#include "ApplicationManager.h"

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
	
			//case select Action
			case DRAWING_AREA:
			newAct = new SelectAction(this);
			std::cout << "Select";
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
		case UNDO:
			
			break;
		case REDO:

			break;
		case TO_PLAY:
			mode = 2;
			newAct = new SwitchToPlay(this);
			break;
		case TO_DRAW:
			mode = 0;
			newAct = new SwitchToDraw(this);
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
	UpdateInterface();

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