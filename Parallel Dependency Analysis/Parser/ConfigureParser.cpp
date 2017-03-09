///////////////////////////////////////////////////////////////////////
//  ConfigureParser.cpp - builds and configures parsers              //
//  ver 1.0														     //
//  Language:        Visual C++ 2008, SP1                            //
// Application:  Parallel Dependency, CSE687 - Object Oriented Design//
// Author:		  Teja Thunuguntla, Syracuse University				 //
//				  tthunugu@syr.edu									 //
//  Source:          Jim Fawcett, CST 4-187, Syracuse University     //
//                   (315) 443-3948, jfawcett@twcny.rr.com           //
///////////////////////////////////////////////////////////////////////

#include <fstream>
#include "Parser.h"
#include "../SemiExp/SemiExp.h"
#include "../Tokenizer/Tokenizer.h"
#include "ActionsAndRules.h"
#include "ConfigureParser.h"

using namespace Scanner;

//----< destructor releases all parts >------------------------------

ConfigParseToConsole::~ConfigParseToConsole()
{
  // when Builder goes out of scope, everything must be deallocated

  delete pHandlePush;
  delete pBeginningOfScope;
  delete pHandlePop;
  delete pEndOfScope;
  delete pPushFunction;
  delete pFunctionDefinition;
  delete pClassNameSpace;
  delete pPushClassNamespace;
  delete pTryDo;
  delete pPushTryDo;
  delete pSplBlock;
  delete pPushSplBlock;
  delete pRepo;
  delete pParser;
  delete pSemi;
  delete pToker;
  pIn->close();
  delete pIn;
}
//----< attach toker to a file stream or stringstream >------------

bool ConfigParseToConsole::Attach(const std::string& name, bool isFile)
{
  if(pToker == 0)
    return false;
  pIn = new std::ifstream(name);
  file = name;
  if (!pIn->good())
    return false;
  return pToker->attach(pIn);
}
//----< Here's where alll the parts get assembled >----------------

Parser* ConfigParseToConsole::Build()
{
  try
  {
    // add Parser's main parts
    pToker = new Toker;
    pToker->returnComments(false);
    pSemi = new SemiExp(pToker);
    pParser = new Parser(pSemi);
    pRepo = new Repository(pToker);
	tree = pRepo->getTree();
	pRepo->setFileName(file);

    pBeginningOfScope = new BeginningOfScope();
    pHandlePush = new HandlePush(pRepo);
    pBeginningOfScope->addAction(pHandlePush);
    pParser->addRule(pBeginningOfScope);
    pEndOfScope = new EndOfScope();
    pHandlePop = new HandlePop(pRepo);
    pEndOfScope->addAction(pHandlePop);
    pParser->addRule(pEndOfScope);
    pFunctionDefinition = new FunctionDefinition;
    pPushFunction = new PushFunction(pRepo); 
    pFunctionDefinition->addAction(pPushFunction);
    pParser->addRule(pFunctionDefinition);

	// Namespace
	pNamespace = new NamespaceDef;
	pPushNamespace = new PushNamespaceDef(pRepo);
	pParser->addRule(pNamespace);
	pNamespace->addAction(pPushNamespace);

	//class, struct and enum
	pClassNameSpace = new ClassNamespace;
	pPushClassNamespace = new PushClassNamespace(pRepo);
	pParser->addRule(pClassNameSpace);
	pClassNameSpace->addAction(pPushClassNamespace);

	pTypeDef = new TypeDef;
	pPushTypeDef = new PushTypeDef(pRepo);
	pParser->addRule(pTypeDef);
	pTypeDef->addAction(pPushTypeDef);
		
	pAlias = new Aliases;
	pPushAlias = new PushAlias(pRepo);
	pParser->addRule(pAlias);
	pAlias->addAction(pPushAlias);
	
    return pParser;
  }
  catch(std::exception& ex)
  {
    std::cout << "\n\n  " << ex.what() << "\n\n";
    return 0;
  }
}

TypeTable* ConfigParseToConsole::getTypeTable()
{
	return pRepo->getTable();
}

#ifdef TEST_CONFIGUREPARSER

#include <queue>
#include <string>

int main(int argc, char* argv[])
{
  std::cout << "\n  Testing ConfigureParser module\n "
            << std::string(32,'=') << std::endl;

  // collecting tokens from files, named on the command line

  if(argc < 2)
  {
    std::cout 
      << "\n  please enter name of file to process on command line\n\n";
    return 1;
  }

  for(int i=1; i<argc; ++i)
  {
    std::cout << "\n  Processing file " << argv[i];
    std::cout << "\n  " << std::string(16 + strlen(argv[i]),'-');

    ConfigParseToConsole configure;
    Parser* pParser = configure.Build();
    try
    {
      if(pParser)
      {
        if(!configure.Attach(argv[i]))
        {
          std::cout << "\n  could not open file " << argv[i] << std::endl;
          continue;
        }
      }
      else
      {
        std::cout << "\n\n  Parser not built\n\n";
        return 1;
      }
      // now that parser is built, use it

      while(pParser->next())
        pParser->parse();
      std::cout << "\n\n";
    }
    catch(std::exception& ex)
    {
      std::cout << "\n\n    " << ex.what() << "\n\n";
    }
    std::cout << "\n\n";
  }
}

#endif
