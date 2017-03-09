#ifndef ASTNODE_H
#define ASTNODE_H

///////////////////////////////////////////////////////////////////////
//  ASTNode.h:	   structure of node to build AST  				     //
//  Language:      Visual C++ 2015, SP1                              //
//  ver 1.0                                                          //
// Application:  Parallel Dependency, CSE687 - Object Oriented Design//
// Author:		  Teja Thunuguntla, Syracuse University				 //
//				  tthunugu@syr.edu									 //
///////////////////////////////////////////////////////////////////////
/*
Module Operations:
==================
* This module provides the structure of node to build 
* an Abstract Syntax Tree (AST).

Build Process:
==============
Required files
- ScopeStack.h

Build commands:
===============
- devenv project3.sln

Maintenance History:
====================
ver 1.0 : 12 Mar 16
- first release

*/

#include <vector>
#include <queue>
#include <string>
#include <sstream>
#include "../ScopeStack/ScopeStack.h"

struct element
{
//public:
	element* parent;
	std::vector<element*> child;
	std::string type;
	std::string name;
	size_t lineCount;
	size_t startline;
	size_t endline;
	size_t complexity;

	element()
	{
		startline = 0;
		endline = 0;
		lineCount = 0;
		complexity = 1;
		parent = NULL;
	}
};

#endif