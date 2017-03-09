/////////////////////////////////////////////////////////////////////
//  MtrExecutive.h:	 tests the FileManager and Parser components   //
//  Language:        Visual C++ 2015, SP1                          //
//  ver 1.0                                                        //
//  Application:     Parser Component				               //
//  Author:		     Teja Thunuguntla, Syracuse University		   //
/////////////////////////////////////////////////////////////////////

#include "MtrExecutive.h"

int main(int argc, char* argv[])
{
	std::vector<std::string>  patterns;
	Test tst;
	if (argc > 1)
	{
		for (int i = 2; i < argc; i++)
			patterns.push_back(argv[i]);
		tst.testFileMgr(argv[1], patterns);
	}
	else
		std::cout << "Wrong path or patterns.! ";
	return 0;
}

// < ------------- tests the FileMngr component---------------- >
void Test::testFileMgr(std::string path, std::vector<std::string> patterns)
{
	DataStore ds;
	FileMgr fm(path, ds);
	std::cout << "Given Path : " + path << "\n \n";
	std::cout << "Given Patterns : \n";
	std::cout << "----------------- \n";
	for (std::string str : patterns)
	{
		std::cout << str << "   ";
		fm.addPattern(str);
	}
	std::cout << "\n\n";
	fm.search();
	std::vector<std::string> files = fm.getFiles();

	std::cout << "Files in the given path : \n";
	std::cout << "----------------------------";
	for (std::string str : files)
		std::cout << "\n" << str;
	std::cout << "\n\n\n\n";
	for (std::string str : files)
		testParser(str);
}

// < ----------- tests the Parser component including AST ------------ >
void Test::testParser(std::string file)
{
	std::string fileSpec = FileSystem::Path::getFullFileSpec(file);
	std::string msg = "Processing file  " + fileSpec;
	std::cout << msg;
	ConfigParseToConsole configure;
	Parser* pParser = configure.Build();
	AST* tree = configure.tree;

	try
	{
		if (pParser)
		{
			if (!configure.Attach(file))
				std::cout << "\n  could not open file " << fileSpec << std::endl;
		}
		else
			std::cout << "\n\n  Parser not built\n\n";

		// now that parser is built, use it

		while (pParser->next())
			pParser->parse();
		Metric metric;

		std::cout << "\n\n" << "Tree Walk  :";
		std::cout << "\n" << "------------";
		metric.print(tree->Root());
		std::cout << "\n\n" << "Metric Analysis  : ";
		std::cout << "\n" << "-------------------" << "\n";
		std::cout << "\tName\t\t" << "Start Line\t" << "End Line\t" << "LineCount\t" << "Complexity\t";
		std::cout << "\n\t----------------------------------------------------------------------------";
		metric.preOrderTraversal(tree->Root());

		std::cout << "\n\n\n";
	}
	catch (std::exception& ex)
	{
		std::cout << "\n\n    " << ex.what() << "\n\n";
	}

	std::cout << "\n";
}
