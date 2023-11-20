#include "Queue.h"

Queue::Queue()
{
	InitializeCriticalSection(&crit_section);
}

Queue::MyTask::MyTask()
{
}

Queue::MyTask::MyTask(Func task, LPVOID lp)
{
	this->function = task;
	this->lpParam = lp;
}

void Queue::addTask(Func task, LPVOID lp)
{
	EnterCriticalSection(&crit_section);
	try {
		tasks->push(MyTask(task, lp));
	}
	catch (...) {
		LeaveCriticalSection(&crit_section);
		throw;
	}
	LeaveCriticalSection(&crit_section);
}

vector<HANDLE> Queue::process_queue(ThreadPool pool)
{
	EnterCriticalSection(&crit_section);
	try {
		pool.clear_pool();
		int th_num = 0;
		int size = pool.size;
		while (!tasks->empty())
		{
			MyTask task = tasks->front();
			tasks->pop();
			pool.pool[th_num].functions->push_back(task.function);
			pool.pool[th_num].lpParams->push_back(task.lpParam);
			th_num = th_num == size - 1 ? 0 : ++th_num;
		}
	}
	catch (...) {
		LeaveCriticalSection(&crit_section);
		throw;
	}
	LeaveCriticalSection(&crit_section);
	return pool.execute();
}
