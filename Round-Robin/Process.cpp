#include "Process.h"
#include "iostream"
#include "ProcessManager.h"
using namespace std;

char Process::ID = 'A';

Process::Process(int _execute, int _start)
{
	time_Execute = _execute;
	time_Remain = _execute;
	time_Start = _start;

	id = ID++;

	time_Turnover = time_Turnover_Weight = 0;
	time_Finished = 0;

	inQueue = false;
	finished = false;
}

char Process::GetID()
{
	return id;
}

float Process::Get_Time_Turnover()
{
	return time_Turnover;
}

float Process::Get_Time_Turnover_Weight()
{
	return time_Turnover_Weight;
}

int Process::Get_Time_Finished()
{
	return time_Finished;
}

int Process::Get_Time_Start()
{
	return time_Start;
}

int Process::Get_Time_Execute()
{
	return time_Execute;
}

int Process::Execute(int _q) {
	int result = time_Remain - _q;

	if (result < 0) {
		finished = true;
		inQueue = false;

		time_Finished = ProcessManager::Get_CurrentTime() + time_Remain;
		time_Turnover = time_Finished - time_Start;
		time_Turnover_Weight = time_Turnover / time_Execute;

		time_Remain = 0;

		return abs(result);	
	}
	else {
		time_Remain -= _q;

		if (time_Remain == 0) {

			time_Finished = ProcessManager::Get_CurrentTime() +  _q;
			time_Turnover = time_Finished - time_Start;
			time_Turnover_Weight = time_Turnover / time_Execute;

			inQueue = false;
			finished = true;
		}

		return 0;
	}
}

int Process::Get_Remain()
{
	return time_Remain;
}

void Process::SetInQueue(bool _v)
{
	inQueue = _v;
}

bool Process::GetInQueue()
{
	return inQueue;
}

bool Process::GetFinished()
{
	return finished;
}
