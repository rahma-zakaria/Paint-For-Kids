#include "CHexagon.h"
#include <iostream>
#include <fstream>
#include <string>
#include "../DEFS.h"

CHexagon::CHexagon(Point c, Point p, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	center = c;
	point = p;
	/*p.x = 50; p.y = 50;*/
	type = "HEXA";
}

CHexagon::CHexagon() {} //default constractur

void CHexagon::DrawMe(GUI* pGUI) const
{
	//Call Output::	
	pGUI->DrawHexa(center, point, FigGfxInfo, Selected);


}

void CHexagon::Save(ofstream& outFile)
{
	outFile << type << "\t" << ID << "\t" << center.x << "\t" << center.y <<
		"\t" << point.x << "\t" << point.y << "\t" << "blue" << "\t";
	if (FigGfxInfo.isFilled) outFile << "red" << endl;
	else outFile << "NO_FILL" << endl;
}

void CHexagon::Load(ifstream& inFile)
{
	string FigureColor;
	string FigureFill;

	//Get a Pointer to the Interface
	inFile >> ID >> center.x >> center.y >> point.x >> point.y;
	std::cout << ID << " " << center.x << " " << center.y << " " << point.x << " " << point.y << " ";
	inFile >> FigureColor >> FigureFill;
	std::cout << FigureColor << " " << FigureFill << endl;
	//FigGfxInfo.DrawClr = FigureColor;
	FigGfxInfo.DrawClr = RED;
	FigGfxInfo.BorderWdth = UI.PenWidth;
	if (FigureFill == "NO_FILL") {
		FigGfxInfo.isFilled = false;
	}
	else {
		//FigGfxInfo.FillClr = FigureFill;
		FigGfxInfo.FillClr = RED;
		FigGfxInfo.isFilled = true;
	}
}

int CHexagon::getFigureData(POINT& p1, POINT& p2)
{
	return 1;
}

string CHexagon::getFigureName() {
	return "Hexagon selected";
}
bool CHexagon::PointInShape(int x, int y) const {
	Point tempP;
	tempP.x = center.x - (point.x - center.x);
	tempP.y = center.y-(point.y-center.y);
	return (x >= tempP.x && x <= point.x)
		&& (y >= tempP.y && y <= point.y);
}