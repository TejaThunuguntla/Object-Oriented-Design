#include "DependencyExec.h"

///////////////////////////////////////////////////////////////////////
// DependencyExec.cpp - checks for dependency on files		         //
///////////////////////////////////////////////////////////////////////
// ver 1.0															 //
// Application:  Parallel Dependency, CSE687 - Object Oriented Design//
// Author:		  Teja Thunuguntla, Syracuse University				 //
//				  tthunugu@sy.edu									 //
///////////////////////////////////////////////////////////////////////

DependencyAnalysis::DependencyAnalysis(Toker* pToker, TypeTable* Ttbl, std::string file) : _pToker(pToker),_typeTbl(Ttbl),_file(file) 
{
	mapDepend = new std::unordered_map<std::string, std::vector<std::string>>();
	_namespace.push_back("GlobalNameSpace");
}

// ------------------< returns a token using tokenizer >------------------
std::string DependencyAnalysis::getToke()
{
	if (_pToker == nullptr)
		throw(std::logic_error("no Toker reference"));

	return _pToker->getTok();
		
}

//-------------------< matches token with the type table >----------------------
void DependencyAnalysis::compare(std::string tok)
{
	if (mergedTbl.find(tok) != mergedTbl.end() && tok.compare("main") != 0)
	{
		std::unordered_map<std::string, std::vector<std::string>> value = mergedTbl.at(tok);

		for (auto val : _namespace)
		{
			if (value.find(val) != value.end())
			{
				std::string fileName = value[val].at(1);

				if (_file.compare(fileName) != 0)
				{
					std::vector<std::string> vec;

					if (!mapDepend->count(_file))
					{
						vec.push_back(fileName);
						mapDepend->insert(std::make_pair(_file, vec));
					}
					else
					{
						vec = mapDepend->at(_file);

						if (std::find(vec.begin(), vec.end(), fileName) != vec.end())
							continue;
						mapDepend->at(_file).push_back(fileName);
					}
				}
				else
					break;
			}
		}
	}
}

// -------------------< end conditions for tokenizing the file >-------------------
std::unordered_map<std::string, std::vector<std::string>>* DependencyAnalysis::dependency()
{
	int count = 0;

	while (true)
	{
		std::string token = getToke();

		if (token.compare("namespace") == 0) 
		{
			count++;
			continue;
		}
		if (count > 0) 
		{
			_namespace.push_back(token); 
			count--;
		}
		mergedTbl = _typeTbl->get();

		if (token == "")
			break;
		else
			compare(token);
	}

	return mapDepend;
}

// ----------------< prints the dependencies to console >-----------------
void DependencyAnalysis::showDependency()
{
	for (auto rec : *mapDepend)
	{
		std::cout << rec.first << " is dependant on ";
		for (auto vc : rec.second)
			std::cout << vc << "    ";
		std::cout << "\n";
	}
}

#ifdef TEST_DEP

void main()
{
	std::string file = "E:\Teja\Syracuse University\OOD\Project1";
	std::cout << "Dependencies :" << "\n";
	std::cout << "================" << "\n";

	Toker tok;
	std::fstream in(file);

	if (!in.good())
		std::cout << "\n  can't open file " << file << "\n\n";
	else
	std::cout << "\n  processing file \"" << fileSpec << "\"\n";

	tok.attach(&in);

	DependencyAnalysis dep(&tok, MergedTypeTbl, trimPath(file));
	std::unordered_map<std::string, std::vector<std::string>>* temp;
	temp = dep.dependency();

	dep.showDependency();
}

#endif // TEST_DEP
