#include <iostream>
#include "conio.h"
#include "easyx.h"
#include "cstdlib"
#include "windows.h"
#include "ProcessManager.h"
#include "Process.h"
#include "vector"
#include "stdlib.h"
#include "time.h"

using namespace std;

bool son = true;
int a = 1;

//线程函数
DWORD WINAPI ThreadProc(LPVOID lpParameter)
{
	for (int i = 0; i < 10; i++) {
		Sleep(1000);
		ProcessManager::AddProcess(new Process(rand()%100,rand()% (ProcessManager::Get_CurrentTime() + 100) + ProcessManager::Get_CurrentTime()));
	}
	return 0L;
}


int main()
{

	
	int count;
	cout << "输入进程数 : ";
	cin >> count;
	if (count <= 0)count = 1;
	cout << "确认进程数 : " << count << endl;
	cout << "**********任意键继续**********" << endl;
	_getch();
	system("cls");

	bool random = false;
	char temp;
	srand((unsigned)time(0));
	cout << "是否随机生成开始-运行时间? Y/y->true other->false ";
	cin >> temp;
	if (temp == 'Y' or temp == 'y')random = true;
	cout << "确认是否随机生成 : " << random << endl;
	cout << "**********任意键继续**********" << endl;
	_getch();
	system("cls");

	char id = 'A';

	srand((unsigned)time(NULL));
	while (count--) {
		int exe;
		int start;

		if (random) {
			start = rand() % 100;
			exe = rand() % 100;
		}
		else {
			cout << "输入进程 开始时间-运行时间 : " << endl;
			cin >> start >> exe;
		}
		if (start < 0)start = 0;
		if (exe < 0)exe = 1;

		ProcessManager::AddProcess(new Process(exe, start));

		cout << "确认进程 " << id++ << "\t开始时间 : "<<start<<"\t运行时间"<<exe<<endl;
		Sleep(10);
	}
	cout << "**********任意键继续**********" << endl;
	_getch();
	system("cls");

	int timeclip;
	cout << "输入时间片大小 : ";
	cin >> timeclip;
	if (timeclip < 1)timeclip = 1;
	cout << "确认时间片大小 : " << timeclip << endl;
	ProcessManager::SetTimeclip(timeclip);
	cout << "**********任意键继续**********" << endl;
	_getch();
	system("cls");

	//HANDLE thread = CreateThread(NULL, 0, ThreadProc, NULL, 0, NULL);
	//CloseHandle(thread);

	ProcessManager::Action();
	return 0;
}

