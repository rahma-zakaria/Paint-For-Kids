#ifndef CSQUARE_H
#define CSQUARE_H

#include "CFigure.h"

class CSquare : public CFigure
{
private:
	Point TopLeftCorner;	
	int length;
public:
	CSquare(Point , int, GfxInfo FigureGfxInfo );
	CSquare();
	virtual void DrawMe(GUI* pOut) const;
	virtual void Move(Point p, Point pMoveTo);
	virtual void Save(ofstream& outFile, GUI* pGUI);
	virtual void Load(ifstream& inFile, GUI* pGUI);
	virtual bool PointInShape(int, int) const;
	virtual float getArea() const;
	virtual float getPremiter() const;
	int getFigureData(POINT& p1, POINT& p2);
	string getFigureName();
	string getFigureColor();
    void Resize(float);
};

#endif