#pragma once
#include "CFigure.h"
class CHexagon :public CFigure
{
private:
	Point center, point;

	int radius;

public:
	CHexagon(Point, Point,int, GfxInfo FigureGfxInfo);
	CHexagon();
	virtual void DrawMe(GUI* pOut) const;
	virtual void Move(Point p, Point pMoveTo);
	virtual void Save(ofstream& outFile, GUI* pGUI);
	virtual void Load(ifstream& inFile, GUI* pGUI);
	// for selecting
	virtual bool PointInShape(int x, int y) const;
	int getFigureData(POINT& p1, POINT& p2);
	string getFigureName();
	string getFigureColor();
	void Resize(float);
};

