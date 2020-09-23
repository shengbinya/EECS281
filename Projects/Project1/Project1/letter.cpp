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
    bool compare(const string & current, const string & reviewed);

    //Writes data to cout
    void write_data();

    bool checkLetters(string);

    bool checkWord(const string &);

    bool checkEnds(const string & temp);

    string diff(const string&, const string &);
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
        cout << "Words in morph: 1\n";
        cout << startWord << "\n";
        exit(0);
    }
}

void reverseString(string &in) {
    string reversed = "";
    std::size_t size = in.size();
    for (std::size_t i = 0; i < size; ++i) {
        reversed += in[size - 1 - i];
    }
    in = reversed;
}

bool letterMan::checkLetters(string check) {
    sort(check.begin(), check.end());
    return sortedStart == check;    
}

bool letterMan::checkWord(const string &temp) {
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

bool letterMan::checkEnds(const string &temp) {
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

        dictionary.reserve(size-1);

        cin.ignore();

        string temp = "";

        for (std::size_t i = 0; i < size; ++i) {
            
            cin >> temp;
            if (temp.substr(0, 2) == "//") {
                getline(cin, temp);
                --i;
            }

            else if (temp.size() == 0) {
                --i;
            }

            else{
              
                if (checkWord(temp)) {
                    if (!checkEnds(temp)) {
                        dictionary.push_back(temp);
                    }
                }
            }
        }
        --size;
    }

    else {
        string temp1 = "";
        cin >> temp1;
        const char* temp2 = { temp1.c_str() };
        size = atoi(temp2);

        dictionary.reserve(size);
        discard.reserve(size / 4);

        cin.ignore();
        string temp = "";

        string reversal = "&";
        string insert = "[]";
        string swap = "!";
        string twice = "?";
        const string chars = "&[]!?";

        for (std::size_t j = 0; j < size; ++j) {

            cin >> temp;
            if (temp.substr(0, 2) == "//") {
                getline(cin, temp);
                --j;
            }

            
            else {

                std::size_t index = temp.find_first_of(chars);
                if (index != std::string::npos) {

                    if (temp[index] == '&') {
                        string temp1 = temp.substr(0, index);
                        if (checkWord(temp1)) {
                            if (!checkEnds(temp1)) {
                                dictionary.push_back(temp1);
                            }
                            reverseString(temp1);
                            
                            if (!checkEnds(temp1)) {
                                dictionary.push_back(temp1);
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
                            temp1[index - 2] = temp[index - 1];
                            temp1[index - 1] = temp[index - 2];
                            if (!checkEnds(temp1)) {
                                dictionary.push_back(temp1);
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


bool letterMan::compare(const string & current, const string & reviewed) {

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
                                ++i;
                            }
                            //If swap doesn't work we change
                            else {
                                changed = true;
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
                    }
                    else {
                        return false;
                    }
                }
            }
            return true;
        }
        else if (swapCheck) {

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
        else
            return false;
    }

    //If length is different by one run lengthcheck
    else {
        
        bool lengthed = false;

        if (currentSize > reviewedSize) {
            //Check for differences
            int j = 0;
            for (size_t i = 0; i < currentSize; ++i) {
                if (current[i] != reviewed[j]) {
                    //Check if already changed
                    if (!lengthed) {
                        if (current[i + 1] == reviewed[j]) {
                            lengthed = true;
                            ++i;
                        }
                        else
                            return false;
                    }
                    else
                        return false;
                }
                ++j;
            }
            return true;
        }
        else {
            //Check for differences
            int j = 0;
            for (size_t i = 0; i < reviewedSize; ++i) {
                if (current[j] != reviewed[i]) {
                    //Check if already changed
                    if (!lengthed) {
                        if (current[j] == reviewed[i + 1]) {
                            lengthed = true;
                            ++i;
                        }
                        else
                            return false;
                    }
                    else
                        return false;
                }
                j++;
            }
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
            ++sizeD;

                //Grab and remove top of queue
            
            currentWord = queue.at(0);
            //cout << "Removed: " << currentWord.wordIn << "\n";
            queue.pop_front();
            --sizeQ;

        }

        for (std::size_t i = 0; i < size; ++i) {
            //Check if word has been discovered already

            if (dictionary[i].empty()) {}

            else {
                if (compare(currentWord.wordIn, dictionary.at(i))) {
                    
                    //Create word object
                    word temp;
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
                        //cout << "Added: " << temp.wordIn << "\n";
                        queue.push_back(temp);
                        ++sizeQ;
                    }
                    else {
                        //cout << "Added: " << temp.wordIn << "\n";
                        queue.push_front(temp);
                        ++sizeQ;
                    }
                    
                    //Add character to denote as discovered
                    dictionary[i] = std::string();
                }
            }
        }
            
     
    } while (sizeQ > 0);
    return false;
}

string letterMan::diff(const string& current, const string& reviewed) {
    size_t currentSize = current.size();
    size_t reviewedSize = reviewed.size();
    
    if (currentSize == reviewedSize) {
        for (size_t i = 0; i < currentSize; ++i) {
            if (current[i] != reviewed[i]) {
                if (i == currentSize - 1)
                    return "c," + to_string(i) + "," + current[i];
                else {
                    if (current[i + 1] != reviewed[i + 1])
                        return "s," + to_string(i);
                    else
                        return "c," + to_string(i) + "," + current[i];
                }
            }
        }
    }
    else {
        if (currentSize > reviewedSize) {
            for (size_t i = 0; i < reviewedSize; ++i) {
                if (current[i] != reviewed[i])
                    return "i," + to_string(i) + "," + current[i];
            }  
            return "i," + to_string(currentSize - 1) + "," + current[currentSize - 1];
        }
        else {
            for (size_t i = 0; i < currentSize; ++i) {
                if (current[i] != reviewed[i]) {
                    return "d," + to_string(i);
                }
            }
            return "d," + to_string(reviewedSize-1);
        }
    }
    return string();
    
}

void letterMan::write_data() {
    
    currentWord = discard.at(sizeD-1);
    vector<string> solution;

    if (outputFormat == 'M') {
        while (currentWord.discoveredBy != -1) {

            solution.push_back(diff(currentWord.wordIn, discard.at(currentWord.discoveredBy).wordIn));
            currentWord = discard.at(currentWord.discoveredBy);
        }
    }
    else {
        while (currentWord.discoveredBy != -1) {

            solution.push_back(currentWord.wordIn);
            currentWord = discard.at(currentWord.discoveredBy);

        }
    }
    
    solution.push_back(currentWord.wordIn);
    int sizeS = static_cast<int>(solution.size());
    
    cout << "Words in morph: " << to_string(sizeS) << "\n";
    cout << solution.at(sizeS - 1) << "\n";
    
    for (int i = sizeS - 2; i >= 0; --i) {
        
        if (outputFormat == 'W')
            cout << solution.at(i) << "\n";
        else
            cout << solution.at(i) << "\n";

    }
}

//Need to check dictionary for start and end word

int main(int argc, char** argv) {
    std::ios_base::sync_with_stdio(false);
   // auto start = std::chrono::high_resolution_clock::now();
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
    */
    /*
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