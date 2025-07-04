#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>

struct Node {
    int id;
    std::string name;
};

struct Graph {
    int number_of_nodes;
    std::vector<std::vector<int>> node_connection;
};

int heuristic(const Node& node, const Node& goal) {
    return std::abs(node.id - goal.id); 
}

struct Compare {
    const std::vector<Node>& nodes;
    const Node& goal;

    Compare(const std::vector<Node>& n, const Node& g) : nodes(n), goal(g) {}

    bool operator()(int a, int b) const {
        return heuristic(nodes[a], goal) > heuristic(nodes[b], goal);
    }
};

void bestfs(const Graph& graph, const std::vector<Node>& nodes, int start_index, int goal_index) {
    std::vector<bool> visited(graph.number_of_nodes, false);
    const Node& goal = nodes[goal_index];

    std::priority_queue<int, std::vector<int>, Compare> pq(Compare(nodes, goal));
    pq.push(start_index);
    visited[start_index] = true;

    while (!pq.empty()) {
        int node = pq.top();
        pq.pop();

        std::cout << "Visited: " << nodes[node].id << " " << nodes[node].name << '\n';

        if (node == goal_index) {
            std::cout << "Reached goal!\n";
            return;
        }

        for (int i = 0; i < graph.number_of_nodes; ++i) {
            if (graph.node_connection[node][i] == 1 && !visited[i]) {
                visited[i] = true;
                pq.push(i);
            }
        }
    }

    std::cout << "Goal not reachable.\n";
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
    int goal_id = 6; 
    if (id_to_index.find(goal_id) == id_to_index.end()) {
               std::cerr << "Goal ID not found in graph.\n";
               return 1;
       }
    int goal_index = id_to_index[goal_id];

    int start_index = id_to_index[start_id];
    std::cout << "BestFS starting from node ID " << start_id << " to " << goal_id << ":\n";
    bestfs(graph, nodes, start_index,goal_index);

    return 0;
}
