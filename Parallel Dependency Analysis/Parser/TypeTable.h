#ifndef TYPETBL
#define TYPETBL

#pragma warning(disable : 4503)

///////////////////////////////////////////////////////////////////////
// TypeTable.h - Table to store the type details of variables		 //
///////////////////////////////////////////////////////////////////////	
// ver 1.0															 //
// Application:  Parallel Dependency, CSE687 - Object Oriented Design//
// Author:		  Teja Thunuguntla, Syracuse University				 //
//				  tthunugu@syr.edu									 //
///////////////////////////////////////////////////////////////////////
/*
Module Operations:
==================
* Record is a map containing name, namespace, type and filename
* Table is a set of records. Provide methods to add records to the table
* and print them to the console.

Public Interface:
=================
* Record()		- creates a new type table record
* showRecord()	- prints a record to the console
* recordMerge()	- merges two records to one
* addRecord()	- adds a record to the type table
* get()			- returns type table records
* merge()		- merges the type table
* showTypeTable()- prints the table to the console

Build Process:
==============
Required files
- 

Build commands:
===============
- devenv project3.sln

Maintenance History:
====================
ver 1.0 : 06 Apr 16
- first release

*/

#include <iostream>
#include <iomanip>
#include <string>
#include <unordered_map>

class TypeTableRecord
{
	using rec =	std::unordered_map<std::string, std::vector<std::string>>;
	using Element =	std::vector<std::string> ;

public:
	rec Record(std::string _namespace, std::string _type, std::string _whereDefined)
	{
		rec record1;
		Element _vector;
		_vector.push_back(_type);
		_vector.push_back(_whereDefined);
		record1[_namespace] = _vector;
		return record1;
	}
	void showRecord(rec _record)
	{
		int count = 0;

		for (auto iterator = _record.begin(); iterator != _record.end(); ++iterator)
		{
			if (count > 0)
				std::cout << std::cout.width(20) <<" " << std::setw(20) << iterator->first;
			else
				std::cout << std::setw(20) << iterator->first;

			std::cout << std::setw(15) << iterator->second.at(0);
			std::cout << std::setw(20) << iterator->second.at(1);
			std::cout << "\n";
			count++;
		}
	}
	rec recordMerge(rec record1, rec record2)
	{
		for (auto iterator = record2.begin(); iterator != record2.end(); ++iterator)
		{
			record1[iterator->first] = iterator->second;
		}
		return record1;
	}
private:
};

class TypeTable
{
	typedef	std::unordered_map<std::string, std::vector<std::string>> recrd;

public:
// ------------< adds records to the type table >--------------
	void addRecord(std::string _name, recrd record)
	{
		if (_records.find(_name) == _records.end())
		{
			_records[_name] = record;
		}
		else
		{
			recrd recordOld = _records[_name];
			recordOld = typeTableRecord.recordMerge(recordOld, record);
			_records[_name] = recordOld;
		}
	}

// ------------< returns the table records >--------------- 
	std::unordered_map<std::string, recrd> get()
	{
		return _records;
	}

// ------------< merge the type tables >---------------
	void merge(std::unordered_map<std::string, recrd> _recordsNew)
	{
		for (auto iterator = _recordsNew.begin(); iterator != _recordsNew.end(); ++iterator)
		{
			if (_records.find(iterator->first) == _records.end())
			{
				_records[iterator->first] = iterator->second;
			}
			else
			{
				recrd recordOld = _records[iterator->first];
				recordOld = typeTableRecord.recordMerge(recordOld, iterator->second);
				_records[iterator->first] = recordOld;
			}
		}
		return;
	}
// ------------< prints the type table to console >--------------
	void showTypeTable()
	{
		showRecordHeader();
		std::cout << "\n";
		for (auto it = _records.begin(); it != _records.end(); ++it)
		{
			std::cout << " " << std::setw(20) << it->first;
			typeTableRecord.showRecord(it->second);
		}
	}
private:
	std::unordered_map<std::string, recrd> _records;
	TypeTableRecord typeTableRecord;

	void showRecordHeader()
	{
		std::cout << std::left << "\n  ";
		std::cout << std::setw(20) << "Name";
		std::cout << std::setw(20) << "Namespace";
		std::cout << std::setw(15) << "Type";
		std::cout << std::setw(20) << "File" << "\n";
		std::cout << " " << std::setw(20) << std::string(10, '-');
		std::cout << std::setw(20) << std::string(12, '-');
		std::cout << std::setw(15) << std::string(10, '-');
		std::cout << std::setw(20) << std::string(14, '-');
	}
};

#endif // !TYPETBL