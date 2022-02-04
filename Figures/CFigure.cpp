#include "CFigure.h"

CFigure::CFigure(GfxInfo FigureGfxInfo)
{ 
	FigGfxInfo = FigureGfxInfo;	//Default status is non-filled.
	Selected = false;
	figColor = "none";
	ID = nextID++;
}
CFigure::CFigure()
{
	//FigGfxInfo = NULL;	//Default status is non-filled.
	Selected = false;
	figColor = "none";
	//ID = nextID++;
}

int CFigure::nextID = 0;

void CFigure::setnexID(int num) { nextID = num; }

void CFigure::SetSelected(bool s)
{	Selected = s; }

bool CFigure::IsSelected() const
{	return Selected; }

void CFigure::ChngDrawClr(color Dclr)
{	FigGfxInfo.DrawClr = Dclr;}

void CFigure::ChngFillClr(color Fclr)
{	
	FigGfxInfo.isFilled = true;
	FigGfxInfo.FillClr = Fclr; 
	if (Fclr.ucBlue == 255 && Fclr.ucGreen == 0 && Fclr.ucRed == 0)
	{
		figColor = "blue";
	}
	else if (Fclr.ucBlue == 0 && Fclr.ucGreen == 255 && Fclr.ucRed == 0)
	{
		figColor = "green";
	}
	else if (Fclr.ucBlue == 0 && Fclr.ucGreen == 0 && Fclr.ucRed == 255)
	{
		figColor = "red";
	}
	else if (Fclr.ucBlue == 0 && Fclr.ucGreen == 0 && Fclr.ucRed == 0)
	{
		figColor = "black";
	}
	else if (Fclr.ucBlue == 255 && Fclr.ucGreen == 255 && Fclr.ucRed == 255)
	{
		figColor = "white";
	}
}

void CFigure::setSize(float size)
{
	FigGfxInfo.Resize_Factor = size;
}

int CFigure::getID() {
	return ID;
}