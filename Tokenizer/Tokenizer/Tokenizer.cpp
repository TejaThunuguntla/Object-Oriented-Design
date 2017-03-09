/////////////////////////////////////////////////////////////////////
// Tokenizer.cpp - read words from a std::stream                   //
// ver 1.0                                                         //
// Language:    C++, Visual Studio 2015                            //
// Application: Parser component, CSE687 - Object Oriented Design  //
// Author:		Teja Thunuguntla, Syracuse University			   //
// Source:      Jim Fawcett, Syracuse University, CST 4-187        //
/////////////////////////////////////////////////////////////////////
/*
Helper code that does not attempt to handle all tokenizing
special cases like escaped characters.
*/
#include "Tokenizer.h"
#include <iostream>
#include <cctype>
#include <string>

namespace Scanner
{
	class ConsumeState
	{
	public:
		ConsumeState();
		ConsumeState(const ConsumeState&) = delete;
		ConsumeState& operator=(const ConsumeState&) = delete;
		virtual ~ConsumeState();
		void attach(std::istream* pIn) { _pIn = pIn; }
		virtual void eatChars() = 0;
		void consumeChars() {
			if (_pState == nullptr)
				_pState = _pEatWhitespace;
			_pState->eatChars();
			_pState = nextState();
		}
		bool canRead() { return _pIn->good(); }
		std::string getTok() { return token; }
		bool hasTok() { return token.size() > 0; }
		bool isSpecialSingleChars(int currChar); // to check special one character tokens
		bool isSpecialCharPairs(int currChar);   // to check special two character token pairs
		bool isEscape(int currChar);   // to check whether the token is an escape sequence
		ConsumeState* nextState();
	protected:
		static std::string token;
		static std::istream* _pIn;
		static int prevChar;
		static int currChar;
		static ConsumeState* _pState;
		static ConsumeState* _pEatCppComment;
		static ConsumeState* _pEatCComment;
		static ConsumeState* _pEatWhitespace;
		static ConsumeState* _pEatPunctuator;
		static ConsumeState* _pEatAlphanum;
		static ConsumeState* _pEatStr;
		static ConsumeState* _pEatNewline;
	};
}

using namespace Scanner;

std::string ConsumeState::token;
std::istream* ConsumeState::_pIn = nullptr;
int ConsumeState::prevChar;
int ConsumeState::currChar;
ConsumeState* ConsumeState::_pState = nullptr;
ConsumeState* ConsumeState::_pEatCppComment = nullptr;
ConsumeState* ConsumeState::_pEatCComment = nullptr;
ConsumeState* ConsumeState::_pEatWhitespace = nullptr;
ConsumeState* ConsumeState::_pEatPunctuator = nullptr;
ConsumeState* ConsumeState::_pEatAlphanum = nullptr;
ConsumeState* ConsumeState::_pEatStr = nullptr;
ConsumeState* ConsumeState::_pEatNewline;

void testLog(const std::string& msg);

//----------< Decides the next state based on current character >----------
ConsumeState* ConsumeState::nextState()
{
	if (!(_pIn->good()))
	{
		return nullptr;
	}
	int chNext = _pIn->peek();
	if (chNext == EOF)
	{
		_pIn->clear();
		// if peek() reads end of file character, EOF, then eofbit is set and
		// _pIn->good() will return false.  clear() restores state to good
	}
	if (std::isspace(currChar) && currChar != '\n') // Check whether the current character is white space
	{
		testLog("state: eatWhitespace");
		return _pEatWhitespace;
	}
	if (currChar == '/' && chNext == '/') // Check whether the current character is CPP comment
	{
		testLog("state: eatCppComment");
		return _pEatCppComment;
	}
	if (currChar == '/' && chNext == '*') // Check whether the current character is C comment
	{
		testLog("state: eatCComment");
		return _pEatCComment;
	}
	if (currChar == '\n') // Check whether the current character is New Line
	{
		testLog("state: eatNewLine");
		return _pEatNewline;
	}
	if (std::isalnum(currChar)) // Check whether the current character is Alpha numerals
	{
		testLog("state: eatAlphanum");
		return _pEatAlphanum;
	}
	if (currChar == 34) // Check whether the current character is String
	{
		testLog("state: eatString");
		return _pEatStr;
	}
	if (ispunct(currChar)) // Check whether the current character is Special Character
	{
		testLog("state: eatPunctuator");
		return _pEatPunctuator;
	}
	if (!_pIn->good())
	{
		//std::cout << "\n  end of stream with currChar = " << currChar << "\n\n";
		return _pEatWhitespace;
	}
	throw(std::logic_error("invalid type"));
}

//-------------< Eat the white space occured >------------
class EatWhitespace : public ConsumeState
{
public:
	virtual void eatChars()
	{
		token.clear();
		//std::cout << "\n  eating whitespace";
		do {
			if (!_pIn->good())  // end of stream
				return;
			currChar = _pIn->get();
		} while (std::isspace(currChar) && currChar != '\n');
	}
};

//---------- Collect the CPP comments starting with // ----------
class EatCppComment : public ConsumeState
{
public:
	virtual void eatChars()
	{
		token.clear();
		//std::cout << "\n  eating C++ comment";
		do {
			token += currChar;
			if (!_pIn->good())  // end of stream
				return;
			currChar = _pIn->get();
		} while (currChar != '\n');
	}
};

//------------ Collect the C comments with /*---- */ ----------
class EatCComment : public ConsumeState
{
public:
	virtual void eatChars()
	{
		token.clear();
		//std::cout << "\n  eating C comment";
		do {
			token += currChar;
			if (!_pIn->good())  // end of stream
				return;
			currChar = _pIn->get();
		} while (currChar != '*' || _pIn->peek() != '/');
		token += "*/";
		_pIn->get();
		currChar = _pIn->get();
	}
};

//------------< collect the special characters occured >--------------
class EatPunctuator : public ConsumeState
{
public:
	virtual void eatChars()
	{
		token.clear();
		//std::cout << "\n  eating punctuator";
		if (isSpecialCharPairs(currChar) || isEscape(currChar))
		{
			token += currChar;
			currChar = _pIn->get();
		}
		else if (isSpecialSingleChars(currChar))
		{
			if (currChar == 92 && _pIn->peek() == 'n') {
				token += currChar;
				currChar = _pIn->get();
			}
		}
		token += currChar;
		if (!_pIn->good())  // end of stream
			return;
		currChar = _pIn->get();
	}
};

//-------------< Collect the Alpha numerals occured >-------------
class EatAlphanum : public ConsumeState
{
public:
	virtual void eatChars()
	{
		token.clear();
		//std::cout << "\n  eating alphanum";
		do {
			token += currChar;
			if (!_pIn->good())  // end of stream
				return;
			currChar = _pIn->get();
		} while (isalnum(currChar));
	}
};

//-------------< Collect the strings occured >-------------
class EatStr : public ConsumeState
{
public:
	virtual void eatChars()
	{
		token.clear();
		//std::cout << "\n  eating strings";
		do {
			token += currChar;
			if (isEscape(currChar)) {
				currChar = _pIn->get();
				token += currChar;
			}
			if (!_pIn->good())  // end of stream
				return;
			currChar = _pIn->get();
		} while (currChar != 34);
		token += currChar;
		currChar = _pIn->get();
	}
};

//-------------< Collect the new line occured >--------------
class EatNewline : public ConsumeState
{
public:
	virtual void eatChars()
	{
		token.clear();
		//std::cout << "\n  eating alphanum";
		token += currChar;
		if (!_pIn->good())  // end of stream
			return;
		currChar = _pIn->get();
	}
};

ConsumeState::ConsumeState()
{
	static bool first = true;
	if (first)
	{
		first = false;
		_pEatAlphanum = new EatAlphanum();
		_pEatCComment = new EatCComment();
		_pEatCppComment = new EatCppComment();
		_pEatPunctuator = new EatPunctuator();
		_pEatWhitespace = new EatWhitespace();
		_pEatStr = new EatStr();
		_pEatNewline = new EatNewline();
		_pState = _pEatWhitespace;
	}
}

ConsumeState::~ConsumeState()
{
	static bool first = true;
	if (first)
	{
		first = false;
		delete _pEatAlphanum;
		delete _pEatCComment;
		delete _pEatCppComment;
		delete _pEatPunctuator;
		delete _pEatWhitespace;
		delete _pEatNewline;
		delete _pEatStr;
	}
}

Toker::Toker() : pConsumer(new EatWhitespace()) {}

Toker::~Toker() { delete pConsumer; }

bool Toker::attach(std::istream* pIn)
{
	if (pIn != nullptr && pIn->good())
	{
		pConsumer->attach(pIn);
		return true;
	}
	return false;
}

// ---------------< to check special one character tokens >-------------------
bool ConsumeState::isSpecialSingleChars(int tok)
{
	if (tok == '<' || tok == '>' || tok == '[' || tok == ']' || tok == '(' ||
		tok == ')' || tok == '{' || tok == '}' || tok == ':' || tok == '=' ||
		tok == '+' || tok == '-' ||	tok == '*' || tok == 92)
	{
		return true;
	}
	return false;
}

// ---------------< to check special two character token pairs >-------------------
bool ConsumeState::isSpecialCharPairs(int tok)
{
	int nextChar = _pIn->peek();

	if (tok == '<' && nextChar == '<' || 
		tok == '>' && nextChar == '>' || 
		tok == ':' && nextChar == ':' ||
		tok == '+' && nextChar == '+' || 
		tok == '-' && nextChar == '-' || 
		tok == '=' && nextChar == '=' ||
		tok == '+' && nextChar == '=' || 
		tok == '-' && nextChar == '=' || 
		tok == '*' && nextChar == '=' ||
		tok == '/' && nextChar == '=' )
		return true;

	return false;
}

// ---------------< to check for escape sequence >-------------------
bool ConsumeState::isEscape(int tok) 
{
	int nextChar = _pIn->peek();

	if (tok == 92 && (nextChar == '0' || nextChar == 39 ||
		nextChar == 34 || nextChar == 92 || nextChar == 't' ||
		nextChar == 'b' || nextChar == 'r' || nextChar == 'v'))
	/* 92 = \ and 39 = ' and 34 = "  */
		return true;

	return false;
}


std::string Toker::getTok()
{
	while (true)
	{
		pConsumer->consumeChars();
		if (pConsumer->hasTok())
			break;
		if (!pConsumer->canRead())
			return "";
	}
	return pConsumer->getTok();
}

bool Toker::canRead() { return pConsumer->canRead(); }

void testLog(const std::string& msg)
{
#ifdef TEST_LOG
	std::cout << "\n  " << msg;
#endif
}

//----< test stub >--------------------------------------------------

#ifdef TEST_TOKENIZER

#include <fstream>

int main()
{
	//std::string fileSpec = "../Tokenizer/Tokenizer.cpp";
	//std::string fileSpec = "../Tokenizer/Tokenizer.h";
	std::string fileSpec = "../Tokenizer/Test.txt";

	std::ifstream in(fileSpec);
	if (!in.good())
	{
		std::cout << "\n  can't open " << fileSpec << "\n\n";
		return 1;
	}
	Toker toker;
	toker.attach(&in);
	do
	{
		std::string tok = toker.getTok();
		if (tok == "\n")
			tok = "newline";
		std::cout << "\n -- " << tok;
	} while (in.good());

	std::cout << "\n\n";
	return 0;
}
#endif