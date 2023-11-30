/*3.	Write a Program to create a Binary Search Tree holding numeric keys and perform following nonrecursive operations on it.
 a. Levelwise display, b. Mirror image, c. Display height of a tree, d. Find */

 #include <stdio.h>
#include <stdlib.h>

// Define a structure for tree nodes
struct TreeNode {
    int key;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Function to create a new node
struct TreeNode* createNode(int key) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->key = key;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a key into BST
struct TreeNode* insert(struct TreeNode* root, int key) {
    if (root == NULL) {
        return createNode(key);
    }

    struct TreeNode* current = root;
    struct TreeNode* parent = NULL;

    while (current != NULL) {
        parent = current;

        if (key < current->key) {
            current = current->left;
        } else if (key > current->key) {
            current = current->right;
        } else {
            // Duplicate keys are not allowed in a BST
            return root;
        }
    }

    if (key < parent->key) {
        parent->left = createNode(key);
    } else {
        parent->right = createNode(key);
    }

    return root;
}

// Function to perform levelwise display
void levelwiseDisplay(struct TreeNode* root) {
    if (root == NULL) return;

    struct TreeNode* queue[100];
    int front = 0, rear = -1;

    queue[++rear] = root;

    while (front <= rear) {
        struct TreeNode* current = queue[front++];

        printf("%d ", current->key);

        if (current->left)
            queue[++rear] = current->left;
        if (current->right)
            queue[++rear] = current->right;
    }

    printf("\n");
}

// Function to create a mirror image of the BST
struct TreeNode* mirrorImage(struct TreeNode* root) {
    if (root == NULL) return NULL;

    struct TreeNode* current = root;
    struct TreeNode* temp;

    while (current != NULL) {
        temp = current->left;
        current->left = current->right;
        current->right = temp;

        if (current->left)
            current = current->left;
        else
            current = current->right;
    }

    return root;
}

// Function to display height of the tree
int heightOfTree(struct TreeNode* root) {
    if (root == NULL) return 0;

    struct TreeNode* queue[100];
    int front = 0, rear = -1;
    int level = 0;

    queue[++rear] = root;

    while (front <= rear) {
        int nodesAtCurrentLevel = rear - front + 1;

        while (nodesAtCurrentLevel > 0) {
            struct TreeNode* current = queue[front++];
            
            if (current->left)
                queue[++rear] = current->left;
            if (current->right)
                queue[++rear] = current->right;

            nodesAtCurrentLevel--;
        }

        level++;
    }

    return level;
}

// Function to find a key in the BST
struct TreeNode* findKey(struct TreeNode* root, int key) {
    struct TreeNode* current = root;

    while (current != NULL) {
        if (key == current->key) {
            return current;
        } else if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    return NULL;
}

// Main function
int main() {
    // Create a sample Binary Search Tree
    struct TreeNode* root = NULL;
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 70);
    insert(root, 20);
    insert(root, 40);
    insert(root, 60);
    insert(root, 80);

    // Perform operations
    printf("Levelwise Display: ");
    levelwiseDisplay(root);

    printf("Mirror Image: ");
    root = mirrorImage(root);
    levelwiseDisplay(root);

    printf("Height of the Tree: %d\n", heightOfTree(root));

    int keyToFind = 40;
    struct TreeNode* foundNode = findKey(root, keyToFind);
    if (foundNode)
        printf("Key %d found in the tree.\n", keyToFind);
    else
        printf("Key %d not found in the tree.\n", keyToFind);

    return 0;
}
