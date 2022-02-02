#ifndef CFIGURE_H
#define CFIGURE_H

#include "..\defs.h"
#include "..\GUI\GUI.h"

//Base class for all figures
class CFigure
{
protected:
	int ID;		//Each figure has an ID
	bool Selected;	//true if the figure is selected.
	GfxInfo FigGfxInfo;	//Figure graphis info
	
	/// Add more parameters if needed.
	string type;
	static int nextID;

public:
	CFigure(GfxInfo FigureGfxInfo);
	CFigure();
	void SetSelected(bool s);	//select/unselect the figure
	bool IsSelected() const;	//check whether fig is selected

	virtual void DrawMe(GUI*) const  = 0 ;		//Draw the figure
	
	void ChngDrawClr(color Dclr);	//changes the figure's drawing color
	void ChngFillClr(color Fclr);	//changes the figure's filling color


	
	virtual bool PointInShape(int x, int y) const = 0;

	///The following functions should be supported by the figure class
	///It should be overridden by each inherited figure

	///Decide the parameters that you should pass to each function	
	virtual int getFigureData(POINT& p1, POINT& p2) = 0;
	virtual string getFigureName() = 0;

	//virtual void Rotate() = 0;	//Rotate the figure
	//virtual void Resize() = 0;	//Resize the figure
	virtual void Move(Point p, Point pMoveTo) = 0; //Moves Figure from point p to point pMoveTo
	virtual void Save(ofstream& OutFile, GUI* pGUI) = 0;	//Save the figure parameters to the file
	virtual void Load(ifstream& Infile, GUI* pGUI) = 0;	//Load the figure parameters to the file

	virtual void Resize(float) = 0;

	void setSize(float);

	void setnexID(int);
	virtual int getID();
	//virtual void PrintInfo(Output* pOut) = 0;	//print all figure info on the status bar
};

#endif