#pragma once
#include<iostream>
#include<locale>
#include "queue.h"
#include "Tasks.h"
using namespace std;

class TJobStream
{
	private:
		TQueue <int> q;
		Tasks *task;
		int intense; // вероятность генерации задания на текущем такте
	public:
		
		TJobStream(int size_queue) : q(size_queue) {};
		void StartStream(int &_taskID, int &cmpltd_tasks, int &_ignor_queue, int &_ignor_proc, int &_idle_tacts, int _tactsNum, int _intens, int _cores); // запустить поток
		int GetNewJob(int _intense);	//генерация нового задания
}; 
