/////////////////////////////////////////////////////////////////////
// Tokenizer.cpp - read words from a std::stream                   //
// ver 1.0                                                         //
// Language:    C++, Visual Studio 2015                            //
// Application: Parser component, CSE687 - Object Oriented Design  //
// Author:		Teja Thunuguntla, Syracuse University			   //
// Source:      Jim Fawcett, Syracuse University, CST 4-187        //
/////////////////////////////////////////////////////////////////////

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <exception>
#include "SemiExp.h"
//#include "iTokcollection.h"
//#include "../Tokenizer/Tokenizer.h"

using namespace Scanner;

SemiExp::SemiExp(Toker* pToker) : _pToker(pToker) {}

bool SemiExp::get(bool clr)
{
	if (_pToker == nullptr)
		throw(std::logic_error("No Toker Reference"));
	if (clr) 
		clear();
	while (true)
	{
		std::string token = _pToker->getTok();
		if (token == "")
			break;
		push_back(token);
		trimFront();
		//if (SemiExp::length() > 0) {
			if (token.length() > 2 && token.at(0) == '/' && (token.at(1) == '/' || token.at(1) == '*'))
				return true;
			else if (length() > 0 && token == "for")
				getHelper();
			else if (length() > 0 && (token == "{" || token == "}" || token == ";"))
				return true;
			else if (length() > 0 && _tokens.front() == "#" && (token == "newline" || token == "\n"))
				return true;
			else if (length() > 0 && token == ":" && (_tokens.front() == "public" || _tokens.front() == "private" || _tokens.front() == "protected"))
				return true;
		//}
	}
	return false;
}

/*Token SemiExp::operator[](size_t n)
{
  if (n < 0 || n >= length())
    throw(std::invalid_argument("index out of range"));
  return _tokens[n];
}*/

size_t SemiExp::find(const std::string & tok)
{
	//for (auto toke : _tokens)
	//{
	//	if (toke == tok)
	//	{
	//		return toke.;
	//	}
	//}
	for (size_t i = length() - 1; i > 0; i--) {
		if (_tokens[i] == tok)
		{
			return i;
		}
	}
	return 0;
}

void SemiExp::push_back(const std::string & tok)
{
	_tokens.push_back(tok);
}

bool SemiExp::remove(const std::string & tok)
{
	//if (semiExpress.find(tok) != std::string::npos) {
	//	semiExpress.erase(semiExpress.find(tok),tok.length);
	//	return true;
	//}
	//else
	//	return false;
	for (int i = 0; i < length(); i++) {
		if (_tokens[i] == tok)
		{
			_tokens.erase(_tokens.begin() + i);
			return true;
		}
	}
	return false;
}

bool SemiExp::remove(size_t pos)
{
	if (pos < length())
	{
		_tokens.erase(_tokens.begin() + pos);
		return true;
	}
	return false;
}

void SemiExp::toLower()
{
	//for (char c : semiExpress) {
	//	putchar(toLower(c));
	//}
	//int i = 0;
	char c;
	for (std::string toke : _tokens) {
		for (int i = 0; i < toke.length(); i++)
		{
			c = toke[i];
			putchar(tolower(c));
		}
	}
}

void SemiExp::trimFront() {
	//if(semiExpress == "newline")
	//	semiExpress.
	if (_tokens.front() == "newline" || _tokens.front() == "\n" || _tokens.front() == " ")
		_tokens.erase(_tokens.begin());
}

void SemiExp::clear() {
	_tokens.clear();
}

size_t SemiExp::length()
{
  return _tokens.size();
}

std::string & Scanner::SemiExp::operator[](int n)
{
	if (n < 0 || n >= length())
		throw(std::invalid_argument("index out of range"));
	return _tokens[n];
}
//void SemiExp::show()
//{
//  std::cout << "\n  ";
//  for (auto token : _tokens)
//    if(token != "\n" && token!= "newline")
//      std::cout << token << " ";
//  std::cout << "\n";
//}

std::string SemiExp::show(bool showNewLines) {
	std::cout << "\n";
	if (showNewLines) {
		for (auto tok : _tokens)
			std::cout << tok << " ";
	}
	else {
		for (auto tok : _tokens)
			if (tok != "\n" && tok != "newline") 
				std::cout << tok << " ";				
	}
	return "";
}

void SemiExp::getHelper()
{
	int count = 0;
	while (true) {
		if (count == 2 && (SemiExp::find(")") > SemiExp::find(";")))
			break;
		else {
			std::string toke = _pToker->getTok();
			if (toke != "\n")
				_tokens.push_back(toke);
			if (toke == ";")
				count++;
		}
	}
}

//----< test stub >--------------------------------------------------

#ifdef TEST_SEMIEXP

#include <fstream>

int main()
{
  Toker toker;
  //std::string fileSpec = "../Tokenizer/Token.txt";
  std::string fileSpec = "../Tokenizer/test.txt";
  //std::string fileSpec = "../Tokenizer/Tokenizer.cpp";
  std::fstream in(fileSpec);
  if (!in.good())
  {
    std::cout << "\n  can't open file " << fileSpec << "\n\n";
    return 1;
  }
  toker.attach(&in);

  SemiExp semi(&toker);
  while(semi.get(true) || in.good())
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

#endif TEST_SEMIEXP