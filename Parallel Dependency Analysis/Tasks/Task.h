#ifndef TASK_H
#define TASK_H

#pragma warning(disable : 4503)

///////////////////////////////////////////////////////////////////////
// Task.h - provides callable obj to run Type analysis asynchronously//
///////////////////////////////////////////////////////////////////////																	 //
// ver 1.0															 //
// Application:  Parallel Dependency, CSE687 - Object Oriented Design//
// Author:		  Teja Thunuguntla, Syracuse University				 //
//				  tthunugu@syr.edu									 //
///////////////////////////////////////////////////////////////////////
/*
Module Operations:
==================
* creates 'n' threads and provides callable objects to run Type Analysis
* asynchronously. Provides methods to print them.

Public Interface:
=================
* getwork()		- provides lamdas and enqueues work item 
* end()			- adds end condition for file manager
* ParallelDependency()- run parallel dependency
* MergeTables() - Merge type tables
* SearchFile()  - search for files using file manager which match the path and patterns
* ParseFile()   - run parser on the file and push type tables to a vector

Build Process:
==============
Required files
- BlockingQ.h, ThreadPool.h, ConfigureParser.h, ConfigureParser.cpp
- TypeTable.h, FileMgr.h, DependencyExec.h, DependencyExec.cpp
- ParallelDA.h

Build commands:
===============
- devenv project3.sln

Maintenance History:
====================
ver 1.0 : 06 Apr 16
- first release

*/

#include "../ThreadPool/BlockingQ.h"
#include "../ThreadPool/ThreadPool.h"
#include "../Parser/ConfigureParser.h"
#include "../Parser/TypeTable.h"
#include "../FileMngr/FileMgr.h"
#include "../ParallelDependencyAnalysis/ParallelDA.h"
#include "../DependencyAnalysis/DependencyExec.h"
#include <vector>
#include <unordered_map>

class Task
{
public:
	Task(std::string , std::vector<std::string> );
	void getwork();
	void end() { _blkQ->enQ("EndofFM"); }
	void ParallelDependency();
	void MergeTables();
	void SearchFile();
	void ParseFile(std::string file);
private:
	BlockingQueue<std::string>* _blkQ;	
	std::vector<std::string> _patterns;
	std::string _path;
	std::vector<TypeTable*> TypeTables;
	TypeTable MergedTypeTbl;
	std::string trimPath(std::string fullpath);
	ProcessWorkItem<std::string>* _ThreadPool;
};

#endif // !TASK_H