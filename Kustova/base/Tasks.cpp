#include "Tasks.h"
#include <iostream>
using namespace std;

Tasks::Tasks()
{
	index = 0;
	create_time = 0;
	priority = 0;		
	Task_cores = 0;
	Task_tacts = 0;
	Is_in_progress = 0;
}


void Tasks::Initializing(double _create_time, int _cores, int _tacts)
{
	
	if (_cores <= 0) throw "negative";
	if (_tacts <= 0) throw "negative";
	create_time = _create_time;
	priority = rand() % 3 + 1;		
	Task_cores = rand() % (_cores + _cores/2) + 1;
	Task_tacts = rand() % 5 + 1;
	Is_in_progress = 0;
}

void Tasks::Change_Is_in_progress()
{
	if (Is_in_progress == 0) Is_in_progress = 1;
	else Is_in_progress = 0;
}

void Tasks::ChangeTacts()
{
	Task_tacts--;
}

void Tasks::ChangeCores()
{
	Task_cores--;
}

void Tasks::ChangePriority()
{
	if (priority == 0) return;
	priority--;
}