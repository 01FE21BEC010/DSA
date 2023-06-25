#include <stdio.h>
#include <stdlib.h>

struct Node {
    int key;
    struct Node* left;
    struct Node* right;
    int height;
};

int max(int a, int b) {
    return (a > b) ? a : b;
}

int getHeight(struct Node* node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

int getBalance(struct Node* node) {
    if (node == NULL) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

struct Node* createNode(int key) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;
    return newNode;
}

struct Node* rightRotate(struct Node* y) {
    struct Node* x = y->left;
    struct Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    // Return new root
    return x;
}

struct Node* leftRotate(struct Node* x) {
    struct Node* y = x->right;
    struct Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    // Return new root
    return y;
}

struct Node* insert(struct Node* root, int key);
struct Node* delete(struct Node* root, int key);

struct Node* insert(struct Node* root, int key) {
    if (root == NULL) {
        return createNode(key);
    }

    if (key < root->key) {
        root->left = insert(root->left, key);
    } else if (key > root->key) {
        root->right = insert(root->right, key);
    } else {
        // Duplicate keys are not allowed
        return root;
    }

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    int balance = getBalance(root);

    // Left Left Case
    if (balance > 1 && key < root->left->key) {
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && key > root->right->key) {
        return leftRotate(root);
    }

    // Left Right Case
    if (balance > 1 && key > root->left->key) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Left Case
    if (balance < -1 && key < root->right->key) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

struct Node* minValueNode(struct Node* node) {
    struct Node* current = node;

    while (current->left != NULL) {
        current = current->left;
    }

    return current;
}

struct Node* delete(struct Node* root, int key) {
    if (root == NULL) {
        return root;
    }

    if (key < root->key) {
        root->left = delete(root->left, key);
    } else if (key > root->key) {
        root->right = delete(root->right, key);
    } else {
        // Node to be deleted found

        // Case 1: No child or only one child
        if (root->left == NULL || root->right == NULL) {
            struct Node* temp = root->left ? root->left : root->right;

            // No child case
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                // One child case
                *root = *temp;
            }
            free(temp);
        } else {
            // Case 2: Two children
            struct Node* temp = minValueNode(root->right);

            root->key = temp->key;
            root->right = delete(root->right, temp->key);
        }
    }

    // If the tree had only one node, return
    if (root == NULL) {
        return root;
    }

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    int balance = getBalance(root);

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0) {
        return rightRotate(root);
    }

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0) {
        return leftRotate(root);
    }

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void displayTree(struct Node* root, int level) {
    if (root != NULL) {
        displayTree(root->right, level + 1);

        for (int i = 0; i < level; i++) {
            printf("    ");
        }

        printf("%d\n", root->key);

        displayTree(root->left, level + 1);
    }
}

void saveTraversalToFile(struct Node* root, FILE* file) {
    if (root != NULL) {
        fprintf(file, "%d ", root->key);
        saveTraversalToFile(root->left, file);
        saveTraversalToFile(root->right, file);
    }
}

void countNodesAtLevel(struct Node* root, int level, int* count) {
    if (root == NULL) {
        return;
    }

    if (level == 0) {
        (*count)++;
    } else if (level > 0) {
        countNodesAtLevel(root->left, level - 1, count);
        countNodesAtLevel(root->right, level - 1, count);
    }
}

void displayNodesAtEachLevel(struct Node* root) {
    int height = getHeight(root);

    printf("Number of nodes at each level:\n");
    for (int level = 0; level <= height; level++) {
        int count = 0;
        countNodesAtLevel(root, level, &count);
        printf("Level %d: %d\n", level, count);
    }
}

int main() {
    struct Node* root = NULL;
    int choice, key;
    int numRandomNumbers;

    // Get the number of random numbers from the user
    printf("Number of random numbers to generate: ");
    scanf("%d", &numRandomNumbers);

    // Generate random numbers and save them in a file
    FILE* randomNumbersFile = fopen("random_numbers.txt", "w");
    if (randomNumbersFile == NULL) {
        printf("Failed to open random_numbers.txt for writing.\n");
        return 1;
    }

    srand(time(0)); // Initialize random seed

    for (int i = 0; i < numRandomNumbers; i++) {
        int randomNumber = rand() % 100; // Random number in the range 0-99
        fprintf(randomNumbersFile,
            "%d\n", randomNumber);
    }

    fclose(randomNumbersFile);
    printf("Random numbers saved in random_numbers.txt.\n");

    // Read random numbers from file and insert them into AVL tree
    randomNumbersFile = fopen("random_numbers.txt", "r");
    if (randomNumbersFile == NULL) {
        printf("Failed to open random_numbers.txt for reading.\n");
        return 1;
    }

    while (fscanf(randomNumbersFile, "%d", &key) == 1) {
        root = insert(root, key);
    }

    fclose(randomNumbersFile);
    printf("Numbers inserted into AVL tree.\n");

    while (1) {
        printf("\n Select the option \n");
        printf("1. Insert a node\n");
        printf("2. Delete a node\n");
        printf("3. Display the tree\n");
        printf("4. Save preorder traversal to file\n");
        printf("5. Save inorder traversal to file\n");
        printf("6. Save postorder traversal to file\n");
        printf("7. Display nodes at each level\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the key to be inserted: ");
                scanf("%d", &key);
                root = insert(root, key);
                printf("Node inserted successfully!\n");
                break;

            case 2:
                printf("Enter the key to be deleted: ");
                scanf("%d", &key);
                root = delete(root, key);
                printf("Node deleted successfully!\n");
                break;

            case 3:
                printf("Tree structure:\n");
                displayTree(root, 0);
                break;

            case 4: {
                FILE* preorderFile = fopen("preorder.txt", "w");
                if (preorderFile == NULL) {
                    printf("Failed to open preorder.txt for writing.\n");
                    return 1;
                }
                saveTraversalToFile(root, preorderFile);
                fclose(preorderFile);
                printf("Preorder traversal saved in preorder.txt.\n");
                break;
            }

            case 5: {
                FILE* inorderFile = fopen("inorder.txt", "w");
                if (inorderFile == NULL) {
                    printf("Failed to open inorder.txt for writing.\n");
                    return 1;
                }
                saveTraversalToFile(root, inorderFile);
                fclose(inorderFile);
                printf("Inorder traversal saved in inorder.txt.\n");
                break;
            }

            case 6: {
                FILE* postorderFile = fopen("postorder.txt", "w");
                if (postorderFile == NULL) {
                    printf("Failed to open postorder.txt for writing.\n");
                    return 1;
                }
                saveTraversalToFile(root, postorderFile);
                fclose(postorderFile);
                printf("Postorder traversal saved in postorder.txt.\n");
                break;
            }

            case 7:
               displayNodesAtEachLevel(root);
                break;

            case 8: {

                printf("Exiting the program...\n");
                exit(0);
            }

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
