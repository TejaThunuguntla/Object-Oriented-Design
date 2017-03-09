/////////////////////////////////////////////////////////////////////
//  TestFile2.h -    test file					                   //
//  ver 1.0														   //
//  Language:        Visual C++ 2008, SP1                          //
//  Application:     Parser Component				               //
//  Author:		     Teja Thunuguntla, Syracuse University		   //
/////////////////////////////////////////////////////////////////////

namespace TestN
{
	class TestC
	{
		void testFunc1()
		{
			try
			{
				while (1)
				{
					return;
				}
			}
			catch (int e) {
				throw e;
			}
		}
	};
}
#ifdef TEST2

int main()
{
	return 0;
}
#endif // TEST2
