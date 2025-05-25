#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR 50
#define MAX 100

struct Node {
    int id;
    char name[STR];
    struct Node  *left;
    struct Node *right;
};


struct Node* createNode(int id, char *name) 
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->id = id;
    strcpy(newNode->name, name);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

int compute_height(struct Node *root) 
{
   if (root == NULL) return 0;
   int left_height = compute_height(root->left);
   int right_height = compute_height(root->right);
   return 1 + (left_height > right_height ? left_height : right_height);
}

struct Node* Right_Rotate(struct Node *root) 
{
   struct Node *newRoot = root->left;
   root->left = newRoot->right;
   newRoot->right = root;
   return newRoot;
}

struct Node* Left_Rotate(struct Node *root) 
{
   struct Node *newRoot = root->right;
   root->right = newRoot->left;
   newRoot->left = root;
   return newRoot;
}

struct Node* Left_Right_Rotate(struct Node *root) 
{
   root->left = Left_Rotate(root->left);
   return Right_Rotate(root);
}

struct Node* Right_Left_Rotate(struct Node *root) 
{
   root->right = Right_Rotate(root->right);
   return Left_Rotate(root);
}

struct Node* balancefactor(struct Node *root) 
{
   if (root == NULL) return root;
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

struct Node* insertNode(struct Node *root, int id, char *name) 
{
    if (root == NULL) 
    {
        struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->id = id;
        strcpy(newNode->name, name);
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }
    if (id < root->id) 
    {
        root->left = insertNode(root->left, id, name);
    } 
    else if (id > root->id) 
    {
        root->right = insertNode(root->right, id, name);
    }
    return balancefactor(root);
}

int isBalanced(struct Node* root) 
{
    if (root == NULL) return 1;
    int left_height = compute_height(root->left);
    int right_height = compute_height(root->right);
    if (abs(left_height - right_height) > 1) return 0;
    return isBalanced(root->left) && isBalanced(root->right);
}


void printTree(struct Node *root) 
{
    if (root == NULL) return;
    printTree(root->left);
    printf("%d %s\n", root->id, root->name);
    printTree(root->right);
}

struct Node* findMin(struct Node* node) 
{
    while (node->left != NULL) 
    {
        node = node->left;
    }
    return node;
}

struct Node* deleteNode(struct Node* root, int id) 
{
    if (root == NULL) return NULL;
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
        if (root->left == NULL && root->right == NULL) 
        {
            free(root);
            return NULL;
        } 
        else if (root->left == NULL) 
        {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } 
        else if (root->right == NULL) 
        {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }
        struct Node* temp = findMin(root->right);
        root->id = temp->id;
        strcpy(root->name, temp->name);
        root->right = deleteNode(root->right, temp->id);
    }
    return balancefactor(root);
}

void checkBalance(struct Node *root) 
{
    if (isBalanced(root)) 
    {
        printf("Το AVL tree είναι ισορροπημένο!\n");
    } 
    else 
    {
        printf("Το AVL tree ΔΕΝ είναι ισορροπημένο!\n");
    }
}

int main(void) 
{
    FILE *f;
    char line[MAX];
    struct Node *root = NULL;
    f = fopen("node.txt", "r");
    if (f == NULL) 
    {
        printf("Error opening file!\n");
        return 1;
    }
    fgets(line, sizeof(line), f);
    while (fgets(line, sizeof(line), f)) 
    {
        if (strncmp(line, "Edges:", 6) == 0)
            break;
        int id;
        char name[STR];
        if (sscanf(line, "%d %s", &id, name) == 2) {
            root=insertNode(root, id, name);
        }
    }
    fclose(f);
    printf("avl Δέντρο (Inorder Traversal):\n");
    printTree(root);
    checkBalance(root);
    int number,x=1,id;
    char name[STR];
    while(x==1)
    {
       printf("You can choose the following\n");
       printf("1:Print the Tree\n");
       printf("2:Insert a node\n");
       printf("3:delete a node\n");
       printf("else:exit");
       printf("\nselection:");
       scanf("%d",&number);
       switch(number)
       {
            case 1:
            printTree(root);
            checkBalance(root);
            break;
            case 2:
            printf("Give me the new id you want to insert:");
            scanf("%d",&id);
            printf("\nGive me a string:");
            scanf("%s",name);
            root=insertNode(root, id, name);
            break;
            case 3:
            printf("\nGive me the id for the node you want to delete:");
            scanf("%d",&id);
            root=deleteNode(root,id);
            break;
            default:
            x=0;
            break;
       }
    }
    return 0;
   }
