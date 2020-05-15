#pragma once
#include "vector"
#include "Process.h"
#include "easyX.h"
#include "vector"

using namespace std;

static class Painter
{
private:
	static int width;
	static int height;

	static int rect_Width;
	static int rect_Height;

	static int spacing;

	static int center_X;
	static int center_Y;

	static COLORREF bkCol;
	
	static COLORREF drawColor_Disable;
	static COLORREF drawColor_InQueue;
	static COLORREF drawColor_Running;
	static COLORREF drawColor_Finished;

	static void DrawRect(int _x, int _y, Process* _p);
public:
	static void SetGrpahSize(int _w, int _h);
	static void SetBkColor(COLORREF _color);

	static void Draw(vector<Process*>& _pool);

	static void Initial();
};

