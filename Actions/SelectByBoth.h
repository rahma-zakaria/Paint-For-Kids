#include "..\Figures\CFigure.h"
#include "..\ApplicationManager.h"



class SelectByBoth : public Action
{
	CFigure* picky;
	Point P;
	int rightScore = 0, wrongScore = 0;
	bool endGame = false;
	GUI* pGUI;
	CFigure* shape;

public:
	SelectByBoth(ApplicationManager*);

	virtual void ReadActionParameters();
	virtual void Execute();
	~SelectByBoth();
};
