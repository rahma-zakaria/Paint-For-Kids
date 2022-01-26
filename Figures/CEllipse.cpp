#include "CEllipse.h"

CEllipse::CEllipse(Point P1, Point P2,double an1,double an2, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	/*center = c;
	P.x = 80; P.y = 30;*/
	point1 = P1;
	point2 = P2;
	angele1 = an1;
	angele2 = an2;

}


void CEllipse::DrawMe(GUI* pGUI) const
{
	//Call Output::	
	pGUI->DrawElli(point1, point2, angele1, angele2, FigGfxInfo, Selected);


}

void CEllipse::Save(ofstream& outFile)
{
}

void CEllipse::Load(ifstream& inFile)
{
}