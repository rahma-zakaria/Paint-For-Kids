#pragma once


#include "CFigure.h"
class CEllipse : public CFigure
{
private:
	Point point1, point2;
	double angele1, angele2;
public:
	CEllipse(Point, Point,double,double, GfxInfo FigureGfxInfo);
	virtual void DrawMe(GUI* pOut) const;
	virtual void Save(ofstream& outFile);
	virtual void Load(ifstream& inFile);
};
