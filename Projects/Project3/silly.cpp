#include <vector>
#include <iostream>
#include <utility>
#include <unordered_map>
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
		m_table.reserve(t_colNum);
	};

};

/* --- DataBase and Function Implementations --- */
class DataBase {
public:
	unordered_map<string, Table*> m_dataBase;
	 
	~DataBase();

	void addTable();
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

DataBase::~DataBase() {
	for (auto i : m_dataBase)
		delete i.second;
}

int main() {
	ios_base::sync_with_stdio(false);   // you should already have this    
	cin >> std::boolalpha;  // add these two lines    
	cout << std::boolalpha;

	DataBase data;
	bool quit = false;
	string cmd = "";
	
	while (!quit) {
		
		cout << "%";
		cin >> cmd;
		
		if (cmd == "CREATE") {
			data.addTable();	
		}
		else if (cmd == "QUIT") {
			return 0;
		}

	}

}