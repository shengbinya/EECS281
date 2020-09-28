# EECS 281: Lab 2 - Balancing Parentheses

#
## Introduction

This assignment serves as an introduction to the stack and queue data structure. With this problem, students gain exposure to a problem where the solution depends on keeping track of data in LIFO order (in this case, students will need to keep track of parentheses - every time they see a right-facing parenthesis, they must check if the previously encountered left-facing parenthesis is of the same type).

## Problem Statement

Implement balanced, a program that checks the contents of a file for balanced parentheses, square brackets and curly braces: (), [] and {}.
* The program should behave on the command-line as follows:   
    ```bash
   ./balanced < filename
    ```
* The program should output the word "Balanced" (without quotes) to stdout if parentheses are balanced and the words "Not balanced" (without quotes) otherwise. Make sure your capitalization is correct!
* Here are some examples of balanced and not balanced strings:
    * Balanced:
        ```bash
        int main() { int x; cin >> x; if (x * (2 + z[1])) { cout << "hi"; }}
        [hi[[((()))]]]
        [1{2[3(4)5]6}7]8(9)0(...)
        ```
    * Not balanced:
        ```bash
        ( { ) }
        int main() }
        [((}}] :)
        ```

## Hints

Here are some hints:
* Use one of the data structures discussed/used in previous labs/projects.
* There is no need to use getopt.
* Do not read in your words as strings. You cannot guarantee there will be spaces between characters.
* Use an input stream iterator to read input and manage memory. Be sure to #include <iterator>. See section 9.4 of The C++ Standard Library textbook by Josuttis or visit the webpage http://www.cplusplus.com/reference/iterator/istream_iterator/ for examples of how to use them.
* You can meet the requirements without using stream iterators - but you should know they exist! This is is a good opportunity to try them out!
* Feel free to use your own C++ files for testing, although be mindful that parentheses inside of string and character literals and in the comments might confuse the program. You need not take care of these cases, but you are certainly welcome to try!

