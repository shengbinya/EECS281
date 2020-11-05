#include <vector>
#include <iostream>
#include <utility>
#include <unordered_map>
#include <exception>
#include <algorithm>
#include "tableEntry.h"

using namespace std;

/* --- Table and Function Implementations --- */
class Table {

private:
	friend class DataBase;

	//Columns types
	vector<EntryType> m_colTypes;

	//Column names
	vector<string> m_colNames;

	//Actual data in table
	vector<vector<TableEntry>> m_table;

	//Table name
	string m_name;

public:
	//Default Constructor
	Table() : m_name{ "" } {};

	//Constructor
	Table(string t_name, int t_colNum) : m_name{ t_name } {
		m_colTypes.resize(t_colNum);
		m_colNames.resize(t_colNum);
	};

};

/* --- Less Than Functor Class --- */
class LessThan {
private:
	size_t m_colNum;
	TableEntry m_value;

public:
	LessThan(size_t t_colNum, TableEntry t_value) : 
		m_colNum{ t_colNum }, m_value{ t_value } {}

	bool operator()(vector<TableEntry>& t_row) {
		return t_row[m_colNum] < m_value;
	}
};

/* --- Equal to Functor Class --- */
class Equal {
private:
	size_t m_colNum;
	TableEntry m_value;

public:
	Equal(size_t t_colNum, TableEntry t_value) :
		m_colNum{ t_colNum }, m_value{ t_value } {}

	bool operator()(vector<TableEntry>& t_row) {
		return t_row[m_colNum] == m_value;
	}
};

/* --- Greater Than to Functor Class --- */
class GreaterThan {
private:
	size_t m_colNum;
	TableEntry m_value;

public:
	GreaterThan(size_t t_colNum, TableEntry t_value) :
		m_colNum{ t_colNum }, m_value{ t_value } {}

	bool operator()(vector<TableEntry>& t_row) {
		return t_row[m_colNum] > m_value;
	}
};

/* --- DataBase and Function Implementations --- */
class DataBase {
public:
	unordered_map<string, Table*> m_dataBase;
	 
	void addTable();

	void removeTable();

	void insert();

	void deleteFrom();

	void print();

	~DataBase();

};

void DataBase::addTable() {
	
	string name;
	int numCol;
	cin >> name;
	string colNum;
	cin >> colNum;
	numCol = stoi(colNum);

	Table* table  = new Table(name, numCol);
	
	string type;
	for (size_t i = 0; i < table->m_colTypes.size(); ++i) {
		cin >> type;

		if (type == "string")
			table->m_colTypes[i] = EntryType::String;
		else if (type == "double")
			table->m_colTypes[i] = EntryType::Double;
		else if (type == "bool")
			table->m_colTypes[i] = EntryType::Bool;
		else if (type == "int")
			table->m_colTypes[i] = EntryType::Int;
		else
			assert(false);
	}
	
	for (size_t i = 0; i < table->m_colNames.size(); ++i) {
		cin >> name;
		table->m_colNames[i] = name;
	}

	m_dataBase[table->m_name] = table;

	cout << "New table " << table->m_name << " with column(s) ";
	for (auto name : table->m_colNames)
		cout << name << " ";
	cout << "created\n";

}

void DataBase::removeTable() {
	string name;
	cin >> name;
	auto it = m_dataBase.find(name);
	if (it != m_dataBase.end()) {
		delete it->second;
		m_dataBase.erase(it);
		cout << "Table " << name << " deleted\n";
		return;
	}
	throw string{ "2" + name };
}

TableEntry convert(EntryType t_type, string t_value) {
	
	//String
	if (t_type == EntryType::String)
		return TableEntry(t_value);
	
	//Double
	else if (t_type == EntryType::Double) {
		double temp;
		temp = stod(t_value);
		return TableEntry(temp);
	}

	//Int
	else if (t_type == EntryType::Int) {
		int temp;
		temp = stoi(t_value);
		return TableEntry(temp);
	}

	//Boolean
	else {
		if (t_value == "true")
			return TableEntry(true);
		else
			return TableEntry(false);
	}
}

void DataBase::insert() {
	string table;
	cin >> table;
	cin >> table;

	//Checks if the value is in the table
	auto tableCheck = m_dataBase.find(table);
	if (tableCheck == m_dataBase.end())
		throw "2" + table;

	string rowNums;
	int numRows;
	cin >> rowNums;
	numRows = stoi(rowNums);
	cin >> rowNums;
	
	Table* tablePtr = tableCheck->second;
	size_t currRowNum = tablePtr->m_table.size();

	//Reserve extra space in all rows and columns
	tablePtr->m_table.resize(currRowNum + numRows);
	for (auto i : tablePtr->m_table)
		i.reserve(tablePtr->m_colNames.size());

	for (int i = 0; i < numRows; ++i) {
		for (size_t j = 0; j < tablePtr->m_colNames.size(); ++j) {
			string temp;
			cin >> temp;
			tablePtr->m_table[i].push_back(convert(tablePtr->m_colTypes[j], temp));
		}
	}

	cout << "Added " << numRows << " rows to " << table << " from position "
		<< currRowNum << " to " << currRowNum + numRows - 1 << "\n";
	
}

void DataBase::deleteFrom() {
	string table = "";
	string colName = "";
	string op = "";
	string value = "";
	size_t numCol = 0;
	size_t numRows = 0;

	cin >> table;
	cin >> table;
	cin >> colName;
	cin >> colName;
	cin >> op;
	cin >> value;

	//Checks if the value is in the table
	auto tableCheck = m_dataBase.find(table);
	if (tableCheck == m_dataBase.end())
		throw "2" + table;

	Table* tablePtr = tableCheck->second;
	numRows = tablePtr->m_table.size();

	//Checks if the column exists
	auto colIt = find(tablePtr->m_colNames.begin(), tablePtr->m_colNames.end(), colName);

	//If not null then calcuate and push corresponding index
	if (colIt != tablePtr->m_colNames.end())
		numCol =  colIt - tablePtr->m_colNames.begin();
	else
		throw string{ "3" + colName + " " + table };

	auto end = tablePtr->m_table.end();
	if (op == "<")
		end = remove_if(tablePtr->m_table.begin(), tablePtr->m_table.end(), LessThan(numCol, 
			convert(tablePtr->m_colTypes[numCol],value)));
	else if (op == "=")
		end = remove_if(tablePtr->m_table.begin(), tablePtr->m_table.end(), Equal(numCol,
			convert(tablePtr->m_colTypes[numCol], value)));
	else if (op == ">")
		end = remove_if(tablePtr->m_table.begin(), tablePtr->m_table.end(), GreaterThan(numCol,
			convert(tablePtr->m_colTypes[numCol], value)));
	else
		assert(false);

	//Erase deleted elements
	tablePtr->m_table.erase(end, tablePtr->m_table.end());

	cout << "Deleted " << numRows - tablePtr->m_table.size() << " rows from " << table << "\n";
}

void DataBase::print() {
	string table;
	cin >> table;
	cin >> table;

	//Checks if the value is in the table
	auto tableCheck = m_dataBase.find(table);
	if (tableCheck == m_dataBase.end())
		throw string{ "2" + table };

	string colNums;
	int numCols;
	cin >> colNums;
	numCols = stoi(colNums);

	Table* tablePtr = tableCheck->second;

	//Store cols in vector
	vector<pair<string, int>> colNames;
	colNames.reserve(numCols);
	string temp;
	for (int i = 0; i < numCols; ++i) {
		cin >> temp;

		//Find iterator
		auto colIt = find(tablePtr->m_colNames.begin(), tablePtr->m_colNames.end(), temp);

		//If not null then calcuate and push corresponding index
		if (colIt != tablePtr->m_colNames.end())
			colNames.push_back(pair<string, int>{temp, colIt - tablePtr->m_colNames.begin()});
		else
			throw string{ "3" + temp + " " + table };
	}

	//Find index of corresponding cols
	string condition;
	cin >> condition;

	//Print out all specified columns
	for (auto i : colNames) {
		cout << i.first << " ";
	}
	cout << "\n";

	//Print out all data
	if (condition == "ALL") {
		for (size_t row = 0; row < tablePtr->m_table.size(); ++row) {
			for (auto i : colNames)
				cout << tablePtr->m_table[row][i.second] << " ";
			cout << "\n";
		}
		cout << "Printed " << tablePtr->m_table.size() << " matching rows from "
			<< table << "\n";
	}
}

DataBase::~DataBase() {
	for (auto i : m_dataBase)
		delete i.second;
}

int main() {

	ios_base::sync_with_stdio(false);  
	cin >> std::boolalpha;
	cout << std::boolalpha;

	DataBase data;
	string cmd = "";
	bool alreadyPrinted = false;

	while (true) {
		
		cout << "% ";
		cin >> cmd;
		alreadyPrinted = false;
		
		try {
			if (cmd[0] == 'C')
				data.addTable();
			else if (cmd[0] == 'R')
				data.removeTable();
			else if (cmd[0] == 'I')
				data.insert();
			else if (cmd[0] == 'D')
				data.deleteFrom();
			else if (cmd[0] == 'P')
				data.print();
			else if (cmd[0] == 'Q')
				throw 0;
			else if (cmd[0] == '#')
				throw string{ "comment" };
			else
				throw string{ "4" };
		}
		catch (string e) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			
			//Checks for error 1
			if (e[0] == '1')
				cout << "Error: Cannot create already existing table " <<
				e.substr(1, e.size() - 1) << "\n";
			
			//Checks for error 2
			else if (e[0] == '2')
				cout << "Error: " << e.substr(1, e.size() - 1) << 
				" does not name a table in the database\n";
			
			//Checks for error 3
			else if (e[0] == '3') {
				size_t space = e.find(" ");
				if (!alreadyPrinted) {
					cout << "Error: " << e.substr(1, e.size() - space) <<
						" does not name a column in " << e.substr(space + 1, space - 1) << "\n";
					alreadyPrinted = true;
				}
			}

			//Checks for error 4
			else if (e[0] == '4')
				cout << "Error: unrecognized command\n";
		}
		catch (int) {
			cout << "Thanks for being silly!\n";
			return 0;
		}
	}

}