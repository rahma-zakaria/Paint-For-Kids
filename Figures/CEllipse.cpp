#include "CEllipse.h"
#include <iostream>
#include <fstream>
#include <string>

CEllipse::CEllipse(Point P1, Point P2,double an1,double an2, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	/*center = c;
	P.x = 80; P.y = 30;*/
	TopLeftCorner = P1;
	BottomRightCorner = P2;
	angele1 = an1;
	angele2 = an2;
	type = "ELPS";

}

CEllipse::CEllipse() {}

void CEllipse::DrawMe(GUI* pGUI) const
{
	//Call Output::	
	pGUI->DrawElli(TopLeftCorner, BottomRightCorner, angele1, angele2, FigGfxInfo, Selected);


}

void CEllipse::Save(ofstream& outFile)
{
	outFile << type << "\t" << ID << "\t" << TopLeftCorner.x << "\t" << TopLeftCorner.y <<
		"\t" << BottomRightCorner.x << "\t" << BottomRightCorner.y << "\t" << angele1 << "\t" 
		<< angele2 << "\t" << "blue" << "\t";
	if (FigGfxInfo.isFilled) outFile << "red" << endl;
	else outFile << "NO_FILL" << endl;
}

void CEllipse::Load(ifstream& inFile)
{
	string FigureColor;
	string FigureFill;

	//Get a Pointer to the Interface
	inFile >> ID >> TopLeftCorner.x >> TopLeftCorner.y >> BottomRightCorner.x >> BottomRightCorner.y >> angele1 >> angele2;
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
	p1.x = TopLeftCorner.x;
	p1.y = TopLeftCorner.y;
	p2.x = BottomRightCorner.x;
	p2.y = BottomRightCorner.y;
	return BottomRightCorner.y - TopLeftCorner.y;
}

string CEllipse::getFigureName() {
	return "Ellipse selected";
}