#pragma once

#include <windows.h>
#include <vector>
#include <stdexcept>

#define STANDART_SIZE 10;

using namespace std;

class ThreadPool
{
private:
	typedef void (*Func)(LPVOID);
	struct MyThread
	{
		vector<Func>* functions = new vector<Func>();
		vector<LPVOID>* lpParams = new vector<LPVOID>();
		HANDLE processHandle = NULL;
		public:
			MyThread();
			MyThread(vector<Func>* f, vector<LPVOID>* lps, HANDLE h);
	};
	vector<MyThread> pool;
	vector<HANDLE> execute();
	void init();
public:
	typedef void (*Func)(LPVOID);
	int size;
	ThreadPool();
	void clear_pool();
	ThreadPool(int s);
	friend class Queue;
	friend DWORD WINAPI MyThreadProc(LPVOID lpParam);
};
