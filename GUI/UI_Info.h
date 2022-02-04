#ifndef UI_INFO_H
#define UI_INFO_H

#include "..\CMUgraphicsLib\CMUgraphics.h"

//User Interface information file.
//This file contains info that is needed by Input and Output classes to
//handle the user interface

enum GUI_MODE	//Graphical user interface mode
{
	MODE_DRAW,	//Drawing mode (startup mode)
	MODE_PLAY,	//Playing mode
	MODE_SIZE  //create size mode 
};

enum DrawMenuItem //The items of the Draw menu (you should add more items)
{
	//Note: Items are ordered here as they appear in menu
	//If you want to change the menu items order, change the order here
	ITM_SQUR,		//Square item in menu
	ITM_ELPS,		//Ellipse item in menu
	
	//TODO: Add more items names here
	ITM_Hexa,       //Hexa item in menue
	 
	ITM_Select,     //Select item in menu

	ITM_Save,       //Save item in menue
	ITM_Load,       //Load item in menue
	ITIM_RESIZE,    //create resize menue 
	ITM_PALETTE,
	ITM_CHANGECDC,
	ITM_CHANGECFC,
	ITM_BACKGROUND_CLR,
	ITIM_UNDO,    //undo item in menue
	ITIM_REDO,    //redo item in menue 
	ITIM_MOVE,    //Move item in menue 
	ITIM_SwitchPlay,    //switch To play Mode 
	ITM_SEND_TO_BACK,   //send to back item in menue
	ITM_BRING_TO_FRONT, //bring to front in menue
	ITM_EXIT,		//Exit item
	
	DRAW_ITM_COUNT		//no. of menu items ==> This should be the last line in this enum
	
};

enum sizeMenueItems //The items of the Draw menu (you should add more items)
{
	//Note: Items are ordered here as they appear in menu
	//If you want to change the menu items order, change the order here
	ITM_QUARTER,		//quarter item in menu
	ITM_HALF,		//Halh item in menu


	//TODO: Add more items names here
	ITM_DOUBLE,       //Double item in menue
	
	ITM_QUADRUPLE, //Quadruple item in menue
	ITM_BACK, // back item in menue

	SIZE_ITM_COUNT		//no. of menu items ==> This should be the last line in this enum

};

enum PlayMenuItem //The items of the Play menu (you should add more items)
{
	ITIM_SwitchDraw,    //switch To Draw Mode 
	ITIM_SelectByShape,
	ITIM_SelectByColor,
	ITIM_SelectByBoth,
	//ITM_EXIT,		//Exit item

	PLAY_ITM_COUNT		//no. of menu items ==> This should be the last line in this enum
};





__declspec(selectany) //This line to prevent "redefinition error"

struct UI_Info	//User Interface Info.
{
	GUI_MODE InterfaceMode;
	
	int	width, height,	//Window width and height
		wx , wy,			//Window starting coordinates
		StatusBarHeight,	//Status Bar Height
		ToolBarHeight,		//Tool Bar Height (distance from top of window to bottom line of toolbar)
		MenuItemWidth;		//Width of each item in toolbar menu
	bool FillFigures;


	color DrawColor;		//Drawing color
	color FillColor;		//Filling color
	color HighlightColor;	//Highlighting color
	color MsgColor;			//Messages color
	color BkGrndColor;		//Background color
	color StatusBarColor;	//Status bar color
	int PenWidth;			//width of the pen that draws shapes

	/// Add more members if needed
	
}UI;	//create a global object UI

#endif