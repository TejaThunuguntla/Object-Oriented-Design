#ifndef AST_H
#define AST_H

/////////////////////////////////////////////////////////////////////
//  AST.h:		  provides functions to build AST  				   //
//  Language:     Visual C++ 2015, SP1                             //
//  ver 1.0                                                        //
// Application:   Parser component, CSE687 - Object Oriented Design//
//  Author:		  Teja Thunuguntla, Syracuse University		       //
/////////////////////////////////////////////////////////////////////
/*
Module Operations:
==================
* This module provides functions to build an Abstract Syntax Tree (AST)
* using the AST node and ScopeStack.

Build Process:
==============
Required files
- ASTNode.h, IAST.h, ScopeStack.h

Build commands: 
===============
- devenv project2.sln

Maintenance History:
====================
ver 1.0 : 12 Mar 16
- first release

*/

#include<iostream>
#include "ASTNode.h"
#include "IAST.h"

class AST : public IAST
{
	element* root;
	element* recent;
public:
	ScopeStack<element>* scopeStack;
	AST(ScopeStack<element>* scopeStack);
	void AddChild(element node);
	element* Root();
	void setRoot(element);
	element* findParent(element);
	void setRecent(element node);
};

#endif