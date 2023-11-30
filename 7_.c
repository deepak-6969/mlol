/*7.	Write a Program to create a Binary Search Tree and perform following nonrecursive operations on it.
 a. Preorder Traversal b. Postorder Traversal c. Display total Number of Nodes d. Display Leaf nodes.

*/

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

    if (key < root->key) {
        root->left = insert(root->left, key);
    } else if (key > root->key) {
        root->right = insert(root->right, key);
    }

    return root;
}

// Function to perform non-recursive preorder traversal
void preorderTraversal(struct TreeNode* root) {
    if (root == NULL) return;

    struct TreeNode* stack[100];
    int top = -1;

    stack[++top] = root;

    while (top >= 0) {
        struct TreeNode* current = stack[top--];
        printf("%d ", current->key);

        if (current->right)
            stack[++top] = current->right;
        if (current->left)
            stack[++top] = current->left;
    }
}

// Function to perform non-recursive postorder traversal
void postorderTraversal(struct TreeNode* root) {
    if (root == NULL) return;

    struct TreeNode* stack1[100];
    struct TreeNode* stack2[100];
    int top1 = -1, top2 = -1;

    stack1[++top1] = root;

    while (top1 >= 0) {
        struct TreeNode* current = stack1[top1--];
        stack2[++top2] = current;

        if (current->left)
            stack1[++top1] = current->left;
        if (current->right)
            stack1[++top1] = current->right;
    }

    while (top2 >= 0) {
        printf("%d ", stack2[top2--]->key);
    }
}

// Function to display total number of nodes
int countNodes(struct TreeNode* root) {
    if (root == NULL) return 0;

    struct TreeNode* stack[100];
    int top = -1;
    int count = 0;

    stack[++top] = root;

    while (top >= 0) {
        struct TreeNode* current = stack[top--];
        count++;

        if (current->right)
            stack[++top] = current->right;
        if (current->left)
            stack[++top] = current->left;
    }

    return count;
}

// Function to display leaf nodes
void displayLeafNodes(struct TreeNode* root) {
    if (root == NULL) return;

    struct TreeNode* stack[100];
    int top = -1;

    stack[++top] = root;

    while (top >= 0) {
        struct TreeNode* current = stack[top--];

        if (current->left == NULL && current->right == NULL) {
            printf("%d ", current->key);
        }

        if (current->right)
            stack[++top] = current->right;
        if (current->left)
            stack[++top] = current->left;
    }
}

// Main function
int main() {
    struct TreeNode* root = NULL;
    int choice, key;

    do {
        printf("\nMenu:\n");
        printf("1. Insert\n");
        printf("2. Preorder Traversal\n");
        printf("3. Postorder Traversal\n");
        printf("4. Display Total Number of Nodes\n");
        printf("5. Display Leaf Nodes\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                root = insert(root, key);
                break;
            case 2:
                printf("Preorder Traversal: ");
                preorderTraversal(root);
                printf("\n");
                break;
            case 3:
                printf("Postorder Traversal: ");
                postorderTraversal(root);
                printf("\n");
                break;
            case 4:
                printf("Total Number of Nodes: %d\n", countNodes(root));
                break;
            case 5:
                printf("Leaf Nodes: ");
                displayLeafNodes(root);
                printf("\n");
                break;
            case 6:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 6);

    return 0;
}
