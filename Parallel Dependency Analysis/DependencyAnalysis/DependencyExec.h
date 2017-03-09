#ifndef DEPANAL_H
#define DEPANAL_H

#pragma warning(disable : 4503)

///////////////////////////////////////////////////////////////////////
// DependencyExec.h - checks for dependency on files		         //
///////////////////////////////////////////////////////////////////////
// ver 1.0															 //
// Application:  Parallel Dependency, CSE687 - Object Oriented Design//
// Author:		  Teja Thunuguntla, Syracuse University				 //
//				  tthunugu@syr.edu									 //
///////////////////////////////////////////////////////////////////////
/*
Module Operations:
==================
* Tokenizes the given file and matches the tokens 
* and its namespace with type table.

Public Interface:
=================
* getToke()		- returns a token using tokenizer
* compare()		- matches token with the type table
* dependency()	- end conditions for tokenizing the file
* showDependency()- prints the dependencies to console

Build Process:
==============
Required files
- Tokenizer.h, Tokenizer.cpp, TypeTable.h

Build commands:
===============
- devenv project3.sln

Maintenance History:
====================
ver 1.0 : 06 Apr 16
- first release

*/

#include <vector>
#include <unordered_map>
#include "../Tokenizer/Tokenizer.h"
#include "../Parser/TypeTable.h"

using namespace Scanner;

class DependencyAnalysis 
{
public:
	DependencyAnalysis(Toker* pToker,TypeTable* Ttbl, std::string file);
	DependencyAnalysis(const DependencyAnalysis&) = delete;
	DependencyAnalysis& operator=(const DependencyAnalysis&) = delete;
	std::string getToke();
	void compare(std::string tok);
	std::unordered_map<std::string, std::vector<std::string>>* dependency();
	void showDependency();
private:
	std::vector<std::string> _tokens;
	Toker* _pToker;
	TypeTable* _typeTbl;
	std::unordered_map<std::string, std::unordered_map<std::string, std::vector<std::string>>> mergedTbl;
	std::vector<std::string> _namespace;
	std::unordered_map<std::string, std::vector<std::string>>* mapDepend;
	std::string _file;
};

#endif