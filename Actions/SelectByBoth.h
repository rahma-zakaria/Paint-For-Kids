#include "..\Figures\CFigure.h"
#include "..\ApplicationManager.h"



class SelectByBoth : public Action
{
private:
	CFigure* picky;
	Point P;
	int rightScore = 0, wrongScore = 0;
	bool endGame = false, isGameSwitched = false, isColoredShapeExists = true;
	GUI* pGUI;
	CFigure* shape;

	void getUserAction();
	void ReadActionParameters();
public:
	SelectByBoth(ApplicationManager*);
	virtual void Execute();
	~SelectByBoth();
};
