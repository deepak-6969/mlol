/*10.	Write a Program to create a Binary Search Tree and display its mirror image with and without disturbing the original tree.
 Also display height of a tree using nonrecursion.*/

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

// Function to display a tree levelwise
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

// Function to create a mirror image of the tree without disturbing the original tree
struct TreeNode* createMirrorImage(struct TreeNode* root) {
    if (root == NULL) return NULL;

    struct TreeNode* mirrorRoot = createNode(root->key);

    mirrorRoot->left = createMirrorImage(root->right);
    mirrorRoot->right = createMirrorImage(root->left);

    return mirrorRoot;
}

// Function to create a mirror image of the tree and disturb the original tree
struct TreeNode* createMirrorImageDisturb(struct TreeNode* root) {
    if (root == NULL) return NULL;

    struct TreeNode* mirrorRoot = createNode(root->key);

    root->left = createMirrorImageDisturb(root->right);
    root->right = createMirrorImageDisturb(root->left);

    return mirrorRoot;
}

// Function to find the height of a tree using non-recursion
int findHeight(struct TreeNode* root) {
    if (root == NULL) return 0;

    struct TreeNode* stack[100];
    int heightStack[100];
    int top = -1;

    stack[++top] = root;
    heightStack[top] = 1; // height of the root is 1

    int maxHeight = 0;

    while (top >= 0) {
        struct TreeNode* current = stack[top--];
        int currentHeight = heightStack[top--];

        if (currentHeight > maxHeight) {
            maxHeight = currentHeight;
        }

        if (current->right) {
            stack[++top] = current->right;
            heightStack[top] = currentHeight + 1;
        }

        if (current->left) {
            stack[++top] = current->left;
            heightStack[top] = currentHeight + 1;
        }
    }

    return maxHeight;
}

// Main function
int main() {
    struct TreeNode* root = NULL;
    int choice, key;

    do {
        printf("\nMenu:\n");
        printf("1. Insert\n");
        printf("2. Display Original Tree Levelwise\n");
        printf("3. Display Mirror Image Without Disturbing Original Tree\n");
        printf("4. Display Original Tree Levelwise After Mirror Image Creation\n");
        printf("5. Display Height of Tree\n");
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
                printf("Original Tree Levelwise: ");
                levelwiseDisplay(root);
                break;
            case 3: {
                struct TreeNode* mirrorRoot = createMirrorImage(root);
                printf("Mirror Image Without Disturbing Original Tree: ");
                levelwiseDisplay(mirrorRoot);
                break;
            }
            case 4: {
                struct TreeNode* mirrorRootDisturb = createMirrorImageDisturb(root);
                printf("Original Tree Levelwise After Mirror Image Creation: ");
                levelwiseDisplay(root);
                break;
            }
            case 5:
                printf("Height of Tree: %d\n", findHeight(root));
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
