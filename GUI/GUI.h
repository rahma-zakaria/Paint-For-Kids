#ifndef GUI_H
#define GUI_H

#include "..\DEFS.h"
#include "UI_Info.h" 
#include "..\CMUgraphicsLib\CMUgraphics.h"


//This class is responsible for Grphical User Interface handling
//All user input and program outputs MUST be done through this class
//No other class is allowed to perform direct i/o
class GUI	
{
public:	
	window* pWind;	//Pointer to the Graphics Window
public:
	GUI();	
	~GUI();	
	window* CreateWind(int, int, int , int) const; //creates the application window

	/////////// Input Functoinality  /////////////////
	void GetPointClicked(int &x, int &y) const;//Get coordinate where user clicks
	string GetSrting() const ;	 //Returns a string entered by the user
	ActionType MapInputToActionType() const; //Read the user click and map to an action


	/////////// Output Functoinality  ////////////////
	void GUI::CreateToolBar() const;
	void CreateDrawToolBar() const;	//creates Draw mode toolbar & menu
	void CreateSizeToolBar() const; // create size toolBar & menue
	void CreatePlayToolBar() const;	//creates Play mode toolbar & menu
	void CreateStatusBar() const;	//create the status bar
	
	void ClearStatusBar() const;	//Clears the status bar
	void ClearDrawArea() const;	//Clears the drawing area
	
	// -- Figures Drawing functions
	void DrawSquare(Point P1, int length, GfxInfo RectGfxInfo, bool selected=false) const;  //Draw a Square
	void GUI::DrawElli(Point p1, Point p2,double ang1,double ang2, GfxInfo elliGfxInfo, bool selected) const; //Draw ellipse
	void GUI::DrawHexa(Point p1, Point p2, GfxInfo elliGfxInfo, bool selected) const;
	///TODO: Make similar functions for drawing all other figures.
	
	void PrintMessage(string msg) const;	//Print a message on Status bar

	color getCrntDrawColor() const;	//get current drwawing color
	color getCrntFillColor() const;	//get current filling color
	color getCrntBackgroundColor() const;
	int getCrntPenWidth() const;		//get current pen width

	void changeCrntDrawColor(color SelectedColor);

	void changeCrntFillColor(color SelectedColor);

	void setCrntBackgroundColor(color c) const;

	color StringToColor(string colorStr); //convert string to color type
	string ColorToString(color clr);     //convert color to string
	bool isMatchedColors(color c1, color c2);        //check if two colors are the same


};


#endif