#pragma once
#include "Action.h"

class SwitchToPlay : public Action
{
public:
	SwitchToPlay (ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute() ;
};

