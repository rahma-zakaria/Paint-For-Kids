#pragma once
#include "CFigure.h"
class CHexagon :public CFigure
{
private:
	Point center, point;

public:
	CHexagon(Point, Point, GfxInfo FigureGfxInfo);
	virtual void DrawMe(GUI* pOut) const;
	virtual void Save(ofstream& outFile);
	virtual void Load(ifstream& inFile);
};

