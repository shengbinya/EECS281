/**
 * problem1.cpp
 *
 * EECS 281: Lab 2
 * Spring 2017
 *
 * Implements insertion sort.
 *
 * Use with the `perf` profiling tool to find out where a program spends most of its time.
 */

#include <iostream>
#include <vector>
#include <utility>
using namespace std;


/**
 * Reads data into a vector of any type that supports >> for reading.
 */
template <typename T>
void readData(vector<T> &data) {
    T temp;

    while (cin >> temp) {
        data.push_back(temp);
    }
}


/**
 * Swaps two values if necessary, so that the smallest comes first.
 */
template <typename T>
void compswap(T &a, T &b) {
    if (b < a) {
        swap(a, b);
    }
}


/**
 * Insertion sort, adapted for a vector of any type that supports < comparisons.
 */
template <typename T>
void insertionSort(vector<T> &data) {
    for (size_t i = data.size() - 1; i > 0; i--) {
        compswap(data[i - 1], data[i]);
    }

    for (size_t i = 2; i < data.size(); i++) {
        T v = data[i];
        size_t j = i;
        while (v < data[j - 1]) {
            data[j] = data[j - 1];
            j--;
        }
        data[j] = v;
    }
}


int main() {
    vector<int> data;

    readData(data);
    insertionSort(data);
    cout << "Largest element: " << data.back() << endl;

    return 0;
}
