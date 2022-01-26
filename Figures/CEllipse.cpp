#include "CEllipse.h"

CEllipse::CEllipse(Point c, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	center = c;
	P.x = 80; P.y = 30;

}


void CEllipse::DrawMe(GUI* pGUI) const
{
	//Call Output::	
	pGUI->DrawElli(center, P, FigGfxInfo, Selected);


}

void CEllipse::Save(ofstream& outFile)
{
}

void CEllipse::Load(ifstream& inFile)
{
}