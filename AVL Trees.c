#include <stdio.h>
#include <stdlib.h>

struct AVLNode {
    int key;
    struct AVLNode* left;
    struct AVLNode* right;
    int height;
};

struct AVLNode* createNode(int key);
struct AVLNode* insertNode(struct AVLNode* root, int key);
struct AVLNode* deleteNode(struct AVLNode* root, int key);
void inorderTraversal(struct AVLNode* root);
struct AVLNode* getRightNode(struct AVLNode* root);
struct AVLNode* getLeftNode(struct AVLNode* root);
struct AVLNode* rightRotate(struct AVLNode* y);
struct AVLNode* leftRotate(struct AVLNode* x);

struct AVLNode* createNode(int key) {
    struct AVLNode* newNode = (struct AVLNode*)malloc(sizeof(struct AVLNode));
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;
    return newNode;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int getHeight(struct AVLNode* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

int getBalanceFactor(struct AVLNode* node) {
    if (node == NULL)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

struct AVLNode* rightRotate(struct AVLNode* y) {
    struct AVLNode* x = y->left;
    struct AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

struct AVLNode* leftRotate(struct AVLNode* x) {
    struct AVLNode* y = x->right;
    struct AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

struct AVLNode* insertNode(struct AVLNode* root, int key) {
    if (root == NULL)
        return createNode(key);

    if (key < root->key)
        root->left = insertNode(root->left, key);
    else if (key > root->key)
        root->right = insertNode(root->right, key);
    else
        return root;

    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;

    int balanceFactor = getBalanceFactor(root);

    if (balanceFactor > 1 && key < root->left->key)
        return rightRotate(root);

    if (balanceFactor < -1 && key > root->right->key)
        return leftRotate(root);

    if (balanceFactor > 1 && key > root->left->key) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balanceFactor < -1 && key < root->right->key) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

struct AVLNode* getMinValueNode(struct AVLNode* root) {
    struct AVLNode* current = root;
    while (current->left != NULL)
        current = current->left;
    return current;
}

struct AVLNode* deleteNode(struct AVLNode* root, int key) {
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == NULL || root->right == NULL) {
            struct AVLNode* temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }
            free(temp);
        } else {
            struct AVLNode* temp = getMinValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }

    if (root == NULL)
        return root;

    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;

    int balanceFactor = getBalanceFactor(root);

    if (balanceFactor > 1 && getBalanceFactor(root->left) >= 0)
        return rightRotate(root);

    if (balanceFactor < -1 && getBalanceFactor(root->right) <= 0)
        return leftRotate(root);

    if (balanceFactor > 1 && getBalanceFactor(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balanceFactor < -1 && getBalanceFactor(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void inorderTraversal(struct AVLNode* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->key);
        inorderTraversal(root->right);
    }
}

struct AVLNode* getRightNode(struct AVLNode* root) {
    if (root != NULL)
        return root->right;
    return NULL;
}

struct AVLNode* getLeftNode(struct AVLNode* root) {
    if (root != NULL)
        return root->left;
    return NULL;
}

int main() {
    struct AVLNode* root = NULL;

    int key;
    printf("Enter keys to insert (enter -1 to stop): ");
    while (scanf("%d", &key) == 1 && key != -1) {
        root = insertNode(root, key);
    }

    printf("Inorder traversal: ");
    inorderTraversal(root);
    printf("\n");

    printf("Enter keys to delete (enter -1 to stop): ");
    while (scanf("%d", &key) == 1 && key != -1) {
        root = deleteNode(root, key);
    }

    printf("Inorder traversal after deletion: ");
    inorderTraversal(root);
    printf("\n");

    return 0;
}
