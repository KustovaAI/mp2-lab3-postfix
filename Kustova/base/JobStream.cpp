#include "JobStream.h"
#include <iostream>
using namespace std;


int TJobStream::GetNewJob(int _intense)
{
	if (rand() % 100 < _intense)
	{
		return 1;
	}
	return 0;
}

void TJobStream::StartStream(int &_taskID, int &cmpltd_tasks, int &_ignor_queue, int &_ignor_proc, int &_idle_tacts, int _tactsNum, int _intens, int _cores) // запустить поток
{
	_taskID = 0;
	int ind;
	int Core_buzy = 0;
	task = new Tasks[_tactsNum];
	for (long i = 0; i < _tactsNum; i++)
	{
		if (i < 6) cout << "Цикл №: " << i << ": " << endl;
		if (GetNewJob( _intens))		//попытка добавить в очередь
		{
			if (i < 6) cout << "	Поступила новая задача: " << endl;
			_taskID++;
			if (!q.IsFull())
			{
				task[_taskID].Initializing(double(clock()), _cores, _tactsNum);
				if (task[_taskID].GetCores() > _cores)
				{
					_ignor_queue++; // отказ в обсуживании 
					if (i < 6) cout << "	Новая задача не добавлена в очередь" << endl;
				}
				else
				{
					q.Push(_taskID);
					q.Sort(task);
					if (i < 6)
					{
						cout << "	Время создания задачи: " << task[_taskID].GetCreateTime() << endl;
						cout << "	Приоритет задачи: " << task[_taskID].Getpriority() << endl;
						cout << "	Сколько ядер требуется для решения задачи: " << task[_taskID].GetCores() << endl;
						cout << "	Количество тактов задачи: " << task[_taskID].GetTacts() << endl;
					}
				}
			}
			else
			{
				_ignor_queue++; // отказ в обсуживании 
				if (i < 6) cout << "	Новая задача не добавлена в очередь" << endl;
			}
		}
		if ((!q.IsEmpty())) // если очередь не пустая
		{
			if (task[q.GetFirst()].GetCores() <= _cores - Core_buzy)	//Если для задания найдутся свободные ядра
			{
				if (i < 6) cout << "	Новая задача поступила на обработку" << endl;
				ind = q.Get();
				Core_buzy += task[ind].GetCores();
				task[ind].Change_Is_in_progress();		
			}
			else
			{
				if (i < 6) cout << "	Новая задача не поступила на обработку" << endl;
				_ignor_proc++;		//отказ в обслуживании процессора
			}
			for (int j = 0; j < _tactsNum; j++)
				if (task[j].Get_Is_in_progress() == 1)
				{
					task[j].ChangeTacts();
					if (task[j].GetTacts() == 0)
					{
						Core_buzy -= task[j].GetCores();
						task[j].Change_Is_in_progress();
						cmpltd_tasks++;
					}
				}
		}
		else if (Core_buzy == 0)
		{
			int k = 0;
			for (int j = 0; j < _tactsNum; j++)
				if (task[j].Get_Is_in_progress() == 1)
				{
					k++;
					task[j].ChangeTacts();
					if (task[j].GetTacts() == 0)
					{
						Core_buzy -= task[j].GetCores();
						task[j].Change_Is_in_progress();
						cmpltd_tasks++;
					}
				}
			if (k == 0)
			{
				if (i < 6) cout << "	Процессор простаивает" << endl;
				_idle_tacts++; // простой процессора 
			}
		}
		
	}					
}
