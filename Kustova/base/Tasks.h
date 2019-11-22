#pragma once
class Tasks
{
private:
	int index;
	double create_time;			 
	int priority;
	int Task_cores;					
	int Task_tacts;
	bool Is_in_progress;
public:
	Tasks();
	
	int GetIndex() { return index; }
	int Getpriority() { return priority; }
	int GetCreateTime() { return create_time; }
	int GetCores() { return Task_cores; }
	int GetTacts() { return Task_tacts; }
	int Get_Is_in_progress() { return Is_in_progress; }
	void Initializing(double _create_time, int _cores, int _tacts);
	void ResetCreateTime(int _create_time) { create_time = _create_time; }
	void Change_Is_in_progress();
	void ChangeTacts(); 
	void ChangeCores(); 
	void ChangePriority(); 
};

