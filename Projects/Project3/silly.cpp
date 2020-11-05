#include <vector>
#include <iostream>
#include <utility>
#include <unordered_map>
#include <exception>
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
		m_table.resize(t_colNum);
	};

};

/* --- DataBase and Function Implementations --- */
class DataBase {
public:
	unordered_map<string, Table*> m_dataBase;
	 
	void addTable();

	void removeTable();

	void insert();

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
	throw string("2" + name);
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
	
	

	size_t currRowNum = m_dataBase[table]->m_table[0].size();
	Table* tablePtr = tableCheck->second;

	//Reserve extra space in all columns
	for (auto i : tablePtr->m_table)
		i.reserve(currRowNum + numRows);

	for (int i = 0; i < numRows; ++i) {
		for (size_t j = 0; j < m_dataBase[table]->m_table.size(); ++j) {
			
			//String
			if (tablePtr->m_colTypes[j] == EntryType::String) {
				string temp;
				cin >> temp;
				tablePtr->m_table[j].push_back(TableEntry(temp));
			}

			//Double
			else if (tablePtr->m_colTypes[j] == EntryType::Double) {
				double temp;
				string tempString;
				cin >> tempString;
				temp = stod(tempString);
				tablePtr->m_table[j].push_back(TableEntry(temp));
			}

			//Int
			else if (tablePtr->m_colTypes[j] == EntryType::Int) {
				int temp;
				string tempString;
				cin >> tempString;
				temp = stoi(tempString);
				tablePtr->m_table[j].push_back(TableEntry(temp));
			}

			//Boolean
			else if (tablePtr->m_colTypes[j] == EntryType::Bool) {
				string in;
				cin >> in;
				if(in == "true")
					tablePtr->m_table[j].push_back(TableEntry(true));
				else
					tablePtr->m_table[j].push_back(TableEntry(false));
			}

			else
				assert(false);

		}
	}

	cout << "Added " << numRows << " rows to " << table << " from position "
		<< currRowNum << " to " << currRowNum + numRows << "\n";
	
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
	

	while (true) {
		
		cout << "% ";
		cin >> cmd;
		
		try {
			if (cmd[0] == 'C')
				data.addTable();
			else if (cmd[0] == 'R')
				data.removeTable();
			else if (cmd[0] == 'I')
				data.insert();
			else if (cmd[0] == 'Q')
				throw 0;
			else if (cmd[0] == '#')
				throw string("comment");
			else
				throw string("4");			
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
				cout << "Error: " << e.substr(1, e.size() - space) <<
				"does not name a column in " << e.substr(space+1, space-1) << "\n";
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