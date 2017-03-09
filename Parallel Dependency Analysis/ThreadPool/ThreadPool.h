#ifndef THREADPOOL_H
#define THREADPOOL_H

///////////////////////////////////////////////////////////////////////
// ThreadPool.h - creates threads which processes enqueued workitems //
///////////////////////////////////////////////////////////////////////	
// ver 1.0															 //
// Application:  Parallel Dependency, CSE687 - Object Oriented Design//
// Author:		  Teja Thunuguntla, Syracuse University				 //
// Source:		  Jim Fawcett, Syracuse University, CST 4-187		 //
//                jfawcett@twcny.rr.com								 //
///////////////////////////////////////////////////////////////////////
/*
Module Operations:
==================
* creates 'n' threads and processes the queued work items  
* execute them asynchronously. Each work item will be a 
* callable object that is supplied by application code.

Public Interface:
=================
* start()	- start child thread that dequeus work items
* doWork()	- enqueue work item
* result()	- retrieve results with blocking call
* wait()	- wait for child thread to terminate

Build Process:
==============
Required files
- BlockingQ.h

Build commands:
===============
- devenv project3.sln

Maintenance History:
====================
ver 1.0 : 06 Apr 16
- first release

*/

#include <thread>
#include <functional>
#include <mutex>
#include "BlockingQ.h"

template<typename Result>
using WorkItem = std::function<Result()>;

///////////////////////////////////////////////////////////////////////
// class to process work items

template<typename Result>
class ProcessWorkItem
{
public:
	void start();
	void doWork(WorkItem<Result>* pWi);
	Result result();
	void wait();
	ProcessWorkItem(int n);
	~ProcessWorkItem();
private:
	std::vector<std::thread*> _pThread;
	BlockingQueue<WorkItem<Result>*> _workItemQueue;
	BlockingQueue<Result> _resultsQueue;
	std::mutex mtx;
	int num;
};

template<typename Result>
ProcessWorkItem<Result>::ProcessWorkItem(int n)
{ 
	num = n;
}

template<typename Result>
BlockingQueue<WorkItem<Result>*> getQ()
{
	return _workItemQueue;
}
//----< wait for child thread to terminate >---------------------------

template<typename Result>
void ProcessWorkItem<Result>::wait()
{
	for (auto thr : _pThread)
		thr->join();
}
//----< enqueue work item >--------------------------------------------

template<typename Result>
void ProcessWorkItem<Result>::doWork(WorkItem<Result>* pWi)
{
	_workItemQueue.enQ(pWi);
}
//----< retrieve results with blocking call >--------------------------

template<typename Result>
Result ProcessWorkItem<Result>::result()
{
	return _resultsQueue.deQ();
}
//----< start child thread that dequeus work items >-------------------

template<typename Result>
void ProcessWorkItem<Result>::start()
{
	std::function<void()> threadProc =
		[&]() {
		while (true)
		{
			WorkItem<Result>* pWi = _workItemQueue.deQ();

			if (pWi == nullptr)
			{
				std::cout << "\n" << "Shutting down thread " << std::this_thread::get_id();
				_workItemQueue.enQ(nullptr);
				return;
			}
			Result result = (*pWi)();
			_resultsQueue.enQ(result);
		}
	};
	for (int i = 0; i < num; i++) {
		_pThread.push_back(new std::thread(threadProc));
	}
}
//----< clean up heap >------------------------------------------------

template<typename Result>
ProcessWorkItem<Result>::~ProcessWorkItem()
{
	for (auto thr : _pThread)
		delete thr;
}

#endif