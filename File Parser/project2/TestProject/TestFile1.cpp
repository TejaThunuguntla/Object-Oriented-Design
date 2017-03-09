/////////////////////////////////////////////////////////////////////
//  TestFile1.h -    test file					                   //
//  ver 1.0														   //
//  Language:        Visual C++ 2008, SP1                          //
//  Application:     Parser Component				               //
//  Author:		     Teja Thunuguntla, Syracuse University		   //
/////////////////////////////////////////////////////////////////////

namespace Scanner 
{
	class test
	{
		bool addRule(char pRule)
		{
			return true;
		}

		bool next()
		{
			bool succeeded = addRule('a');
			if (!succeeded) {
				for (int i = 0; i <10 ; i++)
				{
					continue;
				}
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
			return;
		}

		bool Parser::TestFunc()
		{
			addRule('a');
			if (1)
			{
				return false;
			}
			else
			{
				return true;
			}
			return true;
		}

		void testFunc2()
		{
			return;
		}
	};
}

int main()
{
	return 0;
}




