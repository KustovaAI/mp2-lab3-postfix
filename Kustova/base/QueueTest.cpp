
#include <iostream>
#include "queue.h"
#include "JobStream.h"
#include<iostream>
#include<locale>

using namespace std;

int main()
{
	setlocale(LC_ALL, "RUS");
	int  ncycles, queue_len, cores;
	int JobIntеns;
	cout << "введите длину очереди: ";
	cin >> queue_len;
	cout << "введите количество циклов: ";
	cin >> ncycles;
	cout << "введите интенсивность потока задач (в %): ";
	cin >> JobIntеns;
	cout << "введите  количество ядер процессора: ";
	cin >> cores;
	cout << endl;
	TJobStream job(queue_len);
	int taskID = 0, cmpltd_tasks = 0, ignor_queue = 0, ignor_proc = 0, idle_tacts = 0;
	job.StartStream(taskID, cmpltd_tasks, ignor_queue, ignor_proc, idle_tacts, ncycles, JobIntеns, cores);	
	double tmp;
	cout << endl;
	cout << "Количество поступивших в ВС заданий: " << taskID << endl;
	cout << "Количество обработанных заданий: " << cmpltd_tasks << endl;
	cout << "Число отказов в обслуживании очереди: " << ignor_queue << endl;
	cout << "Число отказов в обслуживании процессора: " << ignor_proc << endl;
	cout << "Число тактов простоя процессора: " << idle_tacts << endl;
	if (ncycles == 0) tmp = 0;
	else
	tmp = (idle_tacts * 100.0) / ncycles;
	cout << "Процент простоя процессора: " << tmp << "%" << endl;

	return 0;

}


