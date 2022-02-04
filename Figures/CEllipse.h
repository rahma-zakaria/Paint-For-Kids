#pragma once


#include "CFigure.h"
class CEllipse : public CFigure
{
private:
	Point point1, point2;
	double angele1, angele2;
	int a;
public:
	CEllipse(Point, Point,double,double, GfxInfo FigureGfxInfo);
	CEllipse();
	virtual void DrawMe(GUI* pOut) const;
	virtual void Move(Point p, Point pMoveTo);
	virtual void Save(ofstream& outFile, GUI* pGUI);
	virtual void Load(ifstream& inFile, GUI* pGUI);

	int getFigureData(POINT& p1, POINT& p2);
	virtual bool PointInShape(int x, int y) const;
	string getFigureName();
	string getFigureColor();
	void Resize(float);
};

