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
	virtual void Save(ofstream& outFile);
	virtual void Load(ifstream& inFile);
	virtual bool PointInShape(int, int) const;
	int getFigureData(POINT& p1, POINT& p2);
	string getFigureName();
	string getFigureColor();
    void Resize(float);
};

#endif