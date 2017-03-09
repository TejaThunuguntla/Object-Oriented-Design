#include "TypeTable.h"

///////////////////////////////////////////////////////////////////////
// TypeTable.h - Table to store the type details of variables		 //
///////////////////////////////////////////////////////////////////////																	 //
// ver 1.0															 //
// Application:  Parallel Dependency, CSE687 - Object Oriented Design//
// Author:		  Teja Thunuguntla, Syracuse University				 //
//				  tthunugu@syr.edu									 //
///////////////////////////////////////////////////////////////////////

#ifdef TEST_TYPETBL

void main()
{
	Utils::Title("MT4Q1 - TypeTable");
	putline();

	TypeTable<TypeTableRecord> table;

	TypeTableRecord record;
	record.name() = "X";
	record.type() = "class";
	record.fileName() = "X.h";
	record.addNameSpace("TypeAnalysis");
	record.addNameSpace("MT4");

	table.addRecord(record);

	record.name() = "fun";
	record.type() = "method";
	record.fileName() = "X.h";
	record.addNameSpace("TypeAnalysis");
	record.addNameSpace("MT4");

	table.addRecord(record);

	showTypeTable(table);
	std::cout << "\n\n";
}

#endif // TEST_TYPETBL