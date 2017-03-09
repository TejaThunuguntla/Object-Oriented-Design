#ifndef ACTIONSANDRULES_H
#define ACTIONSANDRULES_H

/////////////////////////////////////////////////////////////////////
//  ActionsAndRules.h - declares new parsing rules and actions     //
//  Language:        Visual C++ 2015, SP1                          //
//  ver 1.0                                                        //
//  Application:     Parser Component				               //
//  Author:		     Teja Thunuguntla, Syracuse University		   //
//  Source:          Jim Fawcett, CST 4-187, Syracuse University   //
//                   (315) 443-3948, jfawcett@twcny.rr.com         //
/////////////////////////////////////////////////////////////////////
/*
  Module Operations: 
  ==================
  This module defines several action classes.  Its classes provide 
  specialized services needed for specific applications.  The modules
  Parser, SemiExpression, and Tokenizer, are intended to be reusable
  without change.  This module provides a place to put extensions of
  these facilities and is not expected to be reusable. 

  Public Interface:
  =================
  Toker t(someFile);              // create tokenizer instance
  SemiExp se(&t);                 // create a SemiExp attached to tokenizer
  Parser parser(se);              // now we have a parser
  Rule1 r1;                       // create instance of a derived Rule class
  Action1 a1;                     // create a derived action
  r1.addAction(&a1);              // register action with the rule
  parser.addRule(&r1);            // register rule with parser
  while(se.getSemiExp())          // get semi-expression
  parser.parse();                 // and parse it

  Build Process:
  ==============
  Required files
    - Parser.h, Parser.cpp, ScopeStack.h, ScopeStack.cpp,
      ActionsAndRules.h, ActionsAndRules.cpp, ConfigureParser.cpp,
      ItokCollection.h, SemiExpression.h, SemiExpression.cpp, tokenizer.h, tokenizer.cpp
	  
  Build commands:
  ===============
  - devenv project2.sln

  Maintenance History:
  ====================
  ver 1.0 : 12 Mar 16
  - first release

*/

#include <queue>
#include <string>
#include <sstream>
#include "Parser.h"
#include "../SemiExp/itokcollection.h"
#include "../ScopeStack/ScopeStack.h"
#include "../Tokenizer/Tokenizer.h"
#include "../SemiExp/SemiExp.h"

///////////////////////////////////////////////////////////////
// Repository instance is used to share resources
// among all actions.

class Repository  // application specific
{
  ScopeStack<element> stack;
  Scanner::Toker* p_Toker;
  element root;
  AST* tree = new AST(&stack);
public:
  Repository(Scanner::Toker* pToker)
  {
	  if (stack.size() == 0)
	  {
		  root.name = "GlobalNameSpace";
		  root.type = "root";
		  root.startline = 0;
		  stack.push(root);
		  tree->setRoot(root);
	  }
    p_Toker = pToker;
  }
  ScopeStack<element>& scopeStack()
  {  
    return stack;
  }
  AST* getTree()
  {
	  return tree;
  }
  Scanner::Toker* Toker()
  {
    return p_Toker;
  }
  size_t lineCount()
  {
    return (size_t)(p_Toker->currentLineCount());
  }
};

///////////////////////////////////////////////////////////////
// rule to detect beginning of scope

class BeginningOfScope : public IRule
{
public:
  bool doTest(ITokCollection*& pTc)
  {
    if(pTc->find("{") < pTc->length())
    {
      doActions(pTc);
      return true;
    }
    return true;
  }
};

///////////////////////////////////////////////////////////////
// action to handle scope stack at beginning of scope

class HandlePush : public IAction
{
  Repository* p_Repos;
public:
  HandlePush(Repository* pRepos)
  {
    p_Repos = pRepos;
  }
  void doAction(ITokCollection*& pTc)
  {
    element elem;
    elem.type = "scope";
    elem.name = "BeginScope";
    elem.lineCount = p_Repos->lineCount();
    p_Repos->scopeStack().push(elem);
  }
};

///////////////////////////////////////////////////////////////
// rule to detect end of scope

class EndOfScope : public IRule
{
public:
  bool doTest(ITokCollection*& pTc)
  {
    if(pTc->find("}") < pTc->length())
    {
      doActions(pTc);
      return true;
    }
    return true;
  }
};

///////////////////////////////////////////////////////////////
// action to handle scope stack at end of scope

class HandlePop : public IAction
{
  Repository* p_Repos;
public:
  HandlePop(Repository* pRepos)
  {
    p_Repos = pRepos;
  }
  void doAction(ITokCollection*& pTc)
  {
    if(p_Repos->scopeStack().size() == 0)
      return;
    element elem = p_Repos->scopeStack().pop();

	if (elem.type == "function")
	{
		AST* tree = p_Repos->getTree();
		elem.endline = (p_Repos->lineCount() - 1);
		tree->setRecent(elem);
	}
	else if (elem.type == "namespace")
	{
		AST* tree = p_Repos->getTree();
		elem.endline = p_Repos->lineCount();
		tree->setRecent(elem);
	}
	else if (elem.type == "class" || elem.type == "struct" || elem.type == "enum")
	{
		AST* tree = p_Repos->getTree();
		elem.endline = p_Repos->lineCount();
		tree->setRecent(elem);
	}
	else if (elem.type == "SplBlock")
	{
		AST* tree = p_Repos->getTree();
		elem.endline = p_Repos->lineCount();
		tree->setRecent(elem);
	}
  }
};

///////////////////////////////////////////////////////////////
// rule to detect preprocessor statements

class PreprocStatement : public IRule
{
public:
  bool doTest(ITokCollection*& pTc)
  {
    if(pTc->find("#") < pTc->length())
    {
      doActions(pTc);
      return true;
    }
    return true;
  }
};

///////////////////////////////////////////////////////////////
// rule to detect the definitions of namespace, 
// class, struct and enum

class ClassNamespace : public IRule
{
public:
	bool doTest(ITokCollection*& pTc)
	{
		ITokCollection& tc = *pTc;
		size_t len = tc.length() - 1;
		if (tc[len] == "{")
		{
			if (tc.find("class") < tc.length() || tc.find("namespace") < tc.length()
				|| tc.find("struct") < tc.length() || tc.find("enum") < tc.length()) {
				doActions(pTc);
				return true;
			}
		}
		return true;
	}
};

///////////////////////////////////////////////////////////////
// action to push namespace, class, struct and 
// namespace onto scope stack

class PushClassNamespace : public IAction
{
	Repository* p_Repos;
public:
	PushClassNamespace(Repository* pRepos)
	{
		p_Repos = pRepos;
	}
	void doAction(ITokCollection*& pTc)
	{
		// pop anonymous scope
		p_Repos->scopeStack().pop();

		// push function scope
		element elem;
		std::string name;
		if (pTc->find("class") < pTc->length()) {
			name = (*pTc)[pTc->find("class") + 1];
			elem.type = "class";
		}
		else if (pTc->find("namespace") < pTc->length()) {
			name = (*pTc)[pTc->find("namespace") + 1];
			elem.type = "namespace";
		}
		else if (pTc->find("struct") < pTc->length()) {
			name = (*pTc)[pTc->find("struct") + 1];
			elem.type = "struct";
		}
		else if (pTc->find("enum") < pTc->length()) {
			name = (*pTc)[pTc->find("enum") + 1];
			elem.type = "enum";
		}
		elem.name = name;
		elem.lineCount = p_Repos->lineCount();
		AST* tree = p_Repos->getTree();
		tree->AddChild(elem);
		p_Repos->scopeStack().push(elem);
	}
};

///////////////////////////////////////////////////////////////
// rule to detect try, do, else and else if blocks

class TryDo : public IRule
{
public:
	bool doTest(ITokCollection*& pTc)
	{
		ITokCollection& tc = *pTc;
		size_t len = tc.length() - 1;
		if (tc[len] == "{")
		{
			if ((tc.find("try") < tc.length()) || (tc.find("do") < tc.length()) 
				|| (tc.find("else") < tc.length() && tc.find("if")>= tc.length())) {
				doActions(pTc);
				return true;
			}
		}
		return false;
	}
};

///////////////////////////////////////////////////////////////
// action to push try, do, else and else if onto scope stack

class PushTryDo : public IAction
{
	Repository* p_Repos;
public:
	PushTryDo(Repository* pRepos)
	{
		p_Repos = pRepos;
	}
	void doAction(ITokCollection*& pTc)
	{
		// pop anonymous scope
		p_Repos->scopeStack().pop();

		// push function scope
		element elem;
		std::string name = (*pTc)[pTc->find("{") - 1];
		if (name != "try" || name != "else" || name != "do")
			name = (*pTc)[pTc->find("{") - 2];
		elem.type = "SplBlock";
		elem.name = name;
		elem.lineCount = p_Repos->lineCount();
		p_Repos->scopeStack().push(elem);

		AST* tree = p_Repos->getTree();
		tree->AddChild(elem);
		p_Repos->scopeStack().push(elem);
	}
};

///////////////////////////////////////////////////////////////
// rule to detect special blocks

class SplBlock : public IRule
{
public:
	bool isSplKeyword(std::string& tok)
	{
		const static std::string keys[]
			= { "for", "while", "switch", "if", "catch", "else if" };

		for (int i = 0; i < 5; ++i)
			if (tok == keys[i])
				return true;
		return false;
	}
	bool doTest(ITokCollection*& pTc)
	{
		ITokCollection& tc = *pTc;
		if (tc[tc.length() - 1] == "{")
		{
			size_t len = tc.find("(");
			if (len < tc.length() && isSplKeyword(tc[len - 1]))
			{
				doActions(pTc);
				return true;
			}
		}
		return false;
	}
};

///////////////////////////////////////////////////////////////
// action to push special blocks onto ScopeStack

class PushSplBlock : public IAction
{
	Repository* p_Repos;
public:
	PushSplBlock(Repository* pRepos)
	{
		p_Repos = pRepos;
	}
	void doAction(ITokCollection*& pTc)
	{
		// pop anonymous scope
		p_Repos->scopeStack().pop();

		// push function scope
		std::string name = (*pTc)[pTc->find("(") - 1];
		element elem;
		elem.type = "SplBlock";
		elem.name = name;
		elem.lineCount = p_Repos->lineCount();
		p_Repos->scopeStack().push(elem);

		AST* tree = p_Repos->getTree();
		tree->AddChild(elem);
		p_Repos->scopeStack().push(elem);
	}
};

///////////////////////////////////////////////////////////////
// rule to detect function definitions

class FunctionDefinition : public IRule
{
public:
  bool isSpecialKeyWord(const std::string& tok)
  {
    const static std::string keys[]
      = { "for", "while", "switch", "if", "catch" };
    for(int i=0; i<5; ++i)
      if(tok == keys[i])
        return true;
    return false;
  }

  bool doTest(ITokCollection*& pTc)
  {
    ITokCollection& tc = *pTc;
    if(tc[tc.length()-1] == "{")
    {
      size_t len = tc.find("(");
		
      if(len < tc.length() && !isSpecialKeyWord(tc[len-1]))
      {
        doActions(pTc);
        return true;
      } 
    }
    return true;
  }
};

///////////////////////////////////////////////////////////////
// action to push function name onto ScopeStack

class PushFunction : public IAction
{
  Repository* p_Repos;
public:
  PushFunction(Repository* pRepos)
  {
    p_Repos = pRepos;
  }

  void doAction(ITokCollection*& pTc)
  {
    // pop anonymous scope
    p_Repos->scopeStack().pop();

    // push function scope

    element elem;

    elem.type = "function";
    elem.name = (*pTc)[pTc->find("(") - 1];
    elem.lineCount = p_Repos->lineCount();
	AST* tree = p_Repos->getTree();
	tree->AddChild(elem);
    p_Repos->scopeStack().push(elem);
  }
};

#endif