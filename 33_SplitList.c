#include <stdio.h>
#include <stdlib.h>

// Node structure for a linked list
struct Node {
    int data;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to print the elements of a linked list
void printList(struct Node* head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

// Function to split a linked list into two halves
void FrontBackSplit(struct Node* source, struct Node** frontRef, struct Node** backRef) {
    if (source == NULL || source->next == NULL) {
        // Handle cases where the length is less than 2
        *frontRef = source;
        *backRef = NULL;
        return;
    }

    struct Node* slow = source;
    struct Node* fast = source->next;

    // Advance 'fast' two nodes, and advance 'slow' one node
    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    // 'slow' is before the midpoint in the list
    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
}

int main() {
    // Create a linked list: 2 -> 3 -> 5 -> 7 -> 11
    struct Node* head = createNode(2);
    head->next = createNode(3);
    head->next->next = createNode(5);
    head->next->next->next = createNode(7);
    head->next->next->next->next = createNode(11);

    printf("Original List: ");
    printList(head);

    // Initialize front and back pointers
    struct Node* front = NULL;
    struct Node* back = NULL;

    // Split the linked list into front and back halves
    FrontBackSplit(head, &front, &back);

    printf("Front List: ");
    printList(front);

    printf("Back List: ");
    printList(back);

    // Free the allocated memory for the linked lists
    while (head != NULL) {
        struct Node* temp = head;
        head = head->next;
        free(temp);
    }

    while (front != NULL) {
        struct Node* temp = front;
        front = front->next;
        free(temp);
    }

    while (back != NULL) {
        struct Node* temp = back;
        back = back->next;
        free(temp);
    }

    return 0;
}
