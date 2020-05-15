#pragma once
class Process
{
private:
	int time_Execute;
	int time_Remain;
	int time_Start;

	int time_Finished;
	float time_Turnover;
	float time_Turnover_Weight;

	bool inQueue;
	bool finished;

	char id;
	static char ID;
public:
	Process(int _execute, int _start);

	char GetID();

	float Get_Time_Turnover();
	float Get_Time_Turnover_Weight();

	int Get_Time_Finished();
	int Get_Time_Start();
	int Get_Time_Execute();
	int Execute(int _q);

	int Get_Remain();

	void SetInQueue(bool _v);

	bool GetInQueue();
	bool GetFinished();
};

