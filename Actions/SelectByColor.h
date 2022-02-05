#pragma once
#include "..\Figures\CFigure.h"
#include "..\ApplicationManager.h"



class SelectByColor : public Action
{
private:
	CFigure* picky;
	Point P;
	int rightScore = 0, wrongScore = 0;
	bool endGame = false, isGameSwitched = false , isColoredShapeExists = true;
	GUI* pGUI;
	string shapeColor;

	void ReadActionParameters();
	void getUserAction();

public:
	SelectByColor(ApplicationManager*);
	virtual void Execute();
	~SelectByColor();
};
