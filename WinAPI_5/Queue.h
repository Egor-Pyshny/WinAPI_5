#pragma once

#include <windows.h>
#include <queue>
#include <vector>
#include "ThreadPool.h"

using namespace std;

class Queue
{
private:
	typedef void (*Func)(LPVOID);
	struct MyTask
	{
		Func function;
		LPVOID lpParam;
		public:
			MyTask();
			MyTask(Func f, LPVOID lp);
	};
	queue<MyTask>* tasks = new queue<MyTask>();
	CRITICAL_SECTION crit_section;
public:
	Queue();
	void addTask(Func task, LPVOID lp);
	vector<HANDLE> process_queue(ThreadPool pool);
};

