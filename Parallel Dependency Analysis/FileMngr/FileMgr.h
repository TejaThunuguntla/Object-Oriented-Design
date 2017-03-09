#ifndef FILEMGR_H
#define FILEMGR_H

///////////////////////////////////////////////////////////////////////
// FileMngr.h - find files matching specified patterns               //
//             on a specified path                                   //
// ver 1.0                                                           //
// Application:  Parallel Dependency, CSE687 - Object Oriented Design//
// Author:		  Teja Thunuguntla, Syracuse University				 //
// source:      Jim Fawcett, Syracuse University, CST 4-187          //
//              jfawcett@twcny.rr.com                                //
///////////////////////////////////////////////////////////////////////
/*
Module Operations:
==================
* Filemanager takes input through command line arguments.
* Path and multiple patterns are inputs. Returns all files
* and directories which the patterns given.

Build Process:
==============
Required files
- FileSystem.h, FileSystem.cpp

Build commands:
===============
- devenv project3.sln

Maintenance History:
====================
ver 1.0 : 12 Mar 16
- first release

*/

#include "../FileSystem-Windows/FileSystemDemo/FileSystem.h"
#include "../ThreadPool/BlockingQ.h"
#include <iostream>

class FileMgr
{
public:
	FileMgr(const std::string& path, BlockingQueue<std::string>* bQ)
	{
		_blkQ = bQ;
		path_ = path;
		patterns_.push_back("*.*");
	}

	// < ------- add all the patterns to a vector -------- >
	void addPattern(const std::string& patt)
	{
		if (patterns_.size() == 1 && patterns_[0] == "*.*")
			patterns_.pop_back();
		patterns_.push_back(patt);
	}

	void search()
	{
		find(path_);
	}

	// < ---------- find all the files and directories in the given path ----------- >
	void find(const std::string& path)
	{
		std::string fpath = FileSystem::Path::getFullFileSpec(path);

		for (auto patt : patterns_)  
		{
			std::vector<std::string> files = FileSystem::Directory::getFiles(fpath, patt);
			for (auto f : files)
			{
				vFiles.push_back(fpath + "\\" + f);
				_blkQ->enQ(fpath + "\\" + f);
			}
		}
		std::vector<std::string> dirs = FileSystem::Directory::getDirectories(fpath);
		for (auto d : dirs)
		{
			if (d == "." || d == "..")
				continue;
			std::string dpath = fpath + "\\" + d;  // here's the fix
			find(dpath);
		}
	}

	// < --------- returns a files vector ----------- >
	std::vector<std::string> getFiles() 
	{
		return vFiles; 
	}

private:
	std::string path_;
	using patterns = std::vector<std::string>;
	std::vector<std::string> vFiles;
	patterns patterns_;
	BlockingQueue<std::string>* _blkQ;
};

#endif