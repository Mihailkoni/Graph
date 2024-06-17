#include "Graph.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;


void read_file(const string& filename, Graph& graph) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Unable to open file";
        return;
    }

    string line;
    getline(file, line);
    int numVertices = stoi(line);

    graph = Graph(numVertices);

    int s = 0;

    while (getline(file, line)) {
        istringstream ss(line);
        int v, weight;
        while (ss >> v >> weight) {
            graph.add_edge(s, v, weight);
        }
        s++;
    }
    file.close();
}



int main() {
    Graph graph(0); 
    read_file("Input.txt", graph);

    cout << "Graph:" << "\n";
    graph.print_graph(); // ����� �����

    cout << "\nDepth search(starting from 0):" << "\n";
    graph.depth_search(0); // ����� � �������

    cout << "\nBreadth search(starting from 0):" << "\n";
    graph.breadth_search(0); // ����� � ������
    
    graph.algorithm_Prim(); // �������� �����

    return 0;
}