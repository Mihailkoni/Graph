#include "Circular_Doubly_Linked_List.h"
#include "Array_Sort.h"
#include <iostream>
#include <vector>
#include <queue> // очередь
#include <fstream>
#include <sstream>
#include <string>
#include <stack> // стэк
#include <limits>
using namespace std;

class Graph {
private:
    vector<Circle*> My_Graph;
    int num_v;

    void for_depth_search(int v, vector<bool>& visited) {
        stack<int> stack; // стэк
        stack.push(v); // Помещаем начальную вершину в стек

        while (!stack.empty()) { // Пока стек не пуст
            int vertex = stack.top(); // Получаем вершину из вершины стека
            stack.pop(); // Удаляем вершину из стека

            if (!visited[vertex]) { // Если вершина еще не была посещена
                cout << vertex << " "; // Выводим вершину
                visited[vertex] = true; // Помечаем вершину 
            }

            Circle* node = My_Graph[vertex];

            if (node != nullptr) { // Проверяем, есть ли у текущей вершины смежные вершины
                // Создаем временный вектор для хранения непосещенных смежных вершин
                vector<int> neighbors;
                do {
                    if (!visited[node->vertex]) {
                        neighbors.push_back(node->vertex);
                    }
                    node = node->next; 
                } while (node != My_Graph[vertex]); // Пока не вернемся к началу списка
                long n = neighbors.size();
                bubble_Sort(neighbors, n);
                for (int neighbor : neighbors) {
                    stack.push(neighbor); // Добавляем вершину в стек
                }
            }
        }
    }

    void for_breadth_search(int start_vertex, vector<bool>& visited) {
        queue<int> q;// очередь
        q.push(start_vertex); // помещаем начальную вершину в очередь

        while (!q.empty()) { // пока очередь не пуста
            int vertex = q.front(); // берём первый из очереди 
            q.pop(); // удаляем элемент из начала

            if (!visited[vertex]) { // Если вершина еще не была посещена
                cout << vertex << " "; // Выводим вершину
                visited[vertex] = true; // Помечаем вершину 
            }

            Circle* node = My_Graph[vertex];

            if (node != nullptr) { // проверяем есть ли смежные вершины
                vector<int> neighbors;
                do {
                    if (!visited[node->vertex]) { // если ещё не была посещена
                        neighbors.push_back(node->vertex);
                    }
                    node = node->next;
                } while (node != My_Graph[vertex]);
                long n = neighbors.size();
                bubble_Sort(neighbors, n);
                for (int neighbor : neighbors) {
                    q.push(neighbor); // Добавляем вершину в очередь
                }

            }
        }
        cout << "\n";
    }
public:

    Graph(int v) : num_v(v), My_Graph(v, nullptr) {} //конструктор 

    ~Graph() { // деструктор
        for (int i = 0; i < num_v; ++i) {
            delete_List(My_Graph[i]);
        }
        
    }

    void delete_vertex(int vertex) { // удаление вершины
        if (vertex >= num_v) {
            return; 
        }

        // Удаляем все входящие и исходящие ребра
        for (int i = 0; i < num_v; ++i) {
            delete_from_list(My_Graph[i], vertex);
        }

        delete_List(My_Graph[vertex]); // удаляем список
        My_Graph.erase(My_Graph.begin() + vertex);// удаляем сам узел
        num_v--;

        
        for (int i = 0; i < num_v; ++i) {// Обновляем индексы смежных вершин
            Circle* current = My_Graph[i];
            if (current) {
                do {
                    if (current->vertex > vertex) {
                        current->vertex--;
                    }
                    current = current->next;
                } while (current != My_Graph[i]);
            }
        }
    }

    void add_edge(int first, int second, int weight) { // добавление ребра
        add_to_list(My_Graph[first], second, weight);
        add_to_list(My_Graph[second], first, weight);
    }

    void delete_edge(int first, int second) { // удаление ребра
        delete_from_list(My_Graph[first], second);
        delete_from_list(My_Graph[second], first);
    }

    void print_graph() { // вывод графа
        for (int i = 0; i < num_v; ++i) {
            cout << "Vertex " << i << ": ";
            print_list(My_Graph[i]);
        }
    }

    
    void depth_search(int start_vertex) { //обхода графа в глубину 
        vector<bool> visited(num_v, false); // массив для проверки посещения
        for_depth_search(start_vertex, visited);
        cout << "\n";
    }

    void breadth_search(int start_vertex) {
        vector<bool> visited(num_v, false); // массив для проверки посещения
        for_breadth_search(start_vertex, visited);
        cout << "\n";
    }
    
    void algorithm_Prim() {
        int V = num_v; // кол-во вершин 
        vector<int> minimal_tree(V, -1);  // Массив для хранения родителя каждой вершины в минимальном остовном дереве
        vector<int> key(V, numeric_limits<int>::max()); // хранит минимальный путь до каждой вершины, начальное значение - бесконечность(самое большое число типа).
        vector<bool> in_minimal_tree(V, false);  // отслеживать вершины, включенные в минимальное остовное дерево

        key[0] = 0; // начинаем с вершины 0
        minimal_tree[0] = -1;  // первая вершина всегда корень минимального остовного дерева

        for (int i = 0; i < V - 1; i++) {
            // Выбираем минимальный путь из множества вершин, не включенных в минимальное остовное дерево
            int u = -1;
            int min_path = numeric_limits<int>::max();
            for (int j = 0; j < V; j++) {
                if ((!in_minimal_tree[j]) && (key[j] < min_path)) {
                    min_path = key[j];
                    u = j;
                }
            }

            // добавление выбраной вершины в минимальное остовное дерево
            in_minimal_tree[u] = true;

            // обновление значения ключей и родителей смежных вершин выбранной вершины
            Circle* node = My_Graph[u];
            if (node != nullptr) {
                do {
                    int v = node->vertex;
                    int weight = node->weight;
                    if ((!in_minimal_tree[v]) && (weight < key[v])) {
                        minimal_tree[v] = u;
                        key[v] = weight;
                    }
                    node = node->next;
                } while (node != My_Graph[u]);
            }
        }

        
        // Печатаем результат
        cout << "Edge \tWeight\n";
        int total_weight = 0;
        for (int i = 1; i < V; ++i) {
            cout << minimal_tree[i] << " - " << i << " \t" << key[i] << " \n";
            total_weight += key[i];
        }
        cout << "Total weight: " << total_weight << "\n";
    }
    
};

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
    graph.print_graph(); // вывод графа

    cout << "\nDepth search(starting from 0):" << "\n";
    graph.depth_search(0); // Обход в глубину

    cout << "\nBreadth search(starting from 0):" << "\n";
    graph.breadth_search(0); // Обход в ширину
    
    graph.algorithm_Prim(); // алгоритм прима

    return 0;
}