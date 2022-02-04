#pragma once
#ifndef ACTION_CHANGE_BACKGROUND_COLOR_H
#define ACTION_CHANGE_BACKGROUND_COLOR_H

#include "Action.h"
#include "..\Figures\CFigure.h"
#include "..\CMUgraphicsLib\colors.h"

//Add Ellipse Action class
class ActionChangeBgColor : public Action
{
    int SelectedColorIndex;
    CFigure* SelectedFigure;
    color SelectedColor;

public:
    ActionChangeBgColor(ApplicationManager* pApp);

    virtual void ReadActionParameters();
    //ActionChangeFillColor
    virtual void Execute();

};

#endif