#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <sstream>
#include <cmath>

struct Node {
    int id;
    std::string str;
    Node  *left;
    Node *right;
    Node(int id, const std::string& str) : id(id), str(str), left(nullptr), right(nullptr) {}
};


Node* createNode(int id, const std::string& str) {
    Node* newNode = new Node(id, str);  
    return newNode;
}

int compute_height(Node *root) 
{
   if (root == nullptr) return 0;
   int left_height = compute_height(root->left);
   int right_height = compute_height(root->right);
   return 1 + (left_height > right_height ? left_height : right_height);
}

Node* Right_Rotate(Node *root) 
{
   Node *newRoot = root->left;
   root->left = newRoot->right;
   newRoot->right = root;
   return newRoot;
}

Node* Left_Rotate(Node *root) 
{
   Node *newRoot = root->right;
   root->right = newRoot->left;
   newRoot->left = root;
   return newRoot;
}

Node* Left_Right_Rotate(Node *root) 
{
   root->left = Left_Rotate(root->left);
   return Right_Rotate(root);
}

Node* Right_Left_Rotate(Node *root) 
{
   root->right = Right_Rotate(root->right);
   return Left_Rotate(root);
}

Node* balancefactor(Node *root) 
{
   if (root == nullptr) return root;
   int left_height = compute_height(root->left);
   int right_height = compute_height(root->right);
   if (left_height > right_height + 1) 
   {
      if (compute_height(root->left->left) >= compute_height(root->left->right)) 
      {
         return Right_Rotate(root);
      } 
      else 
      {
         return Left_Right_Rotate(root);
      }
   }
   if (right_height > left_height + 1) 
   {
      if (compute_height(root->right->right) >= compute_height(root->right->left)) 
      {
         return Left_Rotate(root);
      } 
      else 
      {
         return Right_Left_Rotate(root);
      }
   }
   return root;
}

Node* insertNode(Node *root, int id, std::string str) 
{
    if (root == nullptr) 
    {
        
        return createNode(id, str) ;
    }
    if (id < root->id) 
    {
        root->left = insertNode(root->left, id, str);
    } 
    else if (id > root->id) 
    {
        root->right = insertNode(root->right, id, str);
    }
    return balancefactor(root);
}

int isBalanced(Node* root) 
{
    if (root == nullptr) return 1;
    int left_height = compute_height(root->left);
    int right_height = compute_height(root->right);
    if (abs(left_height - right_height) > 1) return 0;
    return isBalanced(root->left) && isBalanced(root->right);
}


void printTree(Node *root) 
{
    if (root == nullptr) return;
    printTree(root->left);
    std::cout<< root->id<<' '<< root->str<<"\n";
    printTree(root->right);
}

Node* findMin(Node* node) 
{
    while (node->left != nullptr) 
    {
        node = node->left;
    }
    return node;
}

Node* deleteNode(Node* root, int id) 
{
    if (root == nullptr ) return nullptr;
    if (id < root->id) 
    {
        root->left = deleteNode(root->left, id);
    } 
    else if (id > root->id) 
    {
        root->right = deleteNode(root->right, id);
    } 
    else 
    {
        if (root->left == nullptr && root->right == nullptr) 
        {
            delete root;
            return  nullptr;
        } 
        else if (root->left == nullptr) 
        {
            Node* temp = root->right;
            delete root;
            return temp;
        } 
        else if (root->right == nullptr) 
        {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        Node* temp = findMin(root->right);
        root->id = temp->id;
        root->str = temp->str;
        root->right = deleteNode(root->right, temp->id);
    }
    return balancefactor(root);
}

void checkBalance(Node *root) 
{
    if (isBalanced(root)) 
    {
        std::cout<<"Το AVL tree είναι ισορροπημένο!\n";
    } 
    else 
    {
        std::cout<<"Το AVL tree ΔΕΝ είναι ισορροπημένο!\n";
    }
}

void deleteTree(Node* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main(void) 
{
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
    checkBalance(root);
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
            checkBalance(root);
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

        deleteTree(root); 
        return 0;
   }
