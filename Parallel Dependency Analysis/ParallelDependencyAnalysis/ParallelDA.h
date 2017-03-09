#ifndef PARALLELDA_H
#define PARALLELDA_H

#pragma warning(disable : 4503)

///////////////////////////////////////////////////////////////////////
// ParallelDA.h - runs dependency analysis asynchronously			 //
///////////////////////////////////////////////////////////////////////																	 //
// ver 1.0															 //
// Application:  Parallel Dependency, CSE687 - Object Oriented Design//
// Author:		  Teja Thunuguntla, Syracuse University				 //
//				  tthunugu@syr.edu									 //
///////////////////////////////////////////////////////////////////////
/*
Module Operations:
==================
* provides callable objects to run the dependency analysis
* asynchronously using thread pool. 

Public Interface:
=================
* getLamda() - provides lamdas and enqueues work item 
* trimPath() - trim path to file name
* end()		 - adds end condition for file manager

Build Process:
==============
Required files
- ThreadPool.h, Tokenizer.h, Tokenizer.cpp, TypeTable.h
- FileMgr.h, DependencyExec.h, DependencyExec.cpp

Build commands:
===============
- devenv project3.sln

Maintenance History:
====================
ver 1.0 : 06 Apr 16
- first release

*/

#include "../ThreadPool/ThreadPool.h"
#include "../Tokenizer/Tokenizer.h"
#include "../DependencyAnalysis/DependencyExec.h"
#include "../Parser/TypeTable.h"
#include "../FileMngr/FileMgr.h"

class ParallelDA
{
public:
	ParallelDA(ProcessWorkItem<std::string>* tp, TypeTable* tt)
	{
		_ThreadPool = tp;
		MergedTypeTbl = tt;
		_blkQ1 = new BlockingQueue<std::string>();
	}

// ------------< provides lamdas and enqueues work item >--------------
	void getLamda(std::string* _path, std::vector<std::string> _patterns)
	{
		std::string file1;

		WorkItem<std::string> fileMgr = [&]()
		{
			FileMgr fm(*_path, _blkQ1);
			for (auto pat : _patterns)
				fm.addPattern(pat);
			fm.search();
			end();
			return "";
		};

		WorkItem<std::string> doDependency = [&]()
		{
			//std::string fl = file1;
			Dependency(file1);
			return "";
		};

		WorkItem<std::string> mergeMap = [&]()
		{
			MergeMap();
			return "";
		};

		_ThreadPool->doWork(&fileMgr);

		while (true)
		{
			if (_blkQ1 != NULL && _blkQ1->size() > 0)
			{
				std::string top = _blkQ1->deQ();
				if (top.compare("EndofFM") == 0)
				{
					_ThreadPool->doWork(&mergeMap);
					std::this_thread::sleep_for(std::chrono::milliseconds(400));
					_ThreadPool->doWork(nullptr);
					break;
				}
				else
				{
					file1 = top;
					_ThreadPool->doWork(&doDependency);
					std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				}
			}
		}
		_ThreadPool->wait();
	}

//------------< trim path to file name >--------------
	std::string trimPath(std::string path)
	{
		const size_t last = path.find_last_of("\\/");
		if (std::string::npos != last)
		{
			path.erase(0, last + 1);
		}
		return path;
	}

	void end(){ _blkQ1->enQ("EndofFM"); }
private:
	ProcessWorkItem<std::string>* _ThreadPool;
	TypeTable* MergedTypeTbl;
	BlockingQueue<std::string>* _blkQ1;
	std::vector<std::unordered_map<std::string, std::vector<std::string>>> vectorDep;
	std::unordered_map<std::string, std::vector<std::string>> mergedMap;

	void MergeMap()
	{
		std::cout << "\n\n" << "Dependency Output..." << "\n";
		std::cout << "=======================" << "\n";
		for (auto map : vectorDep)
		{
			mergedMap.insert(map.begin(), map.end());
		}
		for (auto map : mergedMap) {
			std::cout << map.first << " is dependant on ";
			for (auto vec : map.second)
				std::cout << "\t" << vec;
			std::cout << "\n\n";
		}
	}

	void Dependency(std::string _file)
	{
		Toker tok;
		std::fstream in(_file);

		if (!in.good())
			std::cout << "\n  can't open file " << _file << "\n\n";

		tok.attach(&in);

		DependencyAnalysis dep(&tok, MergedTypeTbl, trimPath(_file));
		std::unordered_map<std::string, std::vector<std::string>>* temp;
		temp = dep.dependency();
		vectorDep.push_back(*temp);
	}
};

#endif