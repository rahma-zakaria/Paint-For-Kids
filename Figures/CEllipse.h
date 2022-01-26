#pragma once


#include "CFigure.h"
class CEllipse : public CFigure
{
private :
	Point center, P;
public:
	CEllipse(Point , GfxInfo FigureGfxInfo);
	virtual void DrawMe(GUI* pOut) const;
};

