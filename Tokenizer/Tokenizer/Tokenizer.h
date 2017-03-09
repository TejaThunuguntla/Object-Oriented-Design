#ifndef TOKENIZER_H
#define TOKENIZER_H
/////////////////////////////////////////////////////////////////////
// Tokenizer.cpp - read words from a std::stream                   //
// ver 1.0                                                         //
// Language:    C++, Visual Studio 2015                            //
// Application: tokenizing a file, CSE687 - Object Oriented Design //
// Author:      Teja Thunuguntla, CE, Syracuse University,		   //
//              tthunugu@syr.edu                                   //
// Source:      Jim Fawcett, Syracuse University, CST 4-187        //
/////////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This package provides a public Toker class and private ConsumeState class.
* Toker reads words from a std::stream, throws away whitespace
* and returns words from the stream in the order encountered.  
* Quoted strings and certain punctuators and newlines are returned as single tokens.
*
* This is a new version, based on the State Design Pattern.  Older versions
* exist, based on an informal state machine design.
*
* Build Process:
* --------------
* Required Files: Tokenizer.h, Tokenizer.cpp
* Build Command: devenv Tokenizer.sln /rebuild debug
*
* Maintenance History:
* --------------------
* ver 1.0 : 09 Feb 2016
*
* Planned Additions and Changes:
* ------------------------------
* - Return quoted strings as single token.  This must handle \" and \'
*   correctly.
* - Consider converting eatNewLine() to eatSpecialTokens() - see below
* - Return  <, >, [, ], (, ), {, }, :, =, +, -, *, \n as single character tokens
* - Return <<, >>, ::, ++, --, ==, +=, -=, *=, /= as two character tokens
*/
#include <iosfwd>
#include <string>

namespace Scanner
{
	class ConsumeState;

	class Toker
	{
	public:
		Toker();
		Toker(const Toker&) = delete;
		~Toker();
		Toker& operator=(const Toker&) = delete;
		bool attach(std::istream* pIn); // Attach the input file using istream pointer
		std::string getTok(); // Collects the next token in the stream
		bool canRead(); // Checks the end of the stream
	private:
		ConsumeState* pConsumer;
	};
}
#endif



