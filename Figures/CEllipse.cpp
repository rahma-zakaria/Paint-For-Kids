#include "CEllipse.h"
#include <iostream>
#include <fstream>
#include <string>

CEllipse::CEllipse(Point P1, Point P2,double an1,double an2, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	/*center = c;
	P.x = 80; P.y = 30;*/
	point1 = P1;
	point2 = P2;
	angele1 = an1;
	angele2 = an2;
	type = "ELPS";

}

CEllipse::CEllipse() {
	type = "ELPS";
}

void CEllipse::DrawMe(GUI* pGUI) const
{
	//Call Output::	
	pGUI->DrawElli(point1, point2, angele1, angele2, FigGfxInfo, Selected);


}

void CEllipse::Save(ofstream& outFile, GUI* pGUI)
{
	outFile << type << "\t" << ID << "\t" << point1.x << "\t" << point1.y <<
		"\t" << point2.x << "\t" << point2.y << "\t" << angele1 << "\t"
		<< angele2 << "\t" << pGUI->ColorToString(FigGfxInfo.DrawClr) << "\t";
	if (FigGfxInfo.isFilled) outFile << pGUI->ColorToString(FigGfxInfo.FillClr) << endl;
	else outFile << "NO_FILL" << endl;
}

void CEllipse::Load(ifstream& inFile, GUI* pGUI)
{
	string FigureColor;
	string FigureFill;

	//Get a Pointer to the Interface
	inFile >> ID >> point1.x >> point1.y >> point2.x >> point2.y >> angele1 >> angele2;
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
void CEllipse::Move(Point p, Point pMoveTo) {

	int DeltaX = (pMoveTo.x - p.x);
	int DeltaY = (pMoveTo.y - p.y);

	point1.x += DeltaX;
	point1.y += DeltaY;
	point2.x += DeltaX;
	point2.y += DeltaY;

}

int CEllipse::getFigureData(POINT& p1, POINT& p2)
{
	p1.x = point1.x;
	p1.y = point1.y;
	p2.x = point2.x;
	p2.y = point2.y;
	return point2.y - point1.y;
}

string CEllipse::getFigureName() {
	return "Ellipse";
}

string CEllipse::getFigureColor() {
	return figColor;
}

bool CEllipse::PointInShape(int x, int y) const {
	Point center;
	center.x = (point1.x + point2.x) / 2;
	center.y = (point1.y + point2.y) / 2;
	return pow((x - center.x), 2) / pow((point1.x - center.x), 2) + pow((y - center.y), 2) / pow((point1.y - center.y), 2) <= 1;
}

void CEllipse::Resize(float) {
	if (FigGfxInfo.Resize_Factor == .5) FigGfxInfo.Resize_Factor = -1;
	else if (FigGfxInfo.Resize_Factor == .25) FigGfxInfo.Resize_Factor = -(4.0 / 3);

	Point O;
	O.x = (point1.x + point2.x) / 2;
	O.y = (point1.y + point2.y) / 2;

	if (point1.x <= O.x)
		point1.x -= (O.x - point1.x) * FigGfxInfo.Resize_Factor / 2;
	else
		point1.x += (point1.x - O.x) * FigGfxInfo.Resize_Factor / 2;

	if (point2.x <= O.x)
		point2.x -= (O.x - point2.x) * FigGfxInfo.Resize_Factor / 2;
	else
		point2.x += (point2.x - O.x) * FigGfxInfo.Resize_Factor / 2;

	if (point1.y <= O.y)
		point1.y -= (O.y - point1.y) * FigGfxInfo.Resize_Factor / 2;
	else
		point1.y += (point1.y - O.y) * FigGfxInfo.Resize_Factor / 2;

	if (point2.y <= O.y)
		point2.y -= (O.y - point2.y) * FigGfxInfo.Resize_Factor / 2;
	else
		point2.y += (point2.y - O.y) * FigGfxInfo.Resize_Factor / 2;
}
