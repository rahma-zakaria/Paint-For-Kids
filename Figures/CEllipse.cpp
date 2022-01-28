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

CEllipse::CEllipse() {}

void CEllipse::DrawMe(GUI* pGUI) const
{
	//Call Output::	
	pGUI->DrawElli(point1, point2, angele1, angele2, FigGfxInfo, Selected);


}

void CEllipse::Save(ofstream& outFile)
{
	outFile << type << "\t" << ID << "\t" << point1.x << "\t" << point1.y <<
		"\t" << point2.x << "\t" << point2.y << "\t" << angele1 << "\t" 
		<< angele2 << "\t" << "blue" << "\t";
	if (FigGfxInfo.isFilled) outFile << "red" << endl;
	else outFile << "NO_FILL" << endl;
}

void CEllipse::Load(ifstream& inFile)
{
	string FigureColor;
	string FigureFill;

	//Get a Pointer to the Interface
	inFile >> ID >> point1.x >> point1.y >> point2.x >> point2.y >> angele1 >> angele2;
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

int CEllipse::getFigureData(POINT& p1, POINT& p2)
{
	return 1;
}

string CEllipse::getFigureName() {
	return "Ellipse selected";
}