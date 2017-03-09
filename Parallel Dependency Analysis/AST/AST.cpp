#include "AST.h"

///////////////////////////////////////////////////////////////////////
//  AST.cpp:	  provides functions to build AST  				     //
//  Language:     Visual C++ 2015, SP1                               //
//  ver 1.0                                                          //
// Application:  Parallel Dependency, CSE687 - Object Oriented Design//
// Author:		  Teja Thunuguntla, Syracuse University				 //
//				  tthunugu@syr.edu									 //
///////////////////////////////////////////////////////////////////////

// < ------- adds child node to the AST taking scopestack top element as parent --------- >
void AST::AddChild(element node1)
{
	element* node = new element();
	node->name = node1.name;
	node->type = node1.type;
	node->lineCount = node1.lineCount;
	node->startline = (node1.lineCount - 1);

	if (root == NULL)
	{
		root = node;
		recent = node;
		return;
	}

	element* parent1 = recent;
	
	if (parent1 != NULL)
	{
		if (node->type == "SplBlock")
			node->complexity = 1;

		parent1->child.push_back(node);
		node->parent = parent1;
		recent = node;
	}
	return;
}

// < ----------- gets the top element of ScopeStack -------------- >
element* AST::findParent(element elem)
{
	if (recent != NULL)
	{
		std::string name = elem.name;
		std::string type = elem.type;

		while (true)
		{
			if (recent == NULL)
				return root;
			else if (name == recent->name && type == recent->type)
				return recent;
			else
				recent = recent->parent;
		}
		return NULL;
	}
	return NULL;
}

AST::AST(ScopeStack<element>* scopeStack1)
{
	scopeStack = scopeStack1;
	root = NULL;
	recent = NULL;
}

// < ---------------- returns the root of AST -------------------- >
element* AST::Root()
{
	return root;
}

// < --------------- adds root to begin building the tree -------------------- >
void AST::setRoot(element node1)
{
	element* node = new element();
	node->name = node1.name;
	node->type = node1.type;
	node->lineCount = node1.lineCount;
	node->startline = node1.lineCount;
	root = node;
	recent = root;
	return;
}

// < ----------- changes the current node accordingly with ScopeStack ------------- >
void AST::setRecent(element node)
{
	if (recent != NULL && recent->parent != NULL)
	{
		recent->endline = node.endline;
		recent->lineCount = recent->endline - recent->startline + 1;
		(recent->parent)->complexity = (recent->parent)->complexity + recent->complexity;
		recent = recent->parent;
	}
}

#ifdef TEST_AST

void main()
{
	ScopeStack<element> stack;
	AST* tree = new AST(&stack);

	element elem;
	elem.name = "element1";
	elem.type = "struct";
	elem.startline = 12;
	elem.endline = 23;
	tree->setRoot(elem)
	tree->AddChild(elem);

	element elem2;
	elem2.name = "element2";
	elem2.type = "function";
	elem2.startline = 25;
	elem2.endline = 30;
	tree->setRecent(elem2);
	tree->AddChild(elem2);

	std::cout << elem.name << " " << elem.type << " " << elem.lineCount << "  " << elem.parent;
	std::cout << elem2.name << " " << elem2.type << " " << elem2.lineCount << "  " << elem2.parent;
}

#endif