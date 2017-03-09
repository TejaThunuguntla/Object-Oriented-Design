#ifndef MTRANAL_H
#define MTRANAL_H

/////////////////////////////////////////////////////////////////////
//  MtrAnalysis.h:	 calculate and display metric analysis, AST	   //
//  Language:        Visual C++ 2015, SP1                          //
//  ver 1.0                                                        //
//  Application:     Parser Component				               //
//  Author:		     Teja Thunuguntla, Syracuse University		   //
/////////////////////////////////////////////////////////////////////
/*
Module Operations:
==================
* This module provides functions to display Abstract Syntax Tree (AST)
* and metric analysis (num of lines and complexity) of the functions 
* in it on the console.

Public Interface:
=================
void print(element* elem) -			   Displays the AST on to the console
void preOrderTraversal(element* elem)- Display the metric analysis of functions in AST

Build Process:
==============
Required files
- AST.h, AST.cpp

Build commands:
===============
- devenv project2.sln

Maintenance History:
====================
ver 1.0 : 12 Mar 16
- first release

*/

#include<iomanip>
#include "../AST/AST.h"

class Metric
{
public:
	void print(element* elem);
	void preOrderTraversal(element* elem);
};

#endif 
