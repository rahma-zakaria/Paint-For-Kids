#include "CHexagon.h"
#include <iostream>
#include <fstream>
#include <string>
#include "../DEFS.h"


CHexagon::CHexagon(Point c, Point p,int r,GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	center = c;
	point = p;

	radius = sqrt(pow((c.x - p.x), 2) + pow((c.y - p.y), 2));
	
	/*p.x = 50; p.y = 50;*/
	type = "HEXA";
}

CHexagon::CHexagon() {
	type = "HEXA";
} //default constractur

void CHexagon::DrawMe(GUI* pGUI) const
{
	//Call Output::	
	pGUI->DrawHexa(center, point, radius, FigGfxInfo, Selected);


}

void CHexagon::Save(ofstream& outFile, GUI* pGUI)
{
	outFile << type << "\t" << ID << "\t" << center.x << "\t" << center.y <<
		"\t" << point.x << "\t" << point.y << "\t" << pGUI->ColorToString(FigGfxInfo.DrawClr) << "\t";
	if (FigGfxInfo.isFilled) outFile << pGUI->ColorToString(FigGfxInfo.FillClr) << endl;
	else outFile << "NO_FILL" << endl;
}

void CHexagon::Load(ifstream& inFile, GUI* pGUI)
{
	string FigureColor;
	string FigureFill;

	//Get a Pointer to the Interface
	inFile >> ID >> center.x >> center.y >> point.x >> point.y;
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
void CHexagon::Move(Point p, Point pMoveTo) {

	int DeltaX = (pMoveTo.x - p.x);
	int DeltaY = (pMoveTo.y - p.y);

	center.x += DeltaX;
	center.y += DeltaY;
	point.x += DeltaX;
	point.y += DeltaY;
}

int CHexagon::getFigureData(POINT& p1, POINT& p2)
{
	// not finished yet
	return -1;
}

string CHexagon::getFigureName() {
	return "Hexagon";
}

string CHexagon::getFigureColor() {
	return figColor;
}

bool CHexagon::PointInShape(int x, int y) const {
	return (x <= max(center.x, point.x) && x >= min(center.x, point.x) && y <= max(center.y, point.y) && y >= min(center.y, point.y));
}
void CHexagon::Resize(float size) {

	radius = radius * size;
	/*if (FigGfxInfo.Resize_Factor == .5) FigGfxInfo.Resize_Factor = -1;
	else if (FigGfxInfo.Resize_Factor == .25) FigGfxInfo.Resize_Factor = -(4.0 / 3);
	
	Point O;
	O.x = (center.x + point.x) / 2;
	O.y = (center.y + point.y) / 2;

	if (center.x <= O.x)
		center.x -= (O.x - center.x) * FigGfxInfo.Resize_Factor / 2;
	else
		center.x += (center.x - O.x) * FigGfxInfo.Resize_Factor / 2;

	if (point.x <= O.x)
		point.x -= (O.x - point.x) * FigGfxInfo.Resize_Factor / 2;
	else
		point.x += (point.x - O.x) * FigGfxInfo.Resize_Factor / 2;

	if (center.y <= O.y)
		center.y -= (O.y - center.y) * FigGfxInfo.Resize_Factor / 2;
	else
		center.y += (center.y - O.y) * FigGfxInfo.Resize_Factor / 2;

	if (point.y <= O.y)
		point.y -= (O.y - point.y) * FigGfxInfo.Resize_Factor / 2;
	else
		point.y += (point.y - O.y) * FigGfxInfo.Resize_Factor / 2;*/
}