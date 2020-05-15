#include "Painter.h"
#include "iostream"
#include "cstring"
#include "string"
#include "ProcessManager.h"
#include "conio.h"
#include "math.h"

using namespace std;

int Painter::height = 800;
int Painter::width = 1200;

int Painter::rect_Height = 100;
int Painter::rect_Width = 30;

int Painter::center_X = width / 2;
int Painter::center_Y = height / 2;

int Painter::spacing = 50;

COLORREF Painter::bkCol = RGB(155, 169, 208);

COLORREF Painter::drawColor_Disable = RGB(96,96,96);
COLORREF Painter::drawColor_InQueue = RGB(253,249,146);
COLORREF Painter::drawColor_Finished = RGB(158, 255, 159);
COLORREF Painter::drawColor_Running = RGB(253,85,80);

void Painter::SetGrpahSize(int _w, int _h)
{
	width = _w;
	height = _h;
}

void Painter::SetBkColor(COLORREF _color)
{
	bkCol = _color;
}

void Painter::Initial() {
	initgraph(width, height, EW_SHOWCONSOLE);
}

void Painter::Draw(vector<Process*>& _pool) {
	setbkcolor(bkCol);
	cleardevice();
	setfillcolor(drawColor_Disable);


	int totalWidth = _pool.size() * rect_Width + ((_pool.size() - 1) * spacing);

	int leftistOffset = ((rect_Width + spacing) * (_pool.size() - 1) / 2) * (-1);
	int topOffset = 0;

	int row = 1;
	int maxcolumn = _pool.size();
	if (totalWidth > width) {
		row = ceil((float)totalWidth / width);

		int maxcount = width / rect_Width;
		while (true) {
			if ((maxcount * rect_Width + (maxcount - 1) * spacing) < width) {
				break;
			}

			maxcount--;
		}

		maxcolumn = maxcount;

		topOffset = ((row - 1) * (rect_Height + spacing)) / 2 * (-1);
		leftistOffset = ((rect_Width + spacing) * (maxcolumn - 1) / 2) * (-1);
	}

	int i = 0;
	while(i < _pool.size()){
		for (int r = 0; r < row; r++) {

			for (int c = 0; c < maxcolumn; c++) {
				if (_pool[i]->GetFinished()) {
					setfillcolor(drawColor_Finished);
				}
				else if (_pool[i]->GetInQueue()) {
					setfillcolor(drawColor_InQueue);
				}
				else {
					setfillcolor(drawColor_Disable);
				}

				if (ProcessManager::current_Id == _pool[i]->GetID()) {
					setfillcolor(drawColor_Running);
				}

				DrawRect(center_X + (leftistOffset + c * (spacing + rect_Width)), center_Y +(topOffset + r * (spacing + rect_Height + 10)), _pool[i]);

				i++;

				if (i >= _pool.size())break;
			}
		}

	}

	

	string str = "Current time : ";
	str.append(to_string(ProcessManager::Get_CurrentTime()));
	TCHAR* tcs = new TCHAR[str.size() + 1];
	tcs[str.size()] = 0;
	copy(str.begin(), str.end(), tcs);
	outtextxy(10,10 , tcs);
	str.clear();
}

void Painter::DrawRect(int _x, int _y,Process* _p) {
	int left = _x - (rect_Width / 2);
	int top = _y - (rect_Height / 2);
	int right = _x + (rect_Width / 2);
	int bottom = _y + (rect_Height / 2);
	fillrectangle(left, top, right, bottom);

	int i = 0;
	int spacing = 20;

	string str = "ID : ";
	str.push_back(_p->GetID());
	TCHAR* tcs = new TCHAR[str.size() + 1];	
	tcs[str.size()] = 0;
	copy(str.begin(), str.end(), tcs);
	outtextxy(left, bottom + (i++ * spacing), tcs);
	str.clear();

	str = "Start : ";
	str.append(to_string(_p->Get_Time_Start()));
	tcs = new TCHAR[str.size() + 1];
	tcs[str.size()] = 0;
	copy(str.begin(), str.end(), tcs);
	outtextxy(left, bottom + (i++ * spacing), tcs);
	str.clear();

	str = "Exec : ";
	str.append(to_string(_p->Get_Remain()));
	tcs = new TCHAR[str.size() + 1];
	tcs[str.size()] = 0;
	copy(str.begin(), str.end(), tcs);
	outtextxy(left, bottom + (i++ * spacing), tcs);
	str.clear();

	str.~basic_string();
}
