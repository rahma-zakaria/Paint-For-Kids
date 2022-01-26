#include "CHexagon.h"

CHexagon::CHexagon(Point c, Point p, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	center = c;
	point = p;
	/*p.x = 50; p.y = 50;*/

}

void CHexagon::DrawMe(GUI* pGUI) const
{
	//Call Output::	
	pGUI->DrawHexa(center, point, FigGfxInfo, Selected);


}

void CHexagon::Save(ofstream& outFile)
{
}

void CHexagon::Load(ifstream& inFile)
{
}
