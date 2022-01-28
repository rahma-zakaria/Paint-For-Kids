#pragma once


#include "CFigure.h"
class CEllipse : public CFigure
{
private:
	Point TopLeftCorner, BottomRightCorner;
	double angele1, angele2;
public:
	CEllipse(Point, Point,double,double, GfxInfo FigureGfxInfo);
	CEllipse();
	virtual void DrawMe(GUI* pOut) const;
	virtual void Save(ofstream& outFile);
	virtual void Load(ifstream& inFile);
	int getFigureData(POINT& p1, POINT& p2);
	string getFigureName();
};

