#pragma once
#include "stdafx.h"

class Process
{
public:
	Process();
	Process(long id, long steps_to_do, double time_for_one_process, status status)
		: ID(id),stepsToDo(steps_to_do),stepsLeft(steps_to_do),TimeForOneProcess(time_for_one_process),status(status) {;};
	~Process();
	long getID() const;
	void setID(long id);
	long getStepsToDo() const;
	void setStepsToDo(long steps_to_do);
	long getStepsLeft() const;
	void setStepsLeft(long steps_left);
	void subStepsLeft();
	long getTimeForOneProcess() const;
	void setTimeForOneProcess(long time_for_one_process);
	status getStatus() const;
	void setStatus(status status);
private:
	long ID;
	long stepsToDo;
	long stepsLeft;
	long TimeForOneProcess;
	status status;
};

