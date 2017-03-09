#include "Task.h"

///////////////////////////////////////////////////////////////////////
// Task.cpp-provides callable obj to run Type analysis asynchronously//
///////////////////////////////////////////////////////////////////////
// ver 1.0															 //
// Application:  Parallel Dependency, CSE687 - Object Oriented Design//
// Author:		  Teja Thunuguntla, Syracuse University				 //
//				  tthunugu@syr.edu									 //
///////////////////////////////////////////////////////////////////////

Task::Task(std::string path,std::vector<std::string> patterns)
{
	_patterns = patterns;
	_path = path;
	_blkQ = new BlockingQueue<std::string>();
	_ThreadPool = new ProcessWorkItem<std::string>(4);
	getwork();
} 

// ------------< provides lamdas and enqueues work item >--------------------
void Task::getwork()
{
	std::string file;
	_ThreadPool->start();
	
	WorkItem<std::string> fileSearch = [&]()
	{
		SearchFile();
		return "";
	};

	WorkItem<std::string> parseFile = [&]()
	{
		ParseFile(file);
		return "";
	};

	WorkItem<std::string> mergeTables = [&]()
	{
		MergeTables();
		return "";
	};

	_ThreadPool->doWork(&fileSearch);

	while (true)
	{
		if (_blkQ != NULL && _blkQ->size() > 0)
		{
			std::string top = _blkQ->deQ();

			if (top.compare("EndofFM") == 0)
			{
				_ThreadPool->doWork(&mergeTables);
				std::this_thread::sleep_for(std::chrono::milliseconds(400));
				ParallelDependency();
				break;
			}
			else
			{
				file = top;
				_ThreadPool->doWork(&parseFile);
				std::this_thread::sleep_for(std::chrono::milliseconds(400));
			}
		}		
	}
	//_ThreadPool->wait();
}

//-----------------< Merge type tables >-------------------
void Task::MergeTables()
{
	for (auto tbl : TypeTables)
		MergedTypeTbl.merge(tbl->get());

	std::cout << "\n" << "Merged Type Table :" << "\t" << "thread ID : " << std::this_thread::get_id() << "\n";
	std::cout << "====================";
	MergedTypeTbl.showTypeTable();
	std::cout << "\n";
}

//-------------< search for files using file manager which match the path and patterns >----------------
void Task::SearchFile()
{
	std::cout << "File Manager :" << "\t" << "thread ID : " << std::this_thread::get_id() << "\n";
	std::cout << "=============" << "\n \n";
	FileMgr fm(_path, _blkQ);
	for (auto pat : _patterns)
		fm.addPattern(pat);
	fm.search();
	end();
}

//---------------< run parser on the file and push type tables to a vector >----------------
void Task::ParseFile(std::string file)
{
	ConfigParseToConsole configure(trimPath(file));
	Parser* pParser = configure.Build();

	if (pParser)
	{
		if (!configure.Attach(file))
			std::cout << "\n  could not open file " << file << std::endl;
	}

	while (pParser->next())
		pParser->parse();

	TypeTable *tbl = configure.getTypeTable();
	TypeTables.push_back(tbl);

	std::cout << "thread ID : " << std::this_thread::get_id() << "\t" << file << "\n";
}

//------------< trim path to file name >--------------
std::string Task::trimPath(std::string fullpath)
{
	const size_t last = fullpath.find_last_of("\\/");
	if (std::string::npos != last)
	{
		fullpath.erase(0, last + 1);
	}
	return fullpath;
}

//------------< run parallel dependency >--------------
void Task::ParallelDependency()
{
	ParallelDA PDA(_ThreadPool,&MergedTypeTbl);
	PDA.getLamda(&_path,_patterns);
}

#ifdef TEST_TASK

void main()
{
	std::string path = "E:\Teja\Syracuse University\OOD\Project1";
	std::vector<std::string> pattrns;

	pattrns.push_back("*.h");
	pattrns.push_back("*.cpp");

	Task tsk(path, pattrns);
}

#endif