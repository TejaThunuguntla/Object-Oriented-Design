///////////////////////////////////////////////////////////////////////
// ThreadPool.h - creates threads which processes enqueued workitems //
///////////////////////////////////////////////////////////////////////																	 //
// ver 1.0															 //
// Application:  Parallel Dependency, CSE687 - Object Oriented Design//
// Author:		  Teja Thunuguntla, Syracuse University				 //
// Author:		  Jim Fawcett, Syracuse University, CST 4-187		 //
//                jfawcett@twcny.rr.com								 //
///////////////////////////////////////////////////////////////////////

#include <string>
#include <iostream>
#include <conio.h>
#include "ThreadPool.h"

//----< demonstrate ProcessWorkItem class >----------------------------

using WorkResult = std::string;

#ifdef TEST_THREAD

int main()
{
	std::cout << "Enqueued Work Items";

	std::cout << "\n  main thread id = " << std::this_thread::get_id();

	ProcessWorkItem<WorkResult> processor(2);
	processor.start();

	// define 1st work item

	WorkItem<WorkResult> wi1 = []() {
		std::cout << "\n  working on thread " << std::this_thread::get_id();
		return "Hello from wi1";
	};

	processor.doWork(&wi1);

	WorkItem<WorkResult> wi3 = []() {
		std::cout << "\n  working on thread " << std::this_thread::get_id();
		return "Hello from wi3";
	};
	processor.doWork(&wi3);
	// define 2nd work item

	WorkItem<WorkResult> wi2 = []()
	{
		std::cout << "\n  working on thread " << std::this_thread::get_id();
		size_t sum = 0;
		for (size_t i = 0; i < 100000; ++i)
			sum += i;
		return "wi2 result = "; // +sum;
	};

	processor.doWork(&wi2);

	// the following calls to result() block until results are enqueued

	std::cout << "\n  " << processor.result();
	std::cout << "\n  " << processor.result();
	std::cout << "\n  " << processor.result();
	
	for (int i = 0; i < 2; i++)
		processor.doWork(nullptr);

	// wait for child thread to complete

	processor.wait();
	std::cout << "\n\n";
}

#endif // !TEST_THREAD