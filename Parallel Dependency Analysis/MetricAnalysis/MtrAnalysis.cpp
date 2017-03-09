
///////////////////////////////////////////////////////////////////////
//  MtrAnalysis.h:	 calculate and display metric analysis, AST	     //
//  Language:        Visual C++ 2015, SP1                            //
//  ver 1.0                                                          //
// Application:  Parallel Dependency, CSE687 - Object Oriented Design//
// Author:		  Teja Thunuguntla, Syracuse University				 //
//				  tthunugu@syr.edu									 //
///////////////////////////////////////////////////////////////////////

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

		for (size_t i = 0; i < root->child.size(); i++)
			preOrderTraversal(root->child.at(i));

		return;
	}
}

#ifdef TEST_MTR

void main()
{
	ScopeStack<element> stack;
	AST* tree = new AST(&stack);

	element elem;
	elem.name = "element1";
	elem.type = "struct";
	elem.startline = 12;
	elem.endline = 23;
	tree->setRoot(elem);
	tree->AddChild(elem);

	element elem2;
	elem2.name = "element2";
	elem2.type = "function";
	elem2.startline = 25;
	elem2.endline = 30;
	tree->setRecent(elem2);
	tree->AddChild(elem2);

	Metric mtr;
	mtr.preOrderTraversal(&elem);
	mtr.print(&elem);
}

#endif