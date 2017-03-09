#ifndef SEMIEXPRESSION_H
#define SEMIEXPRESSION_H

///////////////////////////////////////////////////////////////////////
// SemiExpression.h - collect tokens for analysis                    //
// ver 1.0                                                           //
// Language:    C++, Visual Studio 2015                              //
// Application: Parser component, CSE687 - Object Oriented Design    //
// Author:		Teja Thunuguntla									 //
// Source:      Jim Fawcett, Syracuse University, CST 4-187          //
//              jfawcett@twcny.rr.com                                //
///////////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This package provides a public SemiExp class that collects and makes
* available sequences of tokens.  SemiExp uses the services of a Toker
* class to acquire tokens.  Each call to SemiExp::get() returns a 
* sequence of tokens that ends in {.  This will be extended to use the
* full set of terminators: {, }, ;, and '\n' if the line begins with #.
*
* This is a new version for students in CSE687 - OOD, Spring 2016 to use
* for Project #1.
*
* Build Process:
* --------------
* Required Files: 
*   SemiExpression.h, SemiExpression.cpp, Tokenizer.h, Tokenizer.cpp
* 
* Build Command: devenv Project1.sln /rebuild debug
*
* Maintenance History:
* --------------------
* ver 1.0 : 9 Feb 2016
*
* Planned Additions and Changes:
* ------------------------------
* - add public :, protected :, private : as terminators
* - move creation of tokenizer into semiExp constructor so
*   client doesn't have to write that code.
*/

#include <vector>
#include "../Tokenizer/Tokenizer.h"
#include "iTokcollection.h"

namespace Scanner
{
  using Token = std::string;

  class SemiExp:public ITokCollection
  {
  public:
    SemiExp(Toker* pToker);
    //bool get();
	//virtual bool get(bool clear = true);
    //Token operator[](size_t n);
    //void show();
	virtual bool get(bool clear = true);
	virtual size_t length();
	virtual std::string& operator[](int n);
	virtual size_t find(const std::string& tok);
	virtual void push_back(const std::string& tok);
	//virtual bool merge(const std::string& firstTok, const std::string& secondTok) = 0;
	virtual bool remove(const std::string& tok);
	virtual bool remove(size_t i);
	virtual void toLower();
	virtual void trimFront();
	virtual void clear();
	virtual std::string show(bool showNewLines = false);
	void getHelper();
  private:
    std::vector<Token> _tokens;
    Toker* _pToker;
  //protected:
	 // static std::string semiExpress;
  };
}
#endif
