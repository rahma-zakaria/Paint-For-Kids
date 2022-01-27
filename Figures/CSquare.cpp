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

CSquare::CSquare() {}
	

void CSquare::DrawMe(GUI* pGUI) const
{
	//Call Output::DrawRect to draw a Square on the screen	
	pGUI->DrawSquare(TopLeftCorner, length, FigGfxInfo, Selected);
	

}

void CSquare::Save(ofstream& outFile)
{
	outFile << type << "\t" << ID << "\t" << TopLeftCorner.x << "\t" << TopLeftCorner.y <<
		"\t" << length << "\t" << "blue" << "\t";
	if (FigGfxInfo.isFilled) outFile << "red" << endl;
	else outFile << "NO_FILL" << endl;
}

//void CSquare::Save(ofstream& outFile)
//{
//	outFile << type << "\t" << ID << "\t" << TopLeftCorner.x << "\t" << TopLeftCorner.y <<
//		"\t" << length << "\t" << FigGfxInfo.DrawClr << "\t";
//	if (FigGfxInfo.isFilled) outFile << pGUI->ColorToString(FigGfxInfo.FillClr) << endl;
//	else outFile << "NO_FILL" << endl;
//}

void CSquare::Load(ifstream& inFile)
{
	string FigureColor;
	string FigureFill;

	//Get a Pointer to the Interface
	inFile >> ID >> TopLeftCorner.x >> TopLeftCorner.y >> length;
	std::cout << TopLeftCorner.x << " " << TopLeftCorner.y << " " << length << " ";
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
		FigGfxInfo.FillClr = YELLOW;
		FigGfxInfo.isFilled = true;
	}

}