#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <sstream>

struct Node {
    int id;
    std::string str;
    Node* left;
    Node* right;

    Node(int id, const std::string& str) : id(id), str(str), left(nullptr), right(nullptr) {}
};


Node* insertNode(Node* root, int id, const std::string& str) {
    if (root == nullptr) {
        return new Node(id, str);
    }
    if (id < root->id) {
        root->left = insertNode(root->left, id, str);
    } else {
        root->right = insertNode(root->right, id, str);
    }
    return root;
}


void printTree(Node* root) {
    if (!root) return;
    printTree(root->left);
    std::cout << root->id << " " << root->str << '\n';
    printTree(root->right);
}


Node* findMin(Node* node) {
    while (node && node->left)
        node = node->left;
    return node;
}


Node* deleteNode(Node* root, int id) {
    if (!root) return nullptr;

    if (id < root->id) {
        root->left = deleteNode(root->left, id);
    } else if (id > root->id) {
        root->right = deleteNode(root->right, id);
    } else {
        if (!root->left && !root->right) {
            delete root;
            return nullptr;
        } else if (!root->left) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (!root->right) {
            Node* temp = root->left;
            delete root;
            return temp;
        } else {
            Node* temp = findMin(root->right);
            root->id = temp->id;
            root->str = temp->str;
            root->right = deleteNode(root->right, temp->id);
        }
    }
    return root;
}


void deleteTree(Node* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    Node* root = nullptr;

    std::ifstream file("node.txt");
    if (!file) {
        std::cerr << "Error opening file!\n";
        return 1;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.substr(0, 6) == "Edges:") break;
        int id;
        std::string name;
        std::istringstream iss(line);
        if (iss >> id >> name) {
            root = insertNode(root, id, name);
        }
    }
    file.close();

    std::cout << "Δυαδικό Δέντρο (Inorder Traversal):\n";
    printTree(root);

    int choice = 0;
    while (true) {
        std::cout << "\nΕπιλογές:\n";
        std::cout << "1: Εκτύπωση δέντρου\n";
        std::cout << "2: Εισαγωγή κόμβου\n";
        std::cout << "3: Διαγραφή κόμβου\n";
        std::cout << "Άλλη τιμή: Έξοδος\n";
        std::cout << "Επιλογή: ";
        std::cin >> choice;

        if (choice == 1) {
            printTree(root);
        } else if (choice == 2) {
            int id;
            std::string name;
            std::cout << "Δώσε νέο id: ";
            std::cin >> id;
            std::cout << "Δώσε string: ";
            std::cin >> name;
            root = insertNode(root, id, name);
        } else if (choice == 3) {
            int id;
            std::cout << "Δώσε id για διαγραφή: ";
            std::cin >> id;
            root = deleteNode(root, id);
        } else {
            break;
        }
    }

    deleteTree(root); // Ασφαλής απελευθέρωση μνήμης
    return 0;
}
