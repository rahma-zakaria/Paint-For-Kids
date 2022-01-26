#include "CHexagon.h"

CHexagon::CHexagon(Point c, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	center = c;
	p.x = 50; p.y = 50;

}

void CHexagon::DrawMe(GUI* pGUI) const
{
	//Call Output::	
	pGUI->DrawHexa(center, p, FigGfxInfo, Selected);


}
