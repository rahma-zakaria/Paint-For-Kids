#include "GUI.h"
#define _USE_MATH_DEFINES
#include <math.h>
//constructor make necessary initializations
GUI::GUI()
{
	//Initialize user interface parameters
	UI.InterfaceMode = MODE_DRAW;
	
	UI.width = 1300;
	UI.height = 700;
	UI.wx = 5;
	UI.wy =5;

	
	UI.StatusBarHeight = 50;
	UI.ToolBarHeight = 50;
	UI.MenuItemWidth = 65;
	
	UI.DrawColor = BLUE;	//Drawing color
	UI.FillColor = GREEN;	//Filling color
	UI.MsgColor = RED;		//Messages color
	UI.BkGrndColor = LIGHTGOLDENRODYELLOW;	//Background color
	UI.HighlightColor = MAGENTA;	//This color should NOT be used to draw figures. use if for highlight only
	UI.StatusBarColor = TURQUOISE;
	UI.PenWidth = 3;	//width of the figures frames

	
	//Create the output window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	//Change the title
	pWind->ChangeTitle("Paint for Kids - Programming Techniques Project");
	
	CreateDrawToolBar();

	CreateStatusBar();
	
	
}


//======================================================================================//
//								Input Functions										    //
//======================================================================================//


void GUI::GetPointClicked(int &x, int &y) const
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}

string GUI::GetSrting() const 
{
	string Label;
	char Key;
	while(1)
	{
		pWind->WaitKeyPress(Key);
		if(Key == 27 )	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if(Key == 13 )	//ENTER key is pressed
			return Label;
		if(Key == 8 )	//BackSpace is pressed
			Label.resize(Label.size() -1 );			
		else
			Label+= Key;
		PrintMessage(Label);
	}
}

//This function reads the position where the user clicks to determine the desired action
ActionType GUI::MapInputToActionType() const
{	
	int x,y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

	if(UI.InterfaceMode == MODE_DRAW)	//GUI in the DRAW mode
	{
		//[1] If user clicks on the Toolbar
		if ( y >= 0 && y < UI.ToolBarHeight)
		{	
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_PALETTE: 
				if (x < ITM_PALETTE * UI.MenuItemWidth + UI.MenuItemWidth / 5)
				{
					return COLOR_BLACK;
				}
				else if (x < ITM_PALETTE * UI.MenuItemWidth + UI.MenuItemWidth * 2 / 5)
				{
					return COLOR_WHITE;
				}
				else if (x < ITM_PALETTE * UI.MenuItemWidth + UI.MenuItemWidth * 3 / 5)
				{
					return COLOR_RED;
				}
				else if (x < ITM_PALETTE * UI.MenuItemWidth + UI.MenuItemWidth * 4 / 5)
				{
					return COLOR_GREEN;
				}
				else
				{
					return COLOR_BLUE;
				}
			case ITM_CHANGECDC: return CHNG_DRAW_CLR;
			case ITM_CHANGECFC: return CHNG_FILL_CLR;
			case ITM_BACKGROUND_CLR: return CHNG_BK_CLR;
			case ITM_SQUR: return DRAW_SQUARE;
			case ITM_ELPS: return DRAW_ELPS;
			case ITM_Hexa: return DRAW_HEX;
			case ITM_Select:return SELECT;
			case ITM_Save: return SAVE;			
			case ITM_Load: return LOAD;
			case ITIM_RESIZE: return RESIZE;
			case ITIM_UNDO: return UNDO;
			case ITIM_REDO: return REDO;
			case ITIM_MOVE: return MOVE;
			case ITIM_SwitchPlay: return TO_PLAY;    //switch To play Mode 
			case ITM_SEND_TO_BACK: return SEND_BACK;
			case ITM_BRING_TO_FRONT: return BRNG_FRNT;
			case ITM_EXIT: return EXIT;	
			
			default: return EMPTY;	//A click on empty place in desgin toolbar
			}
		}

		//[2] User clicks on the drawing area
		if ( y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return DRAWING_AREA;	
		}
		
		//[3] User clicks on the status bar
		return STATUS;
	}
	else if (UI.InterfaceMode == MODE_SIZE)
	{
		//[1] If user clicks on the Toolbar
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//If division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on
			switch (ClickedItemOrder)
			{
			case ITM_HALF: return HALF;
			case ITM_QUARTER: return QUARTER;
			case ITM_DOUBLE:   return DOUBLE1;
			case ITM_QUADRUPLE: return QUADRUPLE;
			case ITM_BACK:  return BACK;
			}
		}
	}
	else	//GUI is in PLAY mode
	{
		///TODO:
		//perform checks similar to Draw mode checks above
		
		//[1] If user clicks on the Toolbar
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			switch (ClickedItemOrder)
			{
			case ITIM_SwitchDraw: return TO_DRAW;
			case ITIM_SelectByShape: return TO_PLAY_SELECT_BY_SHAPE;
			case ITIM_SelectByColor: return TO_PLAY_SELECT_BY_COLOR;
			case ITIM_SelectByBoth:return TO_PLAY_SELECT_BY_BOTH;
			default: return EMPTY;	//A click on empty place in desgin toolbar
			}
		}

		//[2] User clicks on the drawing area
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return DRAWING_AREA;
		}

		//[3] User clicks on the status bar
		return STATUS;
	}	

}
//======================================================================================//
//								Output Functions										//
//======================================================================================//

window* GUI::CreateWind(int w, int h, int x, int y) const
{ 
	window* pW = new window(w, h, x, y);
	pW->SetBrush(UI.BkGrndColor);
	pW->SetPen(UI.BkGrndColor, 1);
	pW->DrawRectangle(0, UI.ToolBarHeight, w, h);	
	return pW;
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::CreateStatusBar() const
{
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}

void GUI::CreateToolBar() const
{
	pWind->SetPen(WHITE, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::ClearStatusBar() const
{
	//Clear Status bar by drawing a filled white Square
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::CreateDrawToolBar() const
{
	UI.InterfaceMode = MODE_DRAW;

	//You can draw the tool bar icons in any way you want.
	//Below is one possible way
	
	//First prepare List of images for each menu item
	//To control the order of these images in the menu, 
	//reoder them in UI_Info.h ==> enum DrawMenuItem
	string MenuItemImages[DRAW_ITM_COUNT];
	MenuItemImages[ITM_SQUR] = "images\\MenuItems\\Square.jpg";
	MenuItemImages[ITM_ELPS] = "images\\MenuItems\\Elips.jpg";
	MenuItemImages[ITM_Hexa] = "images\\MenuItems\\Hexa.jpg";
	MenuItemImages[ITM_Select] = "images\\MenuItems\\Select.jpg";
	//MenuItemImages[ITM_Delete] = "images\\MenuItems\\delete.jpg";
	MenuItemImages[ITM_Save] = "images\\MenuItems\\Save.jpg";
	MenuItemImages[ITM_Load] = "images\\MenuItems\\Load.jpg";
	MenuItemImages[ITIM_MOVE] = "images\\MenuItems\\Move.jpg";
	MenuItemImages[ITIM_RESIZE] = "images\\MenuItems\\Resize.jpg";
	MenuItemImages[ITM_PALETTE] = "images\\MenuItems\\Menu_Palette.jpg";
	MenuItemImages[ITM_CHANGECDC] = "images\\MenuItems\\drawcolor.jpg";
	MenuItemImages[ITM_CHANGECFC] = "images\\MenuItems\\Menu_FillColor.jpg";
	MenuItemImages[ITM_BACKGROUND_CLR] = "images\\MenuItems\\Background_Color.jpg";
	MenuItemImages[ITIM_UNDO] = "images\\MenuItems\\Undo.jpg";
	MenuItemImages[ITIM_REDO] = "images\\MenuItems\\Redo.jpg";
	MenuItemImages[ITIM_SwitchPlay] = "images\\MenuItems\\play.jpg";
	MenuItemImages[ITM_SEND_TO_BACK] = "images\\MenuItems\\Send_to_Back.jpg";
	MenuItemImages[ITM_BRING_TO_FRONT] = "images\\MenuItems\\Bring_to_Front.jpg";
	MenuItemImages[ITM_EXIT] = "images\\MenuItems\\Exit.jpg";
	

	//TODO: Prepare images for each menu item and add it to the list

	//Draw menu item one image at a time
	for(int i=0; i<DRAW_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*UI.MenuItemWidth,0,UI.MenuItemWidth, UI.ToolBarHeight);


	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);	

}
// new toolBar
void GUI::CreateSizeToolBar() const
{
	CreateToolBar();
	//CreateStatusBar();
	UI.InterfaceMode = MODE_SIZE;

	//First prepare List of images for each menu item
	//To control the order of these images in the menu, 
	//reoder them in UI_Info.h ==> enum DrawMenuItem
	string MenuItemImages[SIZE_ITM_COUNT];
	MenuItemImages[ITM_QUARTER] = "images\\MenuItems\\Quarter.jpg";
	MenuItemImages[ITM_HALF] = "images\\MenuItems\\Half.jpg";
	MenuItemImages[ITM_DOUBLE] = "images\\MenuItems\\2.jpg";
	MenuItemImages[ITM_QUADRUPLE] = "images\\MenuItems\\4.jpg";
	MenuItemImages[ITM_BACK] = "images\\MenuItems\\Back.jpg";

	//TODO: Prepare images for each menu item and add it to the list

	//Draw menu item one image at a time
	for (int i = 0; i < SIZE_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);



	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);

}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::CreatePlayToolBar() const
{
	CreateToolBar();
	UI.InterfaceMode = MODE_PLAY;
	///TODO: write code to create Play mode menu
	string MenuItemImages[PLAY_ITM_COUNT];
	MenuItemImages[ITIM_SwitchDraw] = "images\\MenuItems\\draw.jpg";
	MenuItemImages[ITIM_SelectByShape] = "images\\MenuItems\\select-shape-icon.jpg";
	MenuItemImages[ITIM_SelectByColor] = "images\\MenuItems\\select-color-icon.jpg";
	MenuItemImages[ITIM_SelectByBoth] = "images\\MenuItems\\select-coloredShape-icon.jpg";

	//TODO: Prepare images for each menu item and add it to the list

	//Draw menu item one image at a time
	for (int i = 0; i < PLAY_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);

	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);

}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::ClearDrawArea() const
{
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.width, UI.height - UI.StatusBarHeight);	
	
}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::PrintMessage(string msg) const	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar
	
	pWind->SetPen(UI.MsgColor, 50);
	pWind->SetFont(20, BOLD , BY_NAME, "Arial");   
	pWind->DrawString(10, UI.height - (int)(UI.StatusBarHeight/1.5), msg);
}
//////////////////////////////////////////////////////////////////////////////////////////

color GUI::getCrntDrawColor() const	//get current drwawing color
{	return UI.DrawColor;	}
//////////////////////////////////////////////////////////////////////////////////////////

color GUI::getCrntFillColor() const	//get current filling color
{	return UI.FillColor;	}
//////////////////////////////////////////////////////////////////////////////////////////
color GUI::getCrntBackgroundColor() const	//get current filling color
{
	return UI.BkGrndColor;
}
//////////////////////////////////////////////////////////////////////////////////////////
	
int GUI::getCrntPenWidth() const		//get current pen width
{	return UI.PenWidth;	}

void GUI::changeCrntDrawColor(color SelectedColor)
{
	UI.DrawColor = SelectedColor;
}

void GUI::changeCrntFillColor(color SelectedColor)
{
	UI.FillColor = SelectedColor;
	
}

// change background color
void GUI::setCrntBackgroundColor(color c) const
{
	UI.BkGrndColor = c;
}

color GUI::StringToColor(string colorStr)    //convert string to color type
{
	if (colorStr == "BLUE") return BLUE;
	else if (colorStr == "BLACK") return BLACK;
	else if (colorStr == "RED") return RED;
	else if (colorStr == "YELLOW") return YELLOW;
	else if (colorStr == "WHITE") return WHITE;
	else if (colorStr == "GREEN") return GREEN;
	else if (colorStr == "ORANGE") return ORANGE;
}

string GUI::ColorToString(color clr)    //convert string to color type
{

	if (isMatchedColors(clr, BLUE)) return "BLUE";
	else if (isMatchedColors(clr, BLACK)) return "BLACK";
	else if (isMatchedColors(clr, RED)) return "RED";
	else if (isMatchedColors(clr, YELLOW)) return "YELLOW";
	else if (isMatchedColors(clr, WHITE)) return "WHITE";
	else if (isMatchedColors(clr, GREEN)) return "GREEN";
	else if (isMatchedColors(clr, ORANGE)) return "ORANGE";
	else if (isMatchedColors(clr, LIGHTGOLDENRODYELLOW)) return "LIGHTGOLDENRODYELLOW";

}

bool GUI::isMatchedColors(color c1, color c2)
{
	if (c1.ucBlue == c2.ucBlue && c1.ucRed == c2.ucRed && c1.ucGreen == c2.ucGreen)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//======================================================================================//
//								Figures Drawing Functions								//
//======================================================================================//

void GUI::DrawSquare(Point P1, int length, GfxInfo RectGfxInfo, bool selected) const
{
	color DrawingClr;
	if(selected)	
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else			
		DrawingClr = RectGfxInfo.DrawClr;
	
	pWind->SetPen(DrawingClr, RectGfxInfo.BorderWdth);	//Set Drawing color & width
	
	drawstyle style;
	if (RectGfxInfo.isFilled)	
	{
		style = FILLED;		
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else	
		style = FRAME;

	
	pWind->DrawRectangle(P1.x, P1.y, P1.x +length, P1.y+length, style);
	//pWind->DrawLine(P1.x, P1.y, P1.x + length, P1.y + length, style);

}

void GUI::DrawElli(Point p1,Point p2,double startAngle,double  endAngle, GfxInfo elliGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = elliGfxInfo.DrawClr;


	pWind->SetPen(DrawingClr, elliGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (elliGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(elliGfxInfo.FillClr);
	}
	else
		style = FRAME;


	pWind->DrawEllipse(p1.x, p1.y, p2.x, p1.y, style);
	pWind->DrawArc(p1.x, p1.y, p2.x, p2.y, startAngle, endAngle, style);

}

void GUI::DrawHexa(Point P1, Point P2,int radius, GfxInfo hexaGfxInfo, bool selected) const
{
	//radius = (sqrt(pow((P1.x - P2.x), 2) + pow((P1.y - P2.y), 2))) / 2;
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = hexaGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, 3);
	drawstyle style;
	if (hexaGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(hexaGfxInfo.FillClr);
	}
	else
		style = FRAME;

	int n = 6;
	int HexaX[6]{};
	int HexaY[6]{};
	

	for (int i = 0; i < n; i++) {
		HexaX[i] = ((static_cast<double>(P1.x) + P2.x) / 2) + radius * cos(2 * M_PI * i / n);
		HexaY[i] = ((static_cast<double>(P1.y) + P2.y) / 2) + radius * sin(2 * M_PI * i / n);	
	}
	/*int HexaX[6] = {P1.x + P2.x, P1.x - P2.x, P1.x - 2 * P2.x, P1.x - P2.x ,P1.x + P2.x, P1.x + 2 * P2.x}, HexaY[6] = {P1.y - P2.y, P1.y - P2.y, P1.y, P1.y + P2.y,P1.y + P2.y,P1.y};*/

	pWind->DrawPolygon(HexaX, HexaY, 6, style);

}

//////////////////////////////////////////////////////////////////////////////////////////
GUI::~GUI()
{
	delete pWind;
}

