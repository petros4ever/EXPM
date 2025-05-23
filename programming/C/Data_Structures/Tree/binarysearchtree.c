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


struct Node* createNode(int id, char *name) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->id = id;
    strcpy(newNode->name, name);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
};

void insertNode(struct Node **root, int id, char *name) 
{
    if (*root == NULL) 
    {
        *root = createNode(id, name);
        return;
    }
    if (id < (*root)->id) 
    {
        insertNode(&((*root)->left), id, name);
    } 
    else 
    {
        insertNode(&((*root)->right), id, name);
    }
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
    return root;
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
            insertNode(&root, id, name);
        }
    }
    fclose(f);
    printf("Δυαδικό Δέντρο (Inorder Traversal):\n");
    printTree(root);
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
            case 1:printTree(root);break;
            case 2:
            printf("Give me the new id you want to insert:");
            scanf("%d",&id);
            printf("\nGive me a string:");
            scanf("%s",name);
            insertNode(&root, id, name);
            break;
            case 3:
            printf("\nGive me the id for the node you want to delete:");
            scanf("%d",&id);
            deleteNode(root,id);
            break;
            default:
            x=0;
            break;
       }
    }
    return 0;
   }
