#include "stdafx.h"
#include "Process.h"
#include "Manager.h"

long Manager::getlastID() const
{
	return lastAddedID;
}
void Manager::setLastID(long last_id)
{
	lastAddedID = last_id;
}
std::vector<Process*> Manager::getQueue() const
{
	return Queue;
}
void Manager::pushToQueue(Process* tmp)
{
	this->setLastID(tmp->getID());
	this->Queue.push_back(tmp);
}
