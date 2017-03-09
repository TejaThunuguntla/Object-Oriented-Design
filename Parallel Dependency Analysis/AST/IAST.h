///////////////////////////////////////////////////////////////////////
//  IAST.h:		   interface to build AST						     //
//  Language:      Visual C++ 2015, SP1                              //
//  ver 1.0                                                          //
// Application:  Parallel Dependency, CSE687 - Object Oriented Design//
// Author:		  Teja Thunuguntla, Syracuse University				 //
//				  tthunugu@syr.edu									 //
///////////////////////////////////////////////////////////////////////
/*
Module Operations:
==================
* This interface provides functions to build an Abstract Syntax Tree (AST).

Public Interface:
=================
void AddChild(element node) - adds child node to the AST taking scopestack top element as parent
element* Root()				- returns the root of AST
void setRoot(element)		- adds root to the tree
element* findParent(element)- gets the top element of ScopeStack
void setRecent(element node)- changes the current node accordingly with ScopeStack				-

Build Process:
==============
Required files
- ASTNode.h

Build commands:
===============
- devenv project3.sln

Maintenance History:
====================
ver 1.0 : 12 Mar 16
- first release

*/

#include<iostream>
#include "ASTNode.h"

struct IAST
{
	element* root;
	element* recent;
public:
	virtual void AddChild(element node) = 0;
	virtual element* Root() = 0;
	virtual void setRoot(element) = 0;
	virtual element* findParent(element) = 0;
	virtual void setRecent(element node) = 0;
};
