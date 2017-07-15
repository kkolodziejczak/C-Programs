#include "stdafx.h"
#include "History.h"

std::vector<std::string> History::getQueueHistory()
{
	return QueueHistory;
}

void History::set_queue_history(const std::vector<std::string>& basic_strings)
{
	QueueHistory = basic_strings;
}

void History::addToHistory(std::string a)
{
	QueueHistory.push_back(a);
}

void History::addToHistory(char a)
{
	std::string ab;
	ab += a;
	QueueHistory.push_back(ab);
}

void History::addToHistory(int n, char a)
{
	QueueHistory[n] += a;
}

void History::printHistory()
{
	for (int i = 0; i < QueueHistory.size(); i++)
		std::cout <<i <<": "<<QueueHistory[i]<<"\n";
}

long History::numbers_of_cycles() const
{
	return numbersOfCycles;
}

void History::set_numbers_of_cycles(long numbers_of_cycles)
{
	numbersOfCycles = numbers_of_cycles;
}
