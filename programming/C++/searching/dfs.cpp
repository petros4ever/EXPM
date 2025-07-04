#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stack>
#include <unordered_map>

struct Node {
    int id;
    std::string name;
};

struct Graph {
    int number_of_nodes;
    std::vector<std::vector<int>> node_connection;
};

void dfs(const Graph& graph, const std::vector<Node>& nodes, int start_index) {
    std::vector<bool> visited(graph.number_of_nodes, false);
    std::stack<int> stack;
    stack.push(start_index);

    while (!stack.empty()) {
        int node = stack.top();
        stack.pop();

        if (!visited[node]) {
            std::cout << "Visited: " << nodes[node].id << " " << nodes[node].name << '\n';
            visited[node] = true;
        }

        // Περνάμε από τους γείτονες αντίστροφα για να διατηρήσουμε τη σειρά DFS
        for (int i = graph.number_of_nodes - 1; i >= 0; --i) {
            if (graph.node_connection[node][i] == 1 && !visited[i]) {
                stack.push(i);
            }
        }
    }
}

int main() {
    std::vector<Node> nodes;
    std::unordered_map<int, int> id_to_index;
    Graph graph;

    std::ifstream file("node.txt");
    if (!file) {
        std::cerr << "Error opening file!\n";
        return 1;
    }

    std::string line;
    int row = 0;

    // Ανάγνωση κόμβων
    while (std::getline(file, line)) {
        if (line.substr(0, 6) == "Edges:") break;

        std::istringstream iss(line);
        int id;
        std::string name;
        if (iss >> id >> name) {
            nodes.push_back({id, name});
            id_to_index[id] = row++;
        }
    }

    // Αρχικοποίηση adjacency matrix
    graph.number_of_nodes = row;
    graph.node_connection.resize(row, std::vector<int>(row, 0));

    // Ανάγνωση ακμών
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int src, dest;
        if (iss >> src >> dest) {
            int i = id_to_index[src];
            int j = id_to_index[dest];
            graph.node_connection[i][j] = 1;
        }
    }

    file.close();

    int start_id = 3;
    if (id_to_index.find(start_id) == id_to_index.end()) {
        std::cerr << "Start ID not found in graph.\n";
        return 1;
    }

    int start_index = id_to_index[start_id];
    std::cout << "DFS starting from node ID " << start_id << ":\n";
    dfs(graph, nodes, start_index);

    return 0;
}
