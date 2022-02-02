#pragma once
#pragma once
#include "..\Figures\CFigure.h"
#include "..\ApplicationManager.h"



class SelectByShape : public Action
{
	CFigure* picky;
	Point P;
	int rightScore = 0, wrongScore = 0;
	bool endGame = false;
	GUI* pGUI;
	string shapeName;

public:
	SelectByShape(ApplicationManager*);

	virtual void ReadActionParameters();
	virtual void Execute();
	~SelectByShape();
};

