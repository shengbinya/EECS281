// Project Identifier: 50EB44D3F029ED934858FFFCEAC3547C68768FC9

#include <vector>
#include <iostream>
#include <algorithm>
#include <getopt.h>
#include <string>    
#include <deque>
#include <cmath>
#include <chrono>

using namespace std;

struct word {
    string wordIn = "";
    string modification = "";
    int discoveredBy = -1;
};

class letterMan {

private:

    //Output Variables
    bool output = false;
    bool begin = true;
    bool end = true;
    char outputFormat = '\0';
    bool q = false;
    bool s = false;
    bool changeCheck = false;
    bool swapCheck = false;
    bool lengthCheck = false;
    string modification = "";
    


    //Start and End Varaibles
    string startWord = "";
    size_t startLen = 0;
    string endWord = "";
    

public:
    string sortedStart = "";
    bool startExist = false;
    bool endExist = false;

    //Variables
    vector<string> dictionary;
    std::size_t size = 0;

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

    bool checkLetters(string);

    bool checkWord(string &);

    bool checkEnds(string temp);
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
            if (startWord.substr(0, 1) != "-") {
                startLen = startWord.size();
                sortedStart = startWord;
                sort(sortedStart.begin(), sortedStart.end());
                break;
            }
            else {
                begin = false;
                break;
            }
            break;

        case 'e':
            endWord = optarg;
            if (endWord.substr(0, 1) != "-") {
                break;
            }
            else {
                end = false;
                break;
            }
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
       
    if (!begin) {
        cerr << "No begin word specified.\n";
        exit(1);
    }

    if (!end) {
        cerr << "No end word specified.\n";
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

    if (startWord == endWord) {
        cerr << "Words in morph: 1\n";
        cerr << startWord << "\n";
        exit(0);
    }
}

string reverseString(string in) {
    string reversed = "";
    std::size_t size = in.size();
    for (std::size_t i = 0; i < size; ++i) {
        reversed += in[size - 1 - i];
    }
    return reversed;
}

bool letterMan::checkLetters(string check) {
    sort(check.begin(), check.end());
    return sortedStart == check;    
}

bool letterMan::checkWord(string &temp) {
    //Check if word even needs adding to the dictionary
    if (!lengthCheck) {

        if (startLen != temp.size()) {
            return false;
        }

        else if (!changeCheck) {
            if (checkLetters(temp))
                return true;
            else
                return false;
        }

        else {
            return true;
        }
    }

    return true;
}

bool letterMan::checkEnds(string temp) {
    if (temp == startWord) {
        startExist = true;
        return true;
    }
    else if (temp == endWord)
        endExist = true;
    return false;
}

void letterMan::read_data() {

    char type = '\0';
    cin >> type;

    if (type == 'S') {
        string temp1 = "";
        cin >> temp1;
        const char* temp2 = { temp1.c_str() };
        size = atoi(temp2);

        dictionary.reserve(size);

        cin.ignore();

        string temp = "";

        for (std::size_t i = 0; i < size; ++i) {
            
            getline(cin, temp);
         
            if ("//" == temp.substr(0, 2)) {
                --i;
            }

            else if (temp.size() == 0) {
                --i;
            }

            else{
              
                //Check for carriage returns after reading in
                if (int(temp.at(temp.size() - 1)) ==  13)
                    temp = temp.substr(0, temp.size() - 1);
                if (checkWord(temp)) {
                    if (!checkEnds(temp)) {
                        dictionary.push_back(temp);
                    }
                }
            }
        }
    }

    else {
        string temp1 = "";
        cin >> temp1;
        const char* temp2 = { temp1.c_str() };
        size = atoi(temp2);

        dictionary.reserve(size);

        cin.ignore();
        string temp = "";

        string reversal = "&";
        string insert = "[]";
        string swap = "!";
        string twice = "?";
        const string chars = "&[]!?";

        for (std::size_t j = 0; j < size; ++j) {

            getline(cin, temp);

            if ("//" == temp.substr(0, 2) || temp.empty()) {
                size++;
            }
            
            else {
                if (int(temp.at(temp.size() - 1)) == 13)
                    temp = temp.substr(0, temp.size() - 1);

                std::size_t index = temp.find_first_of(chars);
                if (index != std::string::npos) {

                    if (temp[index] == '&') {
                        string temp1 = temp.substr(0, index);
                        if (checkWord(temp1)) {
                            if (!checkEnds(temp1)) {
                                dictionary.push_back(temp1);
                            }
                            string t = reverseString(temp1);
                            if (!checkEnds(t)) {
                                dictionary.push_back(t);
                            }
                        }
                        
                    }

                    else if (temp[index] == '[') {
                        std::size_t endIndex = temp.find(']');

                        for (std::size_t i = index + 1; i < endIndex; ++i) {
                            string temp1 = temp.substr(0, index) + temp[i] + temp.substr(endIndex + 1, temp.size()-endIndex-1);
                            if (checkWord(temp1)) {
                                if (!checkEnds(temp1)) {
                                    dictionary.push_back(temp1);
                                }
                            }
                        }

                    }

                    else if (temp[index] == '!') {
                        std::size_t size = temp.size();
                        string temp1 = temp.substr(0, index) + temp.substr(index + 1, size-index-1);
                        if (checkWord(temp1)) {
                            if (!checkEnds(temp1)) {
                                dictionary.push_back(temp1);
                            }
                            string t = temp.substr(0, index - 2) + reverseString(temp.substr(index - 2, 2))
                                + temp.substr(index + 1, size - index - 1);
                            if (!checkEnds(t)) {
                                dictionary.push_back(t);
                            }
                        }
  
                    }

                    else if (temp[index] == '?') {
                        std::size_t size = temp.size();
                        string temp1 = temp.substr(0, index) + temp.substr(index + 1, size - index - 1);
                        string temp2 = temp.substr(0, index) + temp[index - 1] + temp.substr(index + 1, size - index - 1);
                        if (checkWord(temp1)) {
                            if (!checkEnds(temp1)) {
                                dictionary.push_back(temp1);
                            }
                        }
                        if (checkWord(temp2)) {
                            if (!checkEnds(temp2)) {
                                dictionary.push_back(temp2);
                            }
                        }
                    }

                }

                else {
                    if (checkWord(temp)) {
                        if (!checkEnds(temp)) {
                            dictionary.push_back(temp);
                        }
                    }
                }
                
            }
        }
        size = dictionary.size();
    }
}


bool letterMan::compare(string current, string reviewed) {

    std::size_t currentSize = current.size();
    std::size_t reviewedSize = reviewed.size();

    //Check if differ by two letters
    if (reviewedSize > currentSize && reviewedSize - currentSize > 1)
        return false;

    else if (currentSize > reviewedSize && currentSize - reviewedSize > 1)
        return false;

    //If length is the same try change and swap
    else if (currentSize == reviewedSize) {
        if (changeCheck && swapCheck) {
            bool changed = false;
            bool swapped = false;

            for (size_t i = 0; i < currentSize; ++i) {
                //If two letters are different
                if (current[i] != reviewed[i]) {
                    //If not at the end
                    if (i != currentSize - 1) {
                        //Check if already been swapped or changed
                        if (!swapped && !changed) {
                            //If swap works
                            if (current[i] == reviewed[i + 1] && current[i + 1] == reviewed[i]) {
                                swapped = true;
                                modification = "s," + to_string(i);
                                ++i;
                            }
                            //If swap doesn't work we change
                            else {
                                changed = true;
                                modification = "c," + to_string(i) + "," + reviewed[i];
                            }
                        }
                        else
                            return false;
                    }
                    //Change
                    else {
                        //Check if already been swapped or changed
                        if (!swapped && !changed) {
                            changed = true;
                            modification = "c," + to_string(i) + "," + reviewed[i];
                        }
                        else {
                            return false;
                        }
                    }
                }
            }
            return true;
        }
        else if (changeCheck) {
            
            bool changed = false;
           
            for (size_t i = 0; i < currentSize; ++i) {
                //If two letters are different
                if (current[i] != reviewed[i]) {
                    //Check if already been changed
                    if (!changed) {
                        changed = true;
                        modification = "c," + to_string(i) + "," + reviewed[i];
                    }
                    else {
                        return false;
                    }
                }
            }
            return true;
        }
        else {

            bool swapped = false;
            
            for (size_t i = 0; i < currentSize; ++i) {
                //If two letters are different
                if (current[i] != reviewed[i]) {
                    //Check if already been swapped or changed
                    if (!swapped) {
                        //If not at the end
                        if (i != currentSize - 1) {
                            //If swap works
                            if (current[i] == reviewed[i + 1] && current[i + 1] == reviewed[i]) {
                                swapped = true;
                                modification = "s," + to_string(i);
                                ++i;
                            }
                            else
                                return false;
                        }
                        else
                            return false;
                    }
                    else
                        return false;
                }
            }
            return true;
            
        }
    }

    //If length is different by one run lengthcheck
    else {

        bool lengthed = false;
        
        //If Current word is larger than reviewed = deletion
        if (currentSize - reviewedSize == 1) {
            size_t j = 0;
            for (size_t i = 0; i < reviewedSize; ++i) {
                //Is there a difference
                if (current[i] != reviewed[j]) {
                    //Has there already been an addition
                    if (!lengthed) {
                        lengthed = true;
                        modification = "d," + to_string(i);
                        ++i;
                        //Check incremented i to make sure everything is good
                        if (current[i] != reviewed[j])
                            return false;
                    }
                    else
                        return false;   
                }
                ++j;
            }
            //Made it all the way to the end with no changes
            if (!lengthed) {
                modification = "d," + to_string(currentSize - 1);
                return true;
            }
            //We changed something and want to make sure the last letters match
            else if (current[currentSize - 1] != reviewed[reviewedSize - 1])
                return false;
            else
                return true;
        }
        //Reviewed word is larger than current = insertion
        else {
            size_t j = 0;
            for (size_t i = 0; i < currentSize; ++i) {
                //Is there a difference
                if (current[i] != reviewed[j]) {
                    //Has there already been an addition
                    if (!lengthed) {
                        lengthed = true;
                        modification = "i," + to_string(i) + "," + reviewed[j];
                        ++j;
                        //Check incremnted j to make sure everything is good
                        if (current[i] != reviewed[j])
                            return false;
                    }
                    else
                        return false;
                }
                ++j;
            }
            //Made it all the way to the end with no changes
            if (!lengthed) {
                modification = "i," + to_string(currentSize) + "," +reviewed[j];
                return true;
            }
            //We changed something and want to make sure the last letters match
            else if (current[currentSize - 1] != reviewed[reviewedSize - 1])
                return false;
            else
                return true;
        }
    }
    return true;
}

bool letterMan::find_path() {
   
    currentWord.wordIn = startWord;

    do {

        //After discovering all words for a particular word
        if (sizeQ > 0) {

            //Add to discard
            discard.push_back(currentWord);
            sizeD++;

                //Grab and remove top of queue
            
            currentWord = queue.at(0);
            //cout << "Removed: " << currentWord.wordIn << "\n";
            queue.pop_front();
            sizeQ--;

        }

        for (std::size_t i = 0; i < size; ++i) {
            //Check if word has been discovered already

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
                        ++sizeQ;
                    }
                    else {
                        //cout << "Added: " << temp.wordIn << "\n";
                        queue.push_front(temp);
                        ++sizeQ;
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
    
    cout << "Words in morph: " << to_string(sizeS) << "\n";
    cout << solution.at(sizeS - 1).wordIn << "\n";
    
    for (int i = sizeS - 2; i >= 0; --i) {
        
        if (outputFormat == 'W')
            cout << solution.at(i).wordIn << "\n";
        else
            cout << solution.at(i).modification << "\n";

    }
}

//Need to check dictionary for start and end word

int main(int argc, char** argv) {
    std::ios_base::sync_with_stdio(false);
    //auto start = std::chrono::high_resolution_clock::now();
    letterMan man;

    man.get_options(argc, argv);
    man.read_data();
    
    if (!man.startExist) {
        cout << "Start word not found in dictionary\n";
        exit(1);
    }
    if (!man.endExist) {
        cout << "End word not found in dictionary\n";
        exit(1);
    }
    
    /*
    
    auto stop1 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop1 - start);
    cerr << "Read_data took: " << duration.count() << "\n";
    
    cout << "Dictionary: \n";
    for (size_t i = 0; i < man.dictionary.size(); i++) {
        cout << man.dictionary.at(i) << "\n";
    }
    cout << "\n\n";
    */
    if (man.find_path()) {
        /*
        auto stop2 = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::microseconds>(stop2 - stop1);
        cerr << "Find_path tood: " << duration.count() << "\n";
        */
        man.write_data();
        /*
        auto stop3 = std::chrono::high_resolution_clock::now();
         duration = std::chrono::duration_cast<std::chrono::microseconds>(stop3 - stop2);
        cerr << "write_data took: " << duration.count() << "\n";
        */
    }
        
    else {
        /*
        auto stop2 = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::microseconds>(stop2 - stop1);
        cerr << "no solution took:" << duration.count() << "\n";
        */
        cout << "No solution, " << to_string(man.sizeD + 1) << " words discovered.\n";
    }
    /*
    auto stop3 = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop3 - start);
    cerr << duration.count() << "\n";
    */

    return 0;
}