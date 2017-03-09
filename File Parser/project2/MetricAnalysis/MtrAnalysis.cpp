
/////////////////////////////////////////////////////////////////////
//  MtrAnalysis.h:	 calculate and display metric analysis, AST	   //
//  Language:        Visual C++ 2015, SP1                          //
//  ver 1.0                                                        //
//  Application:     Parser Component				               //
//  Author:		     Teja Thunuguntla, Syracuse University		   //
/////////////////////////////////////////////////////////////////////

#include "MtrAnalysis.h"

// < --------- Prints the AST on to the console ---------- >
void Metric::print(element* elem)
{
	static size_t indentLevel = 0;
	std::cout << "\n  " << std::string(5 * indentLevel, ' ') << " ( " + elem->name + " , " + elem->type + " )";
	auto iter = elem->child.begin();
	++indentLevel;
	while (iter != elem->child.end())
	{
		print(*iter);
		++iter;
	}
	--indentLevel;
}	

// < ----------- Prints all the functions in the AST and their metric analysis ----------- >
void Metric::preOrderTraversal(element* root)
{
	if (root == NULL)
	{
		return;
	}
	else
	{
		if (root->type == "function")
		{
			std::cout << "\n" << std::setw(15) << root->name << std::setw(15) << root->startline << std::setw(15) << root->endline << std::setw(15) << root->lineCount << std::setw(15) << root->complexity;
		}

		for (int i = 0; i < root->child.size(); i++)
			preOrderTraversal(root->child.at(i));

		return;
	}
}