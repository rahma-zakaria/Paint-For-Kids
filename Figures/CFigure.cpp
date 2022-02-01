#include "CFigure.h"

CFigure::CFigure(GfxInfo FigureGfxInfo)
{ 
	FigGfxInfo = FigureGfxInfo;	//Default status is non-filled.
	Selected = false;
	ID = nextID++;
}
CFigure::CFigure()
{
	//FigGfxInfo = NULL;	//Default status is non-filled.
	Selected = false;
	//ID = nextID++;
}

int CFigure::nextID = 0;

void CFigure::setnexID(int num) { nextID = num; }

void CFigure::SetSelected(bool s)
{	Selected = s; }

bool CFigure::IsSelected() const
{	return Selected; }

void CFigure::ChngDrawClr(color Dclr)
{	FigGfxInfo.DrawClr = Dclr; }

void CFigure::ChngFillClr(color Fclr)
{	
	FigGfxInfo.isFilled = true;
	FigGfxInfo.FillClr = Fclr; 
}

void CFigure::setSize(float size)
{
	FigGfxInfo.Resize_Factor = size;
}

int CFigure::getID() {
	return ID;
}