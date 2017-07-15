#include "stdafx.h"
#include "Process.h"



Process::Process()
{
}
Process::~Process()
{
}
void Process::subStepsLeft()
{
	stepsLeft--;
	if (stepsLeft >= 0)
		status = W;
	else
		status = Z;
}

#pragma region Get/Set
long Process::getID() const
{
	return ID;
}
void Process::setID(long id)
{
	ID = id;
}
long Process::getStepsToDo() const
{
	return stepsToDo;
}
void Process::setStepsToDo(long steps_to_do)
{
	stepsToDo = steps_to_do;
}
long Process::getStepsLeft() const
{
	return stepsLeft;
}
void Process::setStepsLeft(long steps_left)
{
	stepsLeft = steps_left;
}
long Process::getTimeForOneProcess() const
{
	return TimeForOneProcess;
}
void Process::setTimeForOneProcess(long time_for_one_process)
{
	TimeForOneProcess = time_for_one_process;
}
status Process::getStatus() const
{
	return status;
}
void Process::setStatus(::status status)
{
	this->status = status;
}
#pragma endregion 