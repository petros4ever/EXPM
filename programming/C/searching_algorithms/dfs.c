#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR 50
#define MAX 100

struct Node {
    int id;
    char name[STR];
};

struct Graph {
    int number_of_nodes;
    int node_connection[MAX][MAX];
};

struct Stack {
    int items[MAX];
    int top;
};

void push(struct Stack *s, int value) {
    s->items[++(s->top)] = value;
}

int pop(struct Stack *s) {
    return s->items[(s->top)--];
}

int isEmpty(struct Stack *s) {
    return s->top == -1;
}

void dfs(struct Graph *graph, struct Node nodes[], int start_index) 
{
    struct Stack stack;
    stack.top = -1;
    int visited[MAX] = {0};
    push(&stack, start_index);
    while (!isEmpty(&stack)) 
    {
        int node = pop(&stack);
        if (!visited[node]) 
       {
            printf("Visited: %d %s\n", nodes[node].id, nodes[node].name);
            visited[node] = 1;
        }

        for (int i = 0; i < graph->number_of_nodes; i++) {
            if (graph->node_connection[node][i] == 1 && !visited[i]) 
            {
                push(&stack, i);
            }
        }
    }
}

int main(void) {
    FILE *f;
    char line[100];
    int row = 0;
    struct Node nodes[MAX];
    struct Graph graph;
    int id_to_index[100] = {0};  
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
        if (sscanf(line, "%d %s", &id, name) == 2) 
        {
            nodes[row].id = id;
            strcpy(nodes[row].name, name);
            id_to_index[id] = row;
            row++;
        }
    }

    graph.number_of_nodes = row;
    memset(graph.node_connection, 0, sizeof(graph.node_connection));
    int src, dest;
    while (fgets(line, sizeof(line), f)) 
    {
        if (sscanf(line, "%d %d", &src, &dest) == 2) 
        {
            int i = id_to_index[src];
            int j = id_to_index[dest];
            graph.node_connection[i][j] = 1;
        }
    }
    fclose(f);
    int start_id = 3;
    int start_index = id_to_index[start_id];
    printf("Stack-Based DFS starting from node with ID %d:\n", start_id);
    dfs(&graph, nodes, start_index);
    return 0;
}
