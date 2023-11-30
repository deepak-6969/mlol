#include <stdio.h>
#include <stdlib.h>

// Node structure for a doubly linked list
struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the beginning of the doubly linked list
void insertAtBeginning(struct Node** head, int data) {
    struct Node* newNode = createNode(data);

    if (*head == NULL) {
        *head = newNode;
    } else {
        newNode->next = *head;
        (*head)->prev = newNode;
        *head = newNode;
    }
}

// Function to insert a node at the end of the doubly linked list
void insertAtEnd(struct Node** head, int data) {
    struct Node* newNode = createNode(data);

    if (*head == NULL) {
        *head = newNode;
    } else {
        struct Node* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
        newNode->prev = current;
    }
}

// Function to insert a node after a specific node in the doubly linked list
void insertAfter(struct Node* prevNode, int data) {
    if (prevNode == NULL) {
        printf("Previous node cannot be NULL.\n");
        return;
    }

    struct Node* newNode = createNode(data);
    newNode->next = prevNode->next;
    newNode->prev = prevNode;
    
    if (prevNode->next != NULL) {
        prevNode->next->prev = newNode;
    }

    prevNode->next = newNode;
}

// Function to delete a node from the doubly linked list
void deleteNode(struct Node** head, struct Node* targetNode) {
    if (*head == NULL || targetNode == NULL) {
        printf("Invalid deletion.\n");
        return;
    }

    if (*head == targetNode) {
        *head = targetNode->next;
    }

    if (targetNode->next != NULL) {
        targetNode->next->prev = targetNode->prev;
    }

    if (targetNode->prev != NULL) {
        targetNode->prev->next = targetNode->next;
    }

    free(targetNode);
}

// Function to display the doubly linked list
void displayList(struct Node* head) {
    while (head != NULL) {
        printf("%d <-> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

// Function to free memory allocated for the doubly linked list
void freeList(struct Node* head) {
    struct Node* current = head;
    struct Node* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

int main() {
    struct Node* head = NULL;

    // Insert nodes at the beginning
    insertAtBeginning(&head, 3);
    insertAtBeginning(&head, 2);
    insertAtBeginning(&head, 1);

    // Display the doubly linked list
    printf("Doubly Linked List (after inserting at the beginning): ");
    displayList(head);

    // Insert nodes at the end
    insertAtEnd(&head, 4);
    insertAtEnd(&head, 5);

    // Display the doubly linked list
    printf("Doubly Linked List (after inserting at the end): ");
    displayList(head);

    // Insert a node after a specific node (e.g., after the node with data=3)
    struct Node* targetNode = head->next;
    insertAfter(targetNode, 6);

    // Display the doubly linked list
    printf("Doubly Linked List (after inserting after a specific node): ");
    displayList(head);

    // Delete a node (e.g., the node with data=4)
    deleteNode(&head, head->next->next->next);

    // Display the doubly linked list
    printf("Doubly Linked List (after deleting a specific node): ");
    displayList(head);

    // Free the allocated memory for the doubly linked list
    freeList(head);

    return 0;
}
