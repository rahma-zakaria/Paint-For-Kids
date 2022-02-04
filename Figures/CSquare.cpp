#include "CSquare.h"
#include <iostream>
#include <fstream>
#include <string>

CSquare::CSquare(Point P1, int len, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	TopLeftCorner = P1;
	length = len;
	type = "SQR";
}

CSquare::CSquare() {
	type = "SQR";
}
	

void CSquare::DrawMe(GUI* pGUI) const
{
	//Call Output::DrawRect to draw a Square on the screen	
	pGUI->DrawSquare(TopLeftCorner, length, FigGfxInfo, Selected);
	

}
void CSquare::Save(ofstream& outFile, GUI* pGUI)
{
	outFile << type << "\t" << ID << "\t" << TopLeftCorner.x << "\t" << TopLeftCorner.y <<
		"\t" << length << "\t" << pGUI->ColorToString(FigGfxInfo.DrawClr) << "\t";
	if (FigGfxInfo.isFilled) outFile << pGUI->ColorToString(FigGfxInfo.FillClr) << endl;
	else outFile << "NO_FILL" << endl;
}


void CSquare::Load(ifstream& inFile, GUI* pGUI)
{
	string FigureColor;
	string FigureFill;

	//Get a Pointer to the Interface
	inFile >> ID >> TopLeftCorner.x >> TopLeftCorner.y >> length;
	inFile >> FigureColor >> FigureFill;
	FigGfxInfo.DrawClr = pGUI->StringToColor(FigureColor);
	FigGfxInfo.BorderWdth = UI.PenWidth;
	if (FigureFill == "NO_FILL") {
		FigGfxInfo.isFilled = false;
	}
	else {
		FigGfxInfo.FillClr = pGUI->StringToColor(FigureFill);;
		FigGfxInfo.isFilled = true;
	}
}
void CSquare::Move(Point p, Point pMoveTo) {
	int DeltaX = (pMoveTo.x - p.x);
	int DeltaY = (pMoveTo.y - p.y);

	TopLeftCorner.x += DeltaX;
	TopLeftCorner.y += DeltaY;
}

int CSquare::getFigureData(POINT& p1, POINT& p2)
{
	p1.x = TopLeftCorner.x;
	p1.y = TopLeftCorner.y;
	p2.x = TopLeftCorner.x + length;
	p2.y = TopLeftCorner.y + length;
	return length;
}

float CSquare::getArea() const {
	return length*length;
}
float CSquare::getPremiter() const {
	return 4*length;
}

bool CSquare::PointInShape(int x, int y) const {
	return (x >= TopLeftCorner.x && x <= TopLeftCorner.x + length)
		&& (y >= TopLeftCorner.y && y <= TopLeftCorner.y + length);
}

string CSquare::getFigureName() {
	return "Square";
}

string CSquare::getFigureColor() {
	return figColor;
}

void CSquare:: Resize(float size) {
	length = length * size;
}