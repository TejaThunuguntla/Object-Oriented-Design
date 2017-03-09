///////////////////////////////////////////////////////////////////////
// TestSuite.cpp - test the functionality of Tokenizer and SemiExp	 //
// ver 1.0                                                           //
// Language:    C++, Visual Studio 2015                              //
// Application: Parser component, CSE687 - Object Oriented Design	 //
// Author:		Teja Thunuguntla, Syracuse University				 //
//				tthunugu@syr.edu									 //
///////////////////////////////////////////////////////////////////////

#include <fstream>
#include <iostream>
#include <string>/*
#include "../SemiExp/SemiExp.h"
#include "../SemiExp/iTokcollection.h"*/
#include <E:/Teja/Syracuse University/OOD/Project1/SemiExp/SemiExp.h>
#include <E:/Teja/Syracuse University/OOD/Project1/Tokenizer/Tokenizer.h>
//#include "Test Suite.h"

using namespace Scanner;

//SemiExp::SemiExp(Toker* pToker) : _pToker(pToker) {}

int main() 
{
	std::string fileSpec = "../../Tokenizer/test1.txt";

	std::ifstream in(fileSpec);
	if (!in.good())
	{
		std::cout << "\n  can't open " << fileSpec << "\n\n";
		return 1;
	}
	Toker toker;
	toker.attach(&in);
	while (in.good())
	{
		std::string tok = toker.getTok();
		if (tok == "\n")
			tok = "newline";
		std::cout << "\n -- " << tok;
	}
	std::cout << "\n\n";

	// Semi Expression

	std::string fileSpec1 = "../../Tokenizer/test1.txt";
	std::fstream in1(fileSpec1);
	if (!in1.good())
	{
		std::cout << "\n  can't open file " << fileSpec1 << "\n\n";
		return 1;
	}
	Toker toker1;
	toker1.attach(&in1);
	
	SemiExp semi(&toker1);
	while (semi.get(true))
	{
		std::cout << "\n\n  -- semiExpression --";
		semi.show(false);
	}
	/*
	May have collected tokens, but reached end of stream
	before finding SemiExp terminator.
	*/
	if (semi.length() > 0)
	{
		std::cout << "\n\n  -- semiExpression --";
		semi.show();
		std::cout << "\n\n";
	}
	return 0;
}