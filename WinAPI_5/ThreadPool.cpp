#include "ThreadPool.h"
#include "Queue.h"
#include <iostream>

void ThreadPool::clear_pool()
{
	bool ex=false;
	for (int i = 0; i < this->size; i++) {
		try {
			MyThread th = this->pool[i];
			th.functions->clear();
			th.lpParams->clear();
			CloseHandle(th.processHandle);
			th.processHandle = NULL;
		}
		catch (...) {
			ex = true;
			MyThread th = this->pool[i];
			CloseHandle(th.processHandle);
		}
	}
	if (ex) { 
		throw runtime_error(""); 
	}
}

DWORD WINAPI MyThreadProc(LPVOID lpParam)
{
	ThreadPool::MyThread* th = (ThreadPool::MyThread*)(lpParam);
	DWORD tid = GetThreadId(th->processHandle);
	cout << "Thread start " << tid << endl;
	for (int i = 0; i < th->functions->size(); i++) {
		(th->functions->at(i))(th->lpParams->at(i));
	}
	cout << "Thread end " << tid << endl;
	return 0;
}

vector<HANDLE> ThreadPool::execute()
{
	vector<HANDLE> res;
	for (int i = 0; i < this->size; i++) {
		
		LPVOID a = &pool.at(i);
		//cout << "POOL" << i << "ADDRESS  " << a << endl;
		HANDLE h = CreateThread(
			NULL,
			0,
			MyThreadProc,
			a,
			0,
			NULL
		);
		pool[i].processHandle = h;
		Sleep(1);
		res.push_back(h);
	}
	return res;
}

void ThreadPool::init()
{
	for (int i = 0; i < this->size; i++) {
		this->pool.push_back(ThreadPool::MyThread());
	}
}

ThreadPool::ThreadPool()
{
	this->size = STANDART_SIZE;
	this->init();
}


ThreadPool::ThreadPool(int s)
{
	this->size = s;
	this->init();
}

ThreadPool::MyThread::MyThread()
{
}

ThreadPool::MyThread::MyThread(vector<Func>* f, vector<LPVOID>* lps, HANDLE h)
{
	this->functions = f;
	this->lpParams = lps;
	this->processHandle = h;
}
