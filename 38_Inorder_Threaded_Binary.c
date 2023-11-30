#include <stdio.h>
#include <stdlib.h>

// Node structure for a threaded binary tree
struct ThreadedNode {
    int data;
    struct ThreadedNode* left;
    struct ThreadedNode* right;
    int isThreaded; // Flag indicating if the right pointer is a thread
};

// Function to create a new threaded node
struct ThreadedNode* createNode(int data) {
    struct ThreadedNode* newNode = (struct ThreadedNode*)malloc(sizeof(struct ThreadedNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->isThreaded = 0; // Initially, the right pointer is not a thread
    return newNode;
}

// Function to perform threaded tree traversal (Postorder)
void threadedPostorderTraversal(struct ThreadedNode* root) {
    if (root == NULL) {
        return;
    }

    struct ThreadedNode* current = root;
    struct ThreadedNode* prev = NULL;

    while (current != NULL) {
        // If the node has a left child, move to the left child
        if (current->left != NULL) {
            current = current->left;
        } else {
            // If the node has a right child, move to the right child
            if (current->right != NULL && !current->isThreaded && current->right != prev) {
                current = current->right;
            } else {
                // Process the node
                printf("%d ", current->data);

                // Move to the parent if the right pointer is threaded or has been processed
                prev = current;
                current = current->isThreaded ? NULL : current->right;
            }
        }
    }
}

// Function to create threaded nodes from a regular binary tree
void createThreadedNodes(struct ThreadedNode* root, struct ThreadedNode** prev) {
    if (root == NULL) {
        return;
    }

    // Recursively create threaded nodes for the right and left subtrees
    createThreadedNodes(root->right, prev);

    // Thread the current node to its in-order successor
    if (root->right == NULL) {
        root->right = *prev;
        root->isThreaded = 1; // Mark the right pointer as a thread
    }

    // Update the predecessor to the current node
    *prev = root;

    // Recursively create threaded nodes for the left subtree
    createThreadedNodes(root->left, prev);
}

// Function to convert a regular binary tree to a threaded binary tree
void createThreadedTree(struct ThreadedNode* root) {
    struct ThreadedNode* prev = NULL;
    createThreadedNodes(root, &prev);
}

int main() {
    // Create a sample binary tree
    struct ThreadedNode* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);

    // Convert the binary tree to a threaded binary tree
    createThreadedTree(root);

    // Perform threaded Postorder traversal and display the result
    printf("Threaded Postorder Traversal: ");
    threadedPostorderTraversal(root);
    printf("\n");

    // Free the allocated memory for the threaded binary tree
    free(root->left->left);
    free(root->left->right);
    free(root->right->left);
    free(root->right->right);
    free(root->left);
    free(root->right);
    free(root);

    return 0;
}
