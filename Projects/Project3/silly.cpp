//Project Identifier: C0F4DFE8B340D81183C208F70F9D2D797908754D
#include <vector>
#include <iostream>
#include <utility>
#include <map>
#include <unordered_map>
#include <exception>
#include <algorithm>
#include "getopt.h"
#include "TableEntry.h"

using namespace std;

/* --- Table and Function Implementations --- */
class Table {

private:
	friend class DataBase;

	//Actual data in table
	vector<vector<TableEntry>> m_table;

	//Column names
	unordered_map<string, size_t> m_colNames;

	//Columns types
	vector<EntryType> m_colTypes;

	//BST for quick indexing
	map<TableEntry, vector<size_t>> m_bst;

	//Hash table for quick indexing
	unordered_map<TableEntry, vector<size_t>> m_hash;

	//Table name
	string m_name;

	//Indexed Column Name
	string m_indexedName;

	//Indexed column number
	size_t m_indexedNum;

	//Type of indexed col
	string m_indexType;

public:
	//Default Constructor
	Table() : m_name{ "" } {};

	//Constructor
	Table(string t_name, int t_colNum) : m_name{ t_name }, 
		m_indexedName{ "" }, m_indexedNum{ 0 }, m_indexType{ "" } {
		m_colTypes.resize(t_colNum);
		m_colNames.reserve(t_colNum * 2);
	};

	void printTable(bool);

	size_t colCheck(const string& t_col);

	template <class ForwardIterator>
	int printRange(ForwardIterator t_first, ForwardIterator t_last,
		vector<pair<string, int>>& t_printCols, bool q);

	void insertTable();

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

	bool operator()(const TableEntry& t_entry) {
		return t_entry < m_value;
	}

	bool operator()(pair<const TableEntry, int>& t_pair) {
		return t_pair.first < m_value;
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

	bool operator()(const TableEntry& t_entry) {
		return t_entry == m_value;
	}

	bool operator()(pair<const TableEntry, int>& t_pair) {
		return t_pair.first == m_value;
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

	bool operator()(const TableEntry& t_entry) {
		return t_entry > m_value;
	}

	bool operator()(pair<const TableEntry, int>& t_pair) {
		return t_pair.first > m_value;
	}
};

/* --- Helper Functions --- */
TableEntry convert(EntryType& t_type, const string& t_value) {

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

template <class ForwardIterator, class Compare>
int printIf(ForwardIterator t_first, ForwardIterator t_last, Compare t_pred,
	vector<pair<string, int>>& t_printCols, bool q) {
	int prints = 0;
	while (t_first != t_last) {
		if (t_pred(*t_first)) {
			if (!q) {
				for (auto it : t_printCols) {
					cout << t_first->at(it.second) << " ";
				}
				cout << "\n";
			}
			++prints;
		}
		t_first++;
	}
	return prints;
}

size_t Table::colCheck(const string& t_col) {
	// Checks if the column exists
	auto colIt = m_colNames.find(t_col);

	//If not null then calcuate and push corresponding index
	if (colIt != m_colNames.end())
		return colIt->second;
	else
		throw string{ "3" + t_col + " " + m_name };
}

template <class ForwardIterator>
int Table::printRange(ForwardIterator t_first, ForwardIterator t_last,
	vector<pair<string, int>>& t_printCols, bool q) {
	int prints = 0;

	//Iterate through range
	while (t_first != t_last) {
		if (!q) {
			//Go through vector in range
			for (auto i : t_first->second) {

				//Print out appropriate columns
				for (auto it : t_printCols) {

					cout << m_table[i][it.second] << " ";
				}

				cout << "\n";
				prints++;
			}
		}
		else {
			prints += int(t_first->second.size());
		}
		t_first++;
	}

	return prints;
}

/* --- Table Main Function Implementations --- */
void Table::printTable(bool q) {
	string colNums;
	int numCols;
	cin >> colNums;
	numCols = stoi(colNums);

	//Store cols in vector
	vector<pair<string, int>> colNames;
	colNames.reserve(numCols);
	string temp;
	for (int i = 0; i < numCols; ++i) {
		cin >> temp;

		//Check if column exists and if so push back colNum
		colNames.push_back(pair<string, int>{temp, colCheck(temp)});
	}

	//Find index of corresponding cols
	string condition;
	cin >> condition;

	//Print out all specified columns
	for (auto i : colNames) {
		if (!q)
			cout << i.first << " ";
	}
	if (!q)
		cout << "\n";

	//Print out all data
	if (condition == "ALL") {
		if (!q) {
			for (size_t row = 0; row < m_table.size(); ++row) {
				for (auto i : colNames)
					cout << m_table[row][i.second] << " ";
				cout << "\n";
			}
		}
		cout << "Printed " << m_table.size() << " matching rows from "
			<< m_name << "\n";
	}

	else if (condition == "WHERE") {
		string colName;
		string op;
		string value;
		size_t numCol;
		cin >> colName;
		cin >> op;
		cin >> value;

		//Checks if the column exists
		numCol = colCheck(colName);

		int prints = 0;
		if (op == "<") {
			//If an index exists that's the same name as column
			if (colName == m_indexedName && m_indexType == "bst") {
				TableEntry val = convert(m_colTypes[numCol], value);
				auto endIt = m_bst.lower_bound(val);
				prints = printRange(m_bst.begin(), endIt, colNames, q);
			}

			else
				prints = printIf(m_table.begin(), m_table.end(), LessThan(numCol,
					convert(m_colTypes[numCol], value)), colNames, q);
		}

		else if (op == "=") {
			//If an index exists that's the same name as column BST
			if (colName == m_indexedName && m_indexType == "bst") {
				TableEntry val = convert(m_colTypes[numCol], value);
				auto rowIt = m_bst.find(val);
				if (rowIt != m_bst.end()) {
					for (auto k : rowIt->second) {
						if (!q) {
							for (auto colIt : colNames) {
								cout << m_table[k][colIt.second] << " ";
							}
							cout << "\n";
						}
						prints++;
					}
				}

			}
			//If an index exists that's the same as hash
			else if (colName == m_indexedName && m_indexType == "hash") {
				TableEntry val = convert(m_colTypes[numCol], value);
				auto rowIt = m_hash.find(val);
				if (rowIt != m_hash.end()) {
					for (auto k : rowIt->second) {
						if (!q) {
							for (auto colIt : colNames) {
								cout << m_table[k][colIt.second] << " ";
							}
							cout << "\n";
						}
						prints++;
					}
				}
			}
			else
				prints = printIf(m_table.begin(), m_table.end(), Equal(numCol,
					convert(m_colTypes[numCol], value)), colNames, q);
		}

		else {
			//If an index exists that's the same name as column
			if (colName == m_indexedName && m_indexType == "bst") {
				TableEntry val = convert(m_colTypes[numCol], value);
				auto beginIt = m_bst.upper_bound(val);
				prints = printRange(beginIt, m_bst.end(), colNames, q);
			}
			else
				prints = printIf(m_table.begin(), m_table.end(), GreaterThan(numCol,
					convert(m_colTypes[numCol], value)), colNames, q);
		}

		cout << "Printed " << prints << " matching rows from " << m_name << "\n";
	}
}

void Table::insertTable() {
	string rowNums;
	int numRows;
	cin >> rowNums;
	numRows = stoi(rowNums);
	cin >> rowNums;

	size_t currRowNum = m_table.size();

	//Reserve extra space in all rows and columns
	m_table.resize(currRowNum + numRows);
	for (auto i : m_table)
		i.reserve(m_colNames.size());

	//If no BST or Hash Table
	if (m_indexedName.empty()) {
		for (size_t i = currRowNum; i < numRows + currRowNum; ++i) {
			for (size_t j = 0; j < m_colNames.size(); ++j) {
				string temp;
				cin >> temp;
				m_table[i].emplace_back(convert(m_colTypes[j], temp));
			}
		}
	}
	//Update the BST or Hash Table
	else {
		for (size_t i = currRowNum; i < numRows + currRowNum; ++i) {
			for (size_t j = 0; j < m_colNames.size(); ++j) {
				string temp;
				cin >> temp;
				m_table[i].emplace_back(convert(m_colTypes[j], temp));

			}
			//Add element to binary search tree
			if (m_indexType == "bst") {
				m_bst[m_table[i][m_indexedNum]].push_back(i);
			}
			//Add element to hash table
			else {
				m_hash[m_table[i][m_indexedNum]].push_back(i);
			}
		}
	}


	cout << "Added " << numRows << " rows to " << m_name << " from position "
		<< currRowNum << " to " << currRowNum + numRows - 1 << "\n";
}


/* --- DataBase and Function Implementations --- */
class DataBase {
	bool q = false;

public:
	unordered_map<string, Table*> m_dataBase;
	 
	void getOptions(int, char**);

	void addTable();

	void removeTable();

	void insert();

	void deleteFrom();

	void generateIndex();

	void updateIndex(const string&, const string&, const size_t&, Table*);

	void join();

	void print();

	~DataBase();

	Table* tableCheck(const string& t_table);

	size_t colCheck(const string& t_col, Table*);

};



Table* DataBase::tableCheck(const string& t_table) {
	//Checks if the table is in the database
	auto tableCheck = m_dataBase.find(t_table);
	if (tableCheck == m_dataBase.end())
		throw "2" + t_table;

	return tableCheck->second;
}

size_t DataBase::colCheck(const string& t_col, Table* t_tablePtr) {
	// Checks if the column exists
	auto colIt = t_tablePtr->m_colNames.find(t_col);

	//If not null then calcuate and push corresponding index
	if (colIt != t_tablePtr->m_colNames.end())
		return colIt->second;
	else
		throw string{ "3" + t_col + " " + t_tablePtr->m_name };
}

/* --- Main Functions --- */
void DataBase::getOptions(int argc, char** argv) {
	int option_index = 0, option = 0;

	// Don't display getopt error messages about options
	opterr = false;

	// use getopt to find command line options
	struct option longOpts[] = {{ "quiet", no_argument, nullptr, 'q' },
								{ "help", no_argument, nullptr, 'h'},
								{ nullptr, 0, nullptr, '\0' } };

	while ((option = getopt_long(argc, argv, "qh", longOpts, &option_index)) != -1) {
		switch (option) {
		case 'q':
			q = true;
			break;

		case 'h':
			cout << "This program reads in user input from command line and performs"
				<< "operations on a table based on the user input\n"
				<< "Usage: \'./letter\n\t[--quiet | -q]\n"
				<< "\t[--help | -h]\n";
			exit(1);
		}
	}
}

void DataBase::addTable() {
	
	string name;
	int numCol;
	cin >> name;
	string colNum;
	cin >> colNum;
	numCol = stoi(colNum);

	//Make sure no preexisting table
	if (m_dataBase.find(name) != m_dataBase.end())
		throw string{ "1" + name };

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
	
	//Populate the column names of the table
	vector<string> tempPrintVec(numCol);
	for (size_t i = 0; i < size_t(numCol); ++i) {
		cin >> name;
		table->m_colNames[name] = i;
		tempPrintVec[i] = name;
	}

	m_dataBase[table->m_name] = table;

	cout << "New table " << table->m_name << " with column(s) ";
	for (auto name : tempPrintVec)
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

void DataBase::insert() {
	string table;
	cin >> table;
	cin >> table;

	Table* tablePtr = tableCheck(table);

	tablePtr->insertTable();
}

void DataBase::updateIndex(const string& t_colName, const string& t_type,
	const size_t& t_numCol, Table* t_tablePtr) {

	//Clear current indices if they are full
	if (!t_tablePtr->m_hash.empty())
		t_tablePtr->m_hash.clear();
	else if (!t_tablePtr->m_bst.empty())
		t_tablePtr->m_bst.clear();

	//If type is BST
	if (t_type == "bst") {
		//Populate BST with all values in column
		for (size_t i = 0; i < t_tablePtr->m_table.size(); ++i) {
			t_tablePtr->m_bst[t_tablePtr->m_table[i][t_numCol]].push_back(i);
		}
	}
	else if (t_type == "hash") {
		//Populate hash with all values in column
		t_tablePtr->m_hash.reserve(t_tablePtr->m_table.size());
		for (size_t i = 0; i < t_tablePtr->m_table.size(); ++i) {
			t_tablePtr->m_hash[t_tablePtr->m_table[i][t_numCol]].push_back(i);
		}
	}

	t_tablePtr->m_indexedName = t_colName;
	t_tablePtr->m_indexType = t_type;
	t_tablePtr->m_indexedNum = t_numCol;
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

	Table* tablePtr = tableCheck(table);
	numRows = tablePtr->m_table.size();

	numCol = colCheck(colName, tablePtr);

	auto end = tablePtr->m_table.end();

	if (op == "<")
		end = remove_if(tablePtr->m_table.begin(), tablePtr->m_table.end(), LessThan(numCol, 
			convert(tablePtr->m_colTypes[numCol], value)));
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

	updateIndex(tablePtr->m_indexedName, tablePtr->m_indexType, tablePtr->m_indexedNum, tablePtr);

	cout << "Deleted " << numRows - tablePtr->m_table.size() << " rows from " << table << "\n";
}

void DataBase::generateIndex() {
	string table = "";
	string colName = "";
	string type = "";
	string value = "";
	size_t numCol = 0;

	cin >> table;
	cin >> table;
	cin >> type;
	cin >> colName;
	cin >> colName;
	cin >> colName;

	//Checks if the table is in the database
	Table* tablePtr = DataBase::tableCheck(table);

	//Checks if the column exists
	numCol = colCheck(colName, tablePtr);

	updateIndex(colName, type, numCol, tablePtr);

	cout << "Created " << type << " index for table "
		<< table << " on column " << colName << "\n";
}

void DataBase::join() {
	string table1 = "";
	string table2 = "";
	string compCol1 = "";
	string compCol2 = "";
	string garbage = "";
	size_t numCol1 = 0;
	size_t numCol2 = 0;
	int numCols = 0;

	cin >> table1;

	Table* tablePtr1 = tableCheck(table1);

	cin >> table2;
	cin >> table2;

	Table* tablePtr2 = tableCheck(table2);

	cin >> garbage;
	cin >> compCol1;

	numCol1 = colCheck(compCol1, tablePtr1);

	cin >> garbage;
	cin >> compCol2;

	numCol2 = colCheck(compCol2, tablePtr2);

	cin >> garbage;
	cin >> garbage;
	cin >> garbage;

	numCols = stoi(garbage);
	
	//First int is table and second int is col Index
	vector<pair<int, string>> colNames;
	string temp = "";
	colNames.reserve(numCols);

	//Extract and store column information from cmd line
	for (int i = 0; i < numCols; ++i) {
		int numTable = 0;
		cin >> temp;
		cin >> garbage;
		numTable = stoi(garbage);
		
		//Create vector of tables and corresponding column number
		if (numTable == 1) {
			colCheck(temp, tablePtr1);
			colNames.push_back(pair<int, string>{1, temp});
		}
		else {
			colCheck(temp, tablePtr2);
			colNames.push_back(pair<int, string>{2, temp});
		}	
	}
	if (!q) {
		for (auto i : colNames) {
			cout << i.second << " ";
		}
		cout << "\n";
	}

	int printed = 0;

	//Check if table 2 has bst
	if (tablePtr2->m_indexedNum == numCol2 && tablePtr2->m_indexedName == compCol2
		&& tablePtr2->m_indexType == "bst") {
		//Itterate through first table beginning to end
		for (auto i : tablePtr1->m_table) {
			//If we have found a matching row in table 2
			auto it = tablePtr2->m_bst.find(i[numCol1]);
			if (it != tablePtr2->m_bst.end()) {
				for (auto k : it->second) {
					if (!q) {
						//Loop through column names to print and print them out
						for (auto j : colNames) {
							if (j.first == 1)
								cout << i[tablePtr1->m_colNames[j.second]] << " ";
							else
								cout << tablePtr2->m_table[k][tablePtr2->m_colNames[j.second]] << " ";
						}
						cout << "\n";
					}
					printed++;
				}
			}
		}
	}

	//Check if table 2 has hash table
	else if (tablePtr2->m_indexedNum == numCol2 && tablePtr2->m_indexedName == compCol2
		&& tablePtr2->m_indexType == "hash") {
		//Itterate through first table beginning to end
		for (auto i : tablePtr1->m_table) {
			//If we have found a matching row in table 2
			auto it = tablePtr2->m_hash.find(i[numCol1]);
			if (it != tablePtr2->m_hash.end()) {
				for (auto k : it->second) {
					if (!q) {
						//Loop through column names to print and print them out
						for (auto j : colNames) {
							if (j.first == 1)
								cout << i[tablePtr1->m_colNames[j.second]] << " ";
							else
								cout << tablePtr2->m_table[k][tablePtr2->m_colNames[j.second]] << " ";
						}
						cout << "\n";
					}
					printed++;
				}
			}
		}
	}

	//If there is no hash table create one
	else {
		unordered_map<TableEntry, vector<size_t>> hash(tablePtr2->m_table.size()*2);
		for (size_t i = 0; i < tablePtr2->m_table.size(); ++i) {
			hash[tablePtr2->m_table[i][numCol2]].push_back(i);
		}
		for (auto i : tablePtr1->m_table) {
			//If we have found a matching row in table 2
			auto it = hash.find(i[numCol1]);
			if (it != hash.end()) {
				for (auto k : it->second) {
					if (!q) {
						//Loop through column names to print and print them out
						for (auto j : colNames) {
							if (j.first == 1)
								cout << i[tablePtr1->m_colNames[j.second]] << " ";
							else
								cout << tablePtr2->m_table[k][tablePtr2->m_colNames[j.second]] << " ";
						}
						cout << "\n";
					}
					printed++;
				}
			}
		}
		
	}
	
	cout << "Printed " << printed << " rows from joining " << table1 << " to " << table2 << "\n";
}

void DataBase::print() {
	string table;
	cin >> table;
	cin >> table;

	Table* tablePtr = tableCheck(table);

	tablePtr->printTable(q);

}

DataBase::~DataBase() {
	for (auto i : m_dataBase)
		delete i.second;
}

int main(int argc, char** argv) {

	ios_base::sync_with_stdio(false);  
	cin >> std::boolalpha;
	cout << std::boolalpha;

	DataBase data;
	data.getOptions(argc, argv);
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
			else if (cmd[0] == 'G')
				data.generateIndex();
			else if (cmd[0] == 'J')
				data.join();
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