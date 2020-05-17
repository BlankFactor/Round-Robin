#pragma once

#include "queue"
#include "list"
#include "vector"
#include "Process.h"

using namespace std;

static class ProcessManager
{
private:
	static int count;
	static int total;
	static int index;

	static int current_Time;
	

	static bool enable;
	static int timeclip;

	static queue<Process*> processQueue;
	static vector<Process*> processPool;
	static vector<Process*> process_All;

public:
	static char current_Id;

	static void Execute();

	static void AddProcess(Process* _process);
	static void Action();	
	static void SetTimeclip(int _v);

	static void DisplayInfo();
	static void DisplayProcessInfo();

	static int Get_CurrentTime();
};