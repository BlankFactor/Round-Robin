#include "ProcessManager.h"
#include "windows.h"
#include "iostream"
#include "queue"
#include "vector"
#include "Painter.h"
#include "conio.h"
#include "iomanip"

using namespace std;

int ProcessManager::count = 0;
int ProcessManager::total = 0;
int ProcessManager::index = 0;
int ProcessManager::current_Time = 0;
int ProcessManager::timeclip = 5;

bool ProcessManager::enable = false;

char ProcessManager::current_Id = '0';

queue<Process*> ProcessManager::processQueue;
vector<Process*> ProcessManager::processPool;
vector<Process*> ProcessManager::process_Finished;
vector<Process*> ProcessManager::process_All;

void ProcessManager::Execute()
{
	while (enable) {
		
		//_getch();

		try {
			// ׷���½���
			if (processPool.size() > 0) {
				vector<Process*> temp(processPool);
				auto it = temp.begin();
				int offset = 0;
				for (int i = 0; i < processPool.size(); i++) {
					if (processPool[i]->Get_Time_Start() <= current_Time) {
						processQueue.push(processPool[i]);
						temp.erase(it + (i - offset));
						processPool[i]->SetInQueue(true);

						it = temp.begin();
						offset++;
					}
				}

				processPool.clear();
				processPool = temp;
				temp.~vector();
			}
		}
		catch (exception& e) {
			cerr << e.what() << endl;
		}

		// �������޽����һ��н���δ�������
		if (processQueue.empty() && total != count) {
			current_Time += timeclip;
			Painter::Draw(process_All);
			DisplayCurrentInfo();
			Sleep(1000);
			continue;
		}

		Process* p;
		p = processQueue.front();
		processQueue.pop();
		int remain = p->Execute(timeclip);
		current_Time += timeclip - remain;
		current_Id = p->GetID();
		

		if (!p->GetFinished()) {
			processQueue.push(p);
		}
		else {
			total++;
			process_Finished.push_back(p);
			cout << endl;
		}

		// ȫ�����̴������
		if (total == count) {
			current_Id = '0';
			break;
		}
		Painter::Draw(process_All);
		DisplayCurrentInfo();
		Sleep(100);

		current_Id = '0';
	}

	Painter::Draw(process_All);
	DisplayCurrentInfo();
	DisplayInfo();
	_getch();
	closegraph();
}

void ProcessManager::Action() {
	Painter::Initial();
	Painter::Draw(process_All);
	DisplayCurrentInfo();
	enable = true;

	if (count <= 0) {
		enable = false;
		exit(0);
	}

	auto min = processPool.begin();
	auto it = processPool.begin();
	int minT = processPool[0]->Get_Time_Start();
	int minI = 0;
	for (int i = 0; i < processPool.size();i++,it++) {
		if (processPool[i]->Get_Time_Start() < minT) {
			minT = processPool[i]->Get_Time_Start();
			min = it;
			minI = i;
		}
	}

	current_Time += minT;
	processQueue.push(processPool[minI]);
	processPool.erase(min);
	processQueue.front()->SetInQueue(true);
	Execute();
}

void ProcessManager::SetTimeclip(int _v)
{
	if (_v < 1) 
		timeclip = 1;
	else
	{
		timeclip = _v;
	}
}

void ProcessManager::DisplayInfo()
{
	float total_Turnover = 0;
	double total_Turnover_Weight = 0;

	for (int i = 0; i < process_Finished.size(); i++) {
		total_Turnover += process_Finished[i]->Get_Time_Turnover();
		total_Turnover_Weight += process_Finished[i]->Get_Time_Turnover_Weight();
	}

	cout << fixed << setprecision(2)<<endl;
	cout << "************************************************************************" << endl;
	cout << "�����" << endl;
	cout << "�ܺ�ʱ : " << current_Time << endl;
	cout << "����ת : " << total_Turnover << endl;
	cout << "�ܴ�Ȩ��ת : " << total_Turnover_Weight << endl;
	cout << "ƽ����ת : " << (float)total_Turnover / count << endl;
	cout << "ƽ����Ȩ��ת : " << total_Turnover_Weight / count << endl;
	cout << "------------------------------------------------------------------------" << endl;
	cout << "����ID\t\t��תʱ��\t��Ȩ��ת\t����ʱ��" << endl;
	for (int i = 0; i < count; i++) {
		cout << process_All[i]->GetID() << "\t\t" << process_All[i]->Get_Time_Turnover() << "\t\t" << process_All[i]->Get_Time_Turnover_Weight() <<"\t\t" << process_All[i]->Get_Time_Finished() << endl;
	}
	cout << "************************************************************************" << endl;
}

void ProcessManager::DisplayCurrentInfo()
{
	cout << endl;
	cout << "��ǰʱ�� : " << current_Time << endl;
	cout << "************************************************************************" << endl;
	cout << "����ID\t\t����ʱ��\t����ʱ��\t��ǰ״̬\tʣ��ʱ��" << endl;
	for (int i = 0; i < count; i++) {
		string stats;
		if 
			(process_All[i]->GetID() == current_Id)stats = "������";
		else
		{
			stats = process_All[i]->GetFinished() ? "���" : process_All[i]->GetInQueue() ? "����" : "δ����";
		}

		cout << process_All[i]->GetID() << "\t\t" << process_All[i]->Get_Time_Start() << "\t\t" << process_All[i]->Get_Time_Execute() <<"\t\t"<<stats<<"\t\t"<<process_All[i]->Get_Remain()<<endl;
	}
	cout << "************************************************************************" << endl;
}

int ProcessManager::Get_CurrentTime()
{
	return current_Time;
}

void ProcessManager::AddProcess(Process* _process)
{
	count++;
	process_All.push_back(_process);
	processPool.push_back(_process);
}
