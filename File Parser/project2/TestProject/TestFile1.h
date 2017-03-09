/////////////////////////////////////////////////////////////////////
//  TestFile1.h -    test file					                   //
//  ver 1.0														   //
//  Language:        Visual C++ 2008, SP1                          //
//  Application:     Parser Component				               //
//  Author:		     Teja Thunuguntla, Syracuse University		   //
/////////////////////////////////////////////////////////////////////
/*
Module Operations:
==================
Test File - 1

Build commands:
===============
- devenv project2.sln

Maintenance History:
====================
ver 1.0 : 12 Mar 16
- first release

*/

namespace Scanner 
{
	class test
	{
		bool addRule(char pRule);

		bool next()
		{
			bool succeeded = addRule('a');
			if (!succeeded) {
				return false;
			}

			return true;
		}
	};
}

	namespace Utilities
	{
		class Parser
		{
			void Parser::addRule(char pRule)
			{
				int a;
				enum testEnum {a,b,c};
			}

			bool Parser::next();
		};
	}


