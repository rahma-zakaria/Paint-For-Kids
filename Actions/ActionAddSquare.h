#ifndef ACTION_ADD_SQUARE_H
#define ACTION_ADD_SQUARE_H

#include "Action.h"

//Add Square Action class
class ActionAddSquare: public Action
{
public:
	// Constructor of AddEllipse Action Class
	ActionAddSquare(ApplicationManager *pApp);
	
	//Add Square to the ApplicationManager to Excute it
	virtual void Execute();
	~ActionAddSquare();
	
};

#endif