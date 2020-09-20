// Project Identifier: 50EB44D3F029ED934858FFFCEAC3547C68768FC9

#include <vector>
#include <iostream>
#include <algorithm>
#include <getopt.h>
#include <string>    
#include <deque>
#include <cmath>

using namespace std;

struct word{
    string wordIn = "";
    string modification = "";
    int discoveredBy = -1;
};

class letterMan{

private:

    //Output Variables
    bool output = false;
    char outputFormat = '\0';
    bool q = false;
    bool s = false;
    bool changeCheck = false;
    bool swapCheck = false;
    bool lengthCheck = false;
    string modification = "";

    //Start and End Varaibles
    string startWord = "";
    string endWord = "";

public:

    //Variables
    vector<string> dictionary;
    string::size_type size = 0;

    vector<word> discard;
    int sizeD = 0;
    
    deque<word> queue;
    int sizeQ = 0;
    
    word currentWord;

    //Reads in input from txt file
    void read_data();

    //Read and Process Command Line Arguments
    void get_options(int argc, char** argv);

    //Finds the path that Letterman should take
    bool find_path();

    //Compares a word to see if it can be marked as discovered
    bool compare(string current, string reviewed);

    //Writes data to cout
    void write_data();

};

void letterMan::get_options(int argc, char** argv) {
    int option_index = 0, option = 0;
    
    // Don't display getopt error messages about options
    opterr = false;

    int sqTally = 0;

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
            s = true;
            break;

        case 'q':
            sqTally++;
            q = true;
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

bool letterMan::compare(string current, string reviewed) {
    
    string::size_type currentSize = current.size();
    string::size_type reviewedSize = reviewed.size();
    
    //Check if differ by two letters
    if (reviewedSize - currentSize > 1)
        return false;

    //Check if differ by length when we can't change length
    if (currentSize != reviewedSize && !lengthCheck)
        return false;

    //Check if can obtain word by adding or subtracting a letter
    if (currentSize != reviewedSize && lengthCheck) {
        
        string::size_type i = 0;
        string::size_type j = 0;
        string::size_type index = 300;

        while (i < currentSize) {
            if (current[i] != reviewed[j]) {
                if (current[i + 1] == reviewed[j]) {
                    if (index == 300) {
                        index = i;
                        modification = "d," + to_string(index);
                    }
                    ++i;
                }
                else if (current[i] == reviewed[j + 1]) {
                    if (index == 300) {
                        index = i;
                        modification = "i," + to_string(index) + reviewed[j];
                    }
                    ++j;
                }
                else
                    return false;
            }

            ++i;
            ++j;
        }
        if (index != 300)
            return true;
    }

    //Check if can obtain word by changing one letter
    if (currentSize == reviewedSize && changeCheck) {
        
        string::size_type index = 300;
        
        for (string::size_type i = 0; i < currentSize; ++i) {
            if (current[i] != reviewed[i]) {
                if (index != 300)
                    return false;
                else
                    index = i;
            }
                
        }
        if (index != 300){
            modification = "c," + to_string(index) + "," + reviewed[index];
            return true;
        }  
       
    }
    
    //Check if can obtain word by swapping two letter
    if (currentSize == reviewedSize && swapCheck) {
        
        string::size_type index = 300;

        for (string::size_type i = 0; i < currentSize - 1; ++i) {
            if (current.substr(i, i + 2) == reverseString(reviewed.substr(i, i + 2))) {

                if (index != 300)
                    return false;
                else
                    index = i;

            }
                
        }
        if (index != 300) {
            modification = "s," + to_string(index);
            return true;
        }
    }
    
    return false;
}

bool letterMan::find_path() {
   

    //Do I really need this?
    word start;
    start.wordIn = startWord;
    queue.push_back(start);
    sizeQ++;
    queue.pop_front();
    sizeQ--;

    currentWord.wordIn = startWord;

    //Discover Start Word
    for (string::size_type i = 0; i < size; ++i) {
        if (dictionary.at(i) == startWord) {
            dictionary.at(i).insert(0, "#");
            break;
        }
    }

    do {

        //After discovering all words for a particular word
        if (sizeQ > 0) {

            //Add to discard
            discard.push_back(currentWord);
            sizeD++;

            if (q) {

                //Grab and remove top of queue
                currentWord = queue.at(0);
                queue.pop_front();
                sizeQ--;

            }

        }

        for (string::size_type i = 0; i < size; ++i) {
            //Check if word has been discovered already
            cerr << i << "\n";
            cerr << "Considered: " << dictionary.size() << "\n";
            if (dictionary.at(i).at(0) == '#') {}

            else {
                if (compare(currentWord.wordIn, dictionary.at(i))) {
                    
                    //Create word object
                    word temp;
                    temp.modification = modification;
                    temp.wordIn = dictionary.at(i);
                    temp.discoveredBy = sizeD;

                    //End Case
                    if (endWord == dictionary.at(i)) {
                        
                        discard.push_back(currentWord);
                        discard.push_back(temp);
                        sizeD += 2;
                        return true;
                    
                    }

                    //If a queue push it to the back
                    if (q) {
                        queue.push_back(temp);
                        sizeQ++;
                    }
                    
                    //Add character to denote as discovered
                    dictionary.at(i).insert(0, "#");
                }
            }
        }
            
     
    } while (sizeQ > 0);
    return false;
}

void letterMan::write_data() {
    
    currentWord = discard.at(sizeD-1);
    vector<word> solution;

    while (currentWord.discoveredBy != -1) {
        
        solution.push_back(currentWord);
        currentWord = discard.at(currentWord.discoveredBy);

    }
    
    solution.push_back(currentWord);
    int sizeS = static_cast<int>(solution.size());
    
    cout << "Words in Morph: " << to_string(sizeS) << "\n";
    cout << discard.at(sizeS - 1).wordIn << "\n";
    
    for (int i = sizeS - 2; i >= 0; --i) {
        
        if (outputFormat == 'W')
            cout << discard.at(i).wordIn << "\n";
        else
            cout << discard.at(i).modification << "\n";

    }
}

//Need to check dictionary for start and end word

int main(int argc, char** argv) {

    letterMan man;

    man.get_options(argc, argv);

    man.read_data();
    cerr << "Data Read\n";
    if (man.find_path())
        man.write_data();
    else
        cout << "No solution, " << to_string(man.sizeD + 1) << " words discovered.\n";

    return 0;
}