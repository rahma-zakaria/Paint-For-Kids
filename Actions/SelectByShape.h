#pragma once
#pragma once
#include "..\Figures\CFigure.h"
#include "..\ApplicationManager.h"



class SelectByShape : public Action
{
private:
	CFigure* picky;
	Point P;
	int rightScore = 0, wrongScore = 0;
	bool endGame = false, isGameSwitched = false;
	GUI* pGUI;
	string shapeName;
	void selectByShapePlayMode();
	void getUserAction();
public:
	SelectByShape(ApplicationManager*);
	virtual void Execute();
	~SelectByShape();
};

