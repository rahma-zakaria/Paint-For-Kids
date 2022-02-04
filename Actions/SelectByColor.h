#pragma once
#include "..\Figures\CFigure.h"
#include "..\ApplicationManager.h"



class SelectByColor : public Action
{
	CFigure* picky;
	Point P;
	int rightScore = 0, wrongScore = 0;
	bool endGame = false;
	GUI* pGUI;
	string shapeColor;

public:
	SelectByColor(ApplicationManager*);

	virtual void ReadActionParameters();
	virtual void Execute();
	~SelectByColor();
};
