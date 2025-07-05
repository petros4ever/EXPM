#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <climits>
#include <algorithm>

struct Node {
    int id;
    std::string name;
};

struct Graph {
    int number_of_nodes;
    std::vector<std::vector<std::pair<int, int>>> adj; 
};

struct AStarNode {
    int index;
    int f_cost;

    bool operator>(const AStarNode& other) const {
        return f_cost > other.f_cost;
    }
};

int heuristic(const Node& node, const Node& goal) {
    return std::abs(node.id - goal.id); 
}


void astar(const Graph& graph, const std::vector<Node>& nodes, int start_index, int goal_index) {
    std::vector<int> g_cost(graph.number_of_nodes, INT_MAX);
    std::vector<int> parent(graph.number_of_nodes, -1);
    std::vector<bool> visited(graph.number_of_nodes, false);

    const Node& goal = nodes[goal_index];
    g_cost[start_index] = 0;

    std::priority_queue<AStarNode, std::vector<AStarNode>, std::greater<AStarNode>> pq;
    pq.push({start_index, heuristic(nodes[start_index], goal)});

    while (!pq.empty()) {
        int current = pq.top().index;
        pq.pop();

        if (visited[current]) continue;
        visited[current] = true;

        std::cout << "Visited: " << nodes[current].id << " " << nodes[current].name << '\n';

        if (current == goal_index) {
            std::cout << "Reached goal!\n";

            // Ανακατασκευή διαδρομής
            std::vector<int> path;
            for (int at = goal_index; at != -1; at = parent[at])
                path.push_back(at);
            std::reverse(path.begin(), path.end());

            std::cout << "Path: ";
            for (int idx : path)
                std::cout << nodes[idx].id << " ";
            std::cout << '\n';
            return;
        }

        for (const auto& [neighbor, weight] : graph.adj[current]) {
           int tentative_g = g_cost[current] + weight;
           if (tentative_g < g_cost[neighbor]) {
           g_cost[neighbor] = tentative_g;
           parent[neighbor] = current;
           int f = g_cost[neighbor] + heuristic(nodes[neighbor], goal);
           pq.push({neighbor, f});
          }
       }


    }
    std::cout << "Goal not reachable.\n";
}

int main() {
    std::vector<Node> nodes;
    std::unordered_map<int, int> id_to_index;
    Graph graph;

    std::ifstream file("node1.txt");
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

    // Ανάγνωση ακμών
    graph.adj.resize(row); 

    while (std::getline(file, line)) {
           std::istringstream iss(line);
           int src, dest, weight;
           if (iss >> src >> dest >> weight) {
               int i = id_to_index[src];
                int j = id_to_index[dest];
                 graph.adj[i].push_back({j, weight});
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
    std::cout << "astar starting from node ID " << start_id << " to " << goal_id << ":\n";
    astar(graph, nodes, start_index,goal_index);

    return 0;
}
