/*  Identifier = 15C1680EE94C640EC35E1694295A3625C3254CBA

    EECS 281 Lab 4: Connected Components

    For this lab, you will write a program that calculates the
    number of connected components in an undirected graph.

    Your program will receive an input file in the following format:
    1) The first line of input contains the number of vertices V and number of edges E in the graph.
    2) The next E lines list out the connections between vertices in the graph in the format of "u v",
    which indicates the existence of an edge between u and v.

    For example, the following input file would be read as follows:
    4 2  (the graph has 4 vertices (numbered from 0-3), and two edges exist in the graph)
    0 1  (the first of these edges connects vertex 0 with vertex 1)
    0 2  (the second of these edges connects vertex 0 with vertex 2)

    In this case, vertices {0, 1, 2} form a connected component, and vertex {3} forms a connected component
    (since 3 is not connected to anything). Thus, your program should print out 2.

    You will be using union-find to complete this lab. The following starter code has been provided. Feel
    free to modify this code in your implementation. Good luck!
*/

//Matt Martin mgmii
//Brenan Nell bnelll

#include <stdio.h>
#include <vector>
#include <iostream>
#include <utility>
#include <queue>

using std::vector;
using std::cin;
using std::cout;
using std::endl;

class Graph {
    unsigned int V;
    unsigned int E;
    vector<unsigned int> indices;
    vector<unsigned int> check;

public:
    // Graph constructor that initializes the graph and its member variables
    Graph(unsigned int V, unsigned int E) {
        this->V = V;
        this->E = E;
        indices.reserve(V);
        check.resize(V,0);

        //Initialize all values to themselves
        for (unsigned int i = 0; i < V; ++i) {
            indices.push_back(i);
        }

        //Read and update representative
        unsigned int rep = 0;
        unsigned int loc = 0;

        //Go through all given edges
        for (unsigned int i = 0; i < E; ++i) {
            cin >> rep;
            cin >> loc;

            //Assign representative if one not already assigned to it
            if (indices[rep] == rep) {
                if(rep != find(loc))
                    indices[rep] = loc;
            }
                

            //If they're already the same value
            else if (indices[rep] == loc) {}

            //If rep already assigned to value
            else
                set_union(rep, indices[loc]);
        }

    } // Graph()

      // TODO: implement the find function
    unsigned int find(unsigned int v) {
        
        //Find root
        unsigned int current = v;
        while (indices[current] != current) {
            current = indices[current];
        }

        return current;
    } // find()

      // TODO: implement the union function
    void set_union(unsigned int a, unsigned int b) {
        int root = find(a);
        int root2 = find(b);
        int current = 0;
        if (root < root2) {
            indices[root2] = root;
            current = b;
        }
            
        else {
            indices[root] = root2;
            current = a;
            root = root2;
        }
            
        //Path Compression
        int temp = 0;
        while (root != current) {
            temp = indices[current];
            indices[current] = root;
            current = temp;
        }
        
    } // set_union()

      // TODO: implement the count function
    unsigned int count_components() {
        int num = 0;
        for (unsigned int i = 0; i < indices.size(); ++i) {
            if (indices[i] == i)
                check[i] = 1;
            else {
                int root = find(i);
                check[root] = 1;
            }
        }
        for (int i = 0; i < int(check.size()); ++i) {
            num += check[i];
        }
        return num;
    } // count_components()

};

int main() {
    //  You do not need to modify main.
    std::ios_base::sync_with_stdio(false);
    unsigned int vertex_count, edge_count = 0;
    cin >> vertex_count;
    cin >> edge_count;
    Graph g(vertex_count, edge_count);
    cout << g.count_components() << endl;
    return 0;
}
