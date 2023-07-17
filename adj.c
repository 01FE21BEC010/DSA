#include<stdio.h>
#include<stdlib.h>

#define MAX_VERTICES 100

typedef struct
{
    int data[MAX_VERTICES];
    int top;
} Stack;

void initializeStack(Stack* stack)
{
    stack->top = -1;
}

int isStackEmpty(Stack* stack)
{
    return stack->top == -1;
}

void push(Stack* stack, int value)
{
    stack->data[++stack->top] = value;
}

int pop(Stack* stack) {
    return stack->data[stack->top--];
}

void printGraphMatrix(int adj[][MAX_VERTICES], int no_vertices)
{
    int i, j;
    for (i = 0; i < no_vertices; i++)
    {
        for (j = 0; j < no_vertices; j++)
        {
            printf("%d\t", adj[i][j]);
        }
        printf("\n");
    }
}

void printGraphList(int adj[][MAX_VERTICES], int no_vertices)
{
    int i, j;
    for (i = 0; i < no_vertices; i++)
    {
        printf("Adjacent vertices of vertex %d: ", i);
        for (j = 0; j < no_vertices; j++)
        {
            if (adj[i][j] == 1)
                printf("%d ", j);
        }
        printf("\n");
    }
}

void saveGraphToFile(int adj[][MAX_VERTICES], int no_vertices)
{
    FILE *file;
    file = fopen("graph.txt", "w");
    if (file == NULL)
    {
        printf("Unable to open the file.\n");
        return;
    }

    int i, j;
    fprintf(file, "Adjacency Matrix:\n");
    for (i = 0; i < no_vertices; i++)
    {
        for (j = 0; j < no_vertices; j++)
        {
            fprintf(file, "%d\t", adj[i][j]);
        }
        fprintf(file, "\n");
    }

    fprintf(file, "\nAdjacency List:\n");
    for (i = 0; i < no_vertices; i++)
    {
        fprintf(file, "Adjacent vertices of vertex %d: ", i);
        for (j = 0; j < no_vertices; j++)
        {
            if (adj[i][j] == 1)
                fprintf(file, "%d ", j);
        }
        fprintf(file, "\n");
    }

    fclose(file);
    printf("Graph has been saved to graph.txt file.\n");
}


void DFS(int adj[][MAX_VERTICES], int no_vertices, int startVertex)
{        int i;
    int visited[MAX_VERTICES] = {0};
    Stack stack;
    initializeStack(&stack);

    push(&stack, startVertex);
    visited[startVertex] = 1;

   printf("DFS traversal starting from vertex %d: ", startVertex);




    while (!isStackEmpty(&stack))
        {
        int currentVertex = pop(&stack);
        printf("%d ", currentVertex);

        int i;
        for (i = 0; i < no_vertices; i++)
            {
            if (adj[currentVertex][i] == 1 && visited[i] == 0) {
                push(&stack, i);
                visited[i] = 1;
            }
        }
    }

    printf("\n");
}

int main()
{
    int s = 0, d = 0;
    int i, j;
    int no_vertices;

    printf("\nEnter the number of vertices: ");
    scanf("%d", &no_vertices);

    int adjMatrix[MAX_VERTICES][MAX_VERTICES];

    for (i = 0; i < no_vertices; i++)
    {
        for (j= 0; j < no_vertices; j++)
        {
            adjMatrix[i][j] = 0;
        }
    }

    while (s != -1 && d != -1)
    {
        printf("Enter an edge from node (0 to %d) to node (0 to %d): ", no_vertices -1 , no_vertices -1);
        scanf("%d %d", &s, &d);

        if (s == -1 || d == -1)
            break;

 if (s < 0 || s >= no_vertices || d < 0 || d >= no_vertices)
        {
            printf("Invalid input! Please enter valid node indices.\n");
            continue;
        }

        adjMatrix[s][d] = 1;
        adjMatrix[d][s] = 1;
    }

    printf("\nAdjacency Matrix:\n");
    printGraphMatrix(adjMatrix, no_vertices);

    printf("\nAdjacency List:\n");
    printGraphList(adjMatrix, no_vertices);

    saveGraphToFile(adjMatrix, no_vertices);

    int startVertex;
    for(i=0;i<no_vertices;i++)
        {
          printf("Enter the starting vertex for DFS: ");
          scanf("%d", &startVertex);
    DFS(adjMatrix, no_vertices, startVertex);
        }

    return 0;
}
