#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int item) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = item;
    newNode->next = NULL;
    return newNode;
}

typedef struct {
    Node* top;
} Stack;

void initialize(Stack* stack) {
    stack->top = NULL;
}

void push(Stack* stack, int item) {
    Node* newNode = createNode(item);
    newNode->next = stack->top;
    stack->top = newNode;
}

int pop(Stack* stack) {
    if (stack->top == NULL) {
        printf("Pop: Stack is empty\n");
        return -1;
    }

    Node* temp = stack->top;
    int item = temp->data;
    stack->top = stack->top->next;
    free(temp);
    return item;
}

int is_empty(Stack* stack) {
    return stack->top == NULL;
}

// Generate random push and pop operations
void generate_push_pop_operations(const char* input_file, const char* push_output_file, const char* pop_output_file) {
    Stack stack;
    initialize(&stack);

    FILE* input = fopen(input_file, "r");
    if (input == NULL) {
        printf("Error opening input file.\n");
        return;
    }

    FILE* push_output = fopen(push_output_file, "w");
    if (push_output == NULL) {
        printf("Error opening push output file.\n");
        fclose(input);
        return;
    }

    FILE* pop_output = fopen(pop_output_file, "w");
    if (pop_output == NULL) {
        printf("Error opening pop output file.\n");
        fclose(input);
        fclose(push_output);
        return;
    }

    int num_push, num_pop;
    fscanf(input, "%d %d", &num_push, &num_pop);

    int push_count = 0, pop_count = 0;

    // Generate push operations
    for (int i = 0; i < num_push; i++) {
        int item = rand() % 100 + 1;  // Generate a random item
        push(&stack, item);
        fprintf(push_output, "Push: %d\n", item);
        push_count++;
    }

    // Generate pop operations
    for (int i = 0; i < num_pop; i++) {
        if (is_empty(&stack)) {
            fprintf(pop_output, "Pop: Stack is empty\n");
        } else {
            int item = pop(&stack);
            fprintf(pop_output, "Pop: %d\n", item);
            pop_count++;
        }
    }

    fclose(input);
    fclose(push_output);
    fclose(pop_output);

    FILE* count_output = fopen("count_output.txt", "w");
    if (count_output == NULL) {
        printf("Error opening count output file.\n");
        return;
    }

    fprintf(count_output, "Push operations count: %d\n", push_count);
    fprintf(count_output, "Pop operations count: %d\n", pop_count);

    fclose(count_output);
}

int main() {
    srand(time(0));  // Initialize random seed

    const char* input_file = "input.txt";
    const char* push_output_file = "push_output.txt";
    const char* pop_output_file = "pop_output.txt";

    generate_push_pop_operations(input_file, push_output_file, pop_output_file);

    return 0;
}
