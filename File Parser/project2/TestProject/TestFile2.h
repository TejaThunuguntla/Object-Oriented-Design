/////////////////////////////////////////////////////////////////////
//  TestFile2.h -    test file					                   //
//  ver 1.0														   //
//  Language:        Visual C++ 2008, SP1                          //
//  Application:     Parser Component				               //
//  Author:		     Teja Thunuguntla, Syracuse University		   //
/////////////////////////////////////////////////////////////////////
/*
Module Operations:
==================
Test File - 2

Build commands:
===============
- devenv project2.sln

Maintenance History:
====================
ver 1.0 : 12 Mar 16
- first release

*/

#include <iostream>
#include <typeinfo>
#include <exception>

namespace TestN
{
	class TestC
	{
		void testFunc1();
		void testFunc2();
	};

	struct testStruct
	{
		int it;
		void Func();
	};
}