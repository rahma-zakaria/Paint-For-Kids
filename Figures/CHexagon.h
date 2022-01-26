#pragma once
#include "CFigure.h"
class CHexagon :public CFigure
{
private:
	Point center, p;

public:
	CHexagon(Point, GfxInfo FigureGfxInfo);
	virtual void DrawMe(GUI* pOut) const;
};

