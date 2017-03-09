#ifndef CONFIGUREPARSER_H
#define CONFIGUREPARSER_H

/////////////////////////////////////////////////////////////////////
//  ConfigureParser.h - builds and configures parsers              //
//  ver 1.0														   //
//  Language:        Visual C++ 2008, SP1                          //
//  Application:     Parser Component				               //
//  Author:		     Teja Thunuguntla, Syracuse University		   //
//  Source:          Jim Fawcett, CST 4-187, Syracuse University   //
//                   (315) 443-3948, jfawcett@twcny.rr.com         //
/////////////////////////////////////////////////////////////////////
/*
  Module Operations: 
  ==================
  This module builds and configures parsers.  It builds the parser
  parts and configures them with application specific rules and actions.

  Public Interface:
  =================
  ConfigParseToConsole conConfig;
  conConfig.Build();
  conConfig.Attach(someFileName);

  Build Process:
  ==============
  Required files
    - ConfigureParser.h, ConfigureParser.cpp, Parser.h, Parser.cpp,
      ActionsAndRules.h, ActionsAndRules.cpp,
      SemiExpression.h, SemiExpression.cpp, tokenizer.h, tokenizer.cpp

  Build commands:
  ===============
  - devenv project2.sln

  Maintenance History:
  ====================
  ver 1.0 : 12 Mar 16
  - first release

*/

#include <fstream>
#include "Parser.h"
#include "../SemiExp/SemiExp.h"
#include "../Tokenizer/Tokenizer.h"
#include "ActionsAndRules.h"

///////////////////////////////////////////////////////////////
// build parser that writes its output to console

class ConfigParseToConsole : IBuilder
{
public:
  ConfigParseToConsole() {};
  ~ConfigParseToConsole();
  bool Attach(const std::string& name, bool isFile=true);
  Parser* Build();
  AST* tree;

private:
  // Builder must hold onto all the pieces

  std::ifstream* pIn;
  Scanner::Toker* pToker;
  Scanner::SemiExp* pSemi;
  Parser* pParser;
  Repository* pRepo;

  // add Rules and Actions

  BeginningOfScope* pBeginningOfScope;
  HandlePush* pHandlePush;

  EndOfScope* pEndOfScope;
  HandlePop* pHandlePop;

  FunctionDefinition* pFunctionDefinition;
  PushFunction* pPushFunction;

  ClassNamespace* pClassNameSpace;
  PushClassNamespace* pPushClassNamespace;

  TryDo* pTryDo;
  PushTryDo* pPushTryDo;

  SplBlock* pSplBlock;
  PushSplBlock* pPushSplBlock;

  // prohibit copies and assignments

  ConfigParseToConsole(const ConfigParseToConsole&) = delete;
  ConfigParseToConsole& operator=(const ConfigParseToConsole&) = delete;
};

#endif