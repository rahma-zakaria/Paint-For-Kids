#include "CHexagon.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "../stdc++.h"
#include "../DEFS.h"


CHexagon::CHexagon(Point c, Point p, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	center = c;
	point = p;

	//radius = sqrt(pow((c.x - p.x), 2) + pow((c.y - p.y), 2));

	/*p.x = 50; p.y = 50;*/
	type = "HEXA";
}

CHexagon::CHexagon() {
	type = "HEXA";
} //default constractur

void CHexagon::DrawMe(GUI* pGUI) const
{
	//Call Output::	
	pGUI->DrawHexa(center, point, FigGfxInfo, Selected);


}

void CHexagon::Save(ofstream& outFile, GUI* pGUI)
{
	outFile << type << "\t" << ID << "\t" << center.x << "\t" << center.y <<
		"\t" << point.x << "\t" << point.y << "\t" << pGUI->ColorToString(FigGfxInfo.DrawClr) << "\t";
	if (FigGfxInfo.isFilled) outFile << pGUI->ColorToString(FigGfxInfo.FillClr) << endl;
	else outFile << "NO_FILL" << endl;
}

void CHexagon::Load(ifstream& inFile, GUI* pGUI)
{
	string FigureColor;
	string FigureFill;

	//Get a Pointer to the Interface
	inFile >> ID >> center.x >> center.y >> point.x >> point.y;
	inFile >> FigureColor >> FigureFill;
	FigGfxInfo.DrawClr = pGUI->StringToColor(FigureColor);
	FigGfxInfo.BorderWdth = UI.PenWidth;
	if (FigureFill == "NO_FILL") {
		FigGfxInfo.isFilled = false;
	}
	else {
		FigGfxInfo.FillClr = pGUI->StringToColor(FigureFill);;
		FigGfxInfo.isFilled = true;
	}
}
void CHexagon::Move(Point p, Point pMoveTo) {

	int DeltaX = (pMoveTo.x - p.x);
	int DeltaY = (pMoveTo.y - p.y);

	center.x += DeltaX;
	center.y += DeltaY;
	point.x += DeltaX;
	point.y += DeltaY;
}

int CHexagon::getFigureData(POINT& p1, POINT& p2)
{
	// not finished yet
	return -1;
}

string CHexagon::getFigureName() {
	return "Hexagon";
}

string CHexagon::getFigureColor() {
	return figColor;
}

float CHexagon::getArea() const {
	Point c0;
	c0.x = (center.x + point.x) / 2;
	c0.y = (center.y + point.y) / 2;
	int a = (max(c0.y, center.y) - min(c0.y, center.y)) * 2;
	float s = a / 0.866;
	return (s * 6 * a) / 2;
}
float CHexagon::getPremiter() const {
	Point c0;
	c0.x = (center.x + point.x) / 2;
	c0.y = (center.y + point.y) / 2;
	int a = (max(c0.y, center.y) - min(c0.y, center.y)) * 2;
	float s = a / 0.866;
	return s * 6;
}

int areaOfTriangle(Point c1, Point c2, Point c3)
{
	int area = (c1.x * (c2.y - c3.y) + c2.x * (c3.y - c1.y) + c3.x * (c1.y - c2.y)) / 2;
	//int area = ((c1.y+c2.y)*(c1.x-c2.x)+(c1.y+c3.y)*(c3.x-c1.x)-(c2.y+c3.y)*(c3.x-c2.x)) / 2;
	return area;
}

float getAngle(Point c0, Point c1, Point c2)
{
	Point a, b;
	float crossProduct, aMagnitude, bMagnitude;
	a.x = c0.x - c1.x;
	a.y = c0.y - c1.y;
	b.x = c0.x - c2.x;
	b.y = c0.y - c2.y;
	crossProduct = (a.x * b.x) + (a.y * b.y);
	aMagnitude = sqrt(pow(a.x, 2) + pow(a.y, 2));
	bMagnitude = sqrt(pow(b.x, 2) + pow(b.y, 2));
	return acos(crossProduct / (aMagnitude * bMagnitude));

}

bool PointInTriangle(Point c0, Point c1, Point c2, Point c3) {
	//int area = areaOfTriangle(c1, c2, c3);
	//int sArea1= areaOfTriangle(c0, c1, c2);
	//int sArea2 = areaOfTriangle(c0, c2, c3);
	//int sArea3 = areaOfTriangle(c0, c3, c1);
	//cout << area << "\n";
	//cout << sArea1 << "\n";
	//cout << sArea2 << "\n";
	//cout << sArea3 << "\n";
	//return area == sArea1 + sArea2 + sArea3;
	//return true;

	//float d = (c2.x * c3.y) - (c3.x * c2.y);
	//float wa = (c0.x * (c2.y - c3.y) + c0.y * (c3.x - c2.x) + (c2.x * c3.y) - (c3.x * c2.y))/d;
	//float wb = ((c0.x * c3.y) - (c0.y * c3.x)) / d;
	//float wc = ((c0.y * c2.x) - (c0.x * c2.y)) / d;
	//cout << d << " " << wa << " " << wb << " " << wc << "\n";
	//return wa >= 0 && wa <= 1 && wb >= 0 && wb <= 1 && wc >= 0 && wc <= 1;

	//cout << ((getAngle(c0, c1, c2) * 180) / 3.1416) << " " << ((getAngle(c0, c2, c3) * 180) / 3.1416) << " " << ((getAngle(c0, c3, c1) * 180) / 3.1416) << "\n";
	float sumOgAngles = ((getAngle(c0, c1, c2) * 180) / 3.1416) + ((getAngle(c0, c2, c3) * 180) / 3.1416) + ((getAngle(c0, c3, c1) * 180) / 3.1416);
	//cout << sumOgAngles << "\n\n";
	return sumOgAngles <= 360 && sumOgAngles >= 359.8;
}

bool CHexagon::PointInShape(int x, int y) const {
	Point c0, c1, c2, c3, c4, c5, c6, check;
	check.x = x;
	check.y = y;
	c0.x = (center.x + point.x) / 2;
	c0.y = (center.y + point.y) / 2;
	int a = (int)sqrt(pow(max(c0.y, center.y) - min(c0.y, center.y), 2) + pow(max(c0.x, center.x) - min(c0.x, center.x), 2));
	int s = int(a / 0.866);
	c1.x = c0.x - (s / 2);
	c1.y = c0.y - a;
	c2.x = c0.x + (s / 2);
	c2.y = c0.y - a;
	c3.x = c0.x + s;
	c3.y = c0.y;
	c4.x = c0.x + (s / 2);
	c4.y = c0.y + a;
	c5.x = c0.x - (s / 2);
	c5.y = c0.y + a;
	c6.x = c0.x - s;
	c6.y = c0.y;
	return PointInTriangle(check, c0, c1, c2) || PointInTriangle(check, c0, c2, c3) || PointInTriangle(check, c0, c3, c4)
		|| PointInTriangle(check, c0, c4, c5) || PointInTriangle(check, c0, c5, c6) || PointInTriangle(check, c0, c6, c1);
	//cout << c1.x << " " << c1.y << "\n";
	//cout << c2.x << " " << c2.y << "\n";
	//cout << c3.x << " " << c3.y << "\n";
	//cout << c4.x << " " << c4.y << "\n";
	//cout << c5.x << " " << c5.y << "\n";
	//cout << c6.x << " " << c6.y << "\n";
	//cout << x << " " << y << "\n";
	//return (x <= max(c1.x, c4.x) && x >= min(c1.x, c4.x) && y <= max(c1.y, c4.y) && y >= min(c1.y, c4.y)) && (y >= c1.y && y<= c4.y );
}

void CHexagon::Resize(float size) {

	//radius = radius * size;
	if (FigGfxInfo.Resize_Factor == .5) FigGfxInfo.Resize_Factor = -1;
	else if (FigGfxInfo.Resize_Factor == .25) FigGfxInfo.Resize_Factor = -(4.0 / 3);

	Point O;
	O.x = (center.x + point.x) / 2;
	O.y = (center.y + point.y) / 2;

	if (center.x <= O.x)
		center.x -= (O.x - center.x) * FigGfxInfo.Resize_Factor / 2;
	else
		center.x += (center.x - O.x) * FigGfxInfo.Resize_Factor / 2;

	if (point.x <= O.x)
		point.x -= (O.x - point.x) * FigGfxInfo.Resize_Factor / 2;
	else
		point.x += (point.x - O.x) * FigGfxInfo.Resize_Factor / 2;

	if (center.y <= O.y)
		center.y -= (O.y - center.y) * FigGfxInfo.Resize_Factor / 2;
	else
		center.y += (center.y - O.y) * FigGfxInfo.Resize_Factor / 2;

	if (point.y <= O.y)
		point.y -= (O.y - point.y) * FigGfxInfo.Resize_Factor / 2;
	else
		point.y += (point.y - O.y) * FigGfxInfo.Resize_Factor / 2;
}