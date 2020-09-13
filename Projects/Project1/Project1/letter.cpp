// Project Identifier: 50EB44D3F029ED934858FFFCEAC3547C68768FC9

#include <vector>
#include <iostream>
#include <algorithm>
#include <getopt.h>
#include <string>    
#include <deque>

using namespace std;

class letterMan{

private:

    //Output Variables
    bool output = false;
    char outputFormat = '\0';
    
    //Start and End Varaibles
    string startWord = "";
    string endWord = "";

public:
    //Reads in input from txt file
    void read_data();

    //Read and Process Command Line Arguments
    void get_options(int argc, char** argv);

    vector<string> dictionary;
    string::size_type size = 0;

};

void letterMan::get_options(int argc, char** argv) {
    int option_index = 0, option = 0;
    
    // Don't display getopt error messages about options
    opterr = false;

    int sqTally = 0;
    bool changeCheck = false;
    bool swapCheck = false;
    bool lengthCheck = false;

    // use getopt to find command line options
    struct option longOpts[] = { { "stack", no_argument, nullptr, 's' },
                                { "queue", no_argument, nullptr, 'q' },
                                { "change", no_argument, nullptr, 'c' },
                                { "swap", no_argument, nullptr, 'p'},
                                { "length", no_argument, nullptr, 'l'},
                                { "output", required_argument, nullptr, 'o'},
                                { "begin", required_argument, nullptr, 'b'},
                                { "end", required_argument, nullptr, 'e'},
                                { "help", no_argument, nullptr, 'h'},
                                { nullptr, 0, nullptr, '\0' } };

    while ((option = getopt_long(argc, argv, "sqcplo:b:e:h", longOpts, &option_index)) != -1) {
        switch (option) {
        case 's':
            sqTally++;
            break;

        case 'q':
            sqTally++;
            break;

        case 'c':
            changeCheck = true;
            break;

        case 'p':
            swapCheck = true;
            break;

        case 'l':
            lengthCheck = true;
            break;
        
        case 'o':
            output = true;
            outputFormat = *optarg;
            break;

        case 'b':
            startWord = optarg;
            break;

        case 'e':
            endWord = optarg;
            break;

        case 'h':
            std::cerr << "This program reads in a dictionary from a file.\n"
                << "It runs takes in an end word as an initial argument\n"
                << "and generates a path from the beginning word to the end \n"
                << "word according to the provided arguemnts."
                << "Usage: \'./letter\n\t[--stack | -s]\n"
                << "\t[--queue | -q]\n"
                << "\t[--change | -c]\n"
                << "\t[--swap | -p]\n"
                << "\t[--length | -l]\n"
                << "\t[--output | -o] (W|M)\n"
                << "\t[--begin | -b] <word>\n"
                << "\t[--end | -e] <word>\n"
                << "\t[--help | -h]\n"
                << "\t<Dictionary File>\'" << std::endl;
            exit(1);
        }
    }

    //Validate Input
    if (sqTally != 1) {
        cerr << "More or less than one -s or -q on command line.\n";
        exit(1);
    }
        
    if (!changeCheck && !swapCheck && !lengthCheck) {
        cerr << "No -c, -l, -s on command line.\n";
        exit(1);
    }

    if (!(outputFormat == 'W' || outputFormat == 'M') && output) {
        cerr << "Output Format not specified.\n";
        exit(1);
    }
    
    if (startWord.empty() || endWord.empty()) {
        cerr << "Start word or end word not specified.\n";
        exit(1);
    }

    if (startWord.size() != endWord.size() && !lengthCheck) {
        cerr << "Cannot modify length. Impossible case.\n";
        exit(1);
    }
}

string reverseString(string in) {
    string reversed = "";
    string::size_type size = in.size();
    for (string::size_type i = 0; i < size; ++i) {
        reversed += in[size - 1 - i];
    }
    return reversed;
}

void letterMan::read_data() {

    char type = '\0';
    cin >> type;

    if (type == 'S') {
        char temp1 = '\0';
        cin >> temp1;
        const char* ptr = &temp1;
        size = atoi(ptr);

        dictionary.reserve(size);
        dictionary.resize(size);

        cin.ignore();
        string temp = "";

        for (string::size_type i = 0; i < size; ++i) {
            
            getline(cin, temp);

            if ("//" == temp.substr(0, 2)) {
                i--;
            }

            else {
                dictionary[i] = temp;
            }
        }
    }

    else {
        char temp1 = '\0';
        cin >> temp1;
        const char* ptr = &temp1;
        size = atoi(ptr);

        dictionary.reserve(size);

        cin.ignore();
        string temp = "";

        string reversal = "&";
        string insert = "[]";
        string swap = "!";
        string twice = "?";
        const string chars = "&[]!?";

        for (string::size_type i = 0; i <= size; ++i) {

            getline(cin, temp);

            if ("//" == temp.substr(0, 2)) {
                i--;
            }
            
            else {
                string::size_type index = temp.find_first_of(chars);
                if (index != std::string::npos) {

                    if (temp[index] == '&') {
                        dictionary.push_back(temp.substr(0, index));
                        dictionary.push_back(reverseString(temp.substr(0,index)));
                    }

                    else if (temp[index] == '[') {
                        string::size_type endIndex = temp.find(']');
                        
                        for (string::size_type i = index+1; i < endIndex; ++i) {
                            dictionary.push_back(temp.substr(0, index)
                                + temp[i] + temp.substr(endIndex + 1, temp.size()));
                        }

                    }

                    else if (temp[index] == '!') {
                        string::size_type size = temp.size();
                        dictionary.push_back(temp.substr(0,index) + 
                             temp.substr(index + 1, size));
                        dictionary.push_back(reverseString(temp.substr(0, index))
                            + temp.substr(index + 1, size));
                    }

                    else if (temp[index] == '?') {
                        string::size_type size = temp.size();
                        dictionary.push_back(temp.substr(0, index) + 
                            temp.substr(index + 1, size));
                        dictionary.push_back(temp.substr(0, index) + temp[index-1]
                            + temp.substr(index + 1, size));
                    }

                }

                else {
                    dictionary.push_back(temp);
                }

            }
        }
    }
}
//Need to check dictionary for start and end word

int main(int argc, char** argv) {

    letterMan man;

    man.get_options(argc, argv);

    man.read_data();

    for (auto i : man.dictionary) {
        cout << i << '\n';
    }

    return 0;
}