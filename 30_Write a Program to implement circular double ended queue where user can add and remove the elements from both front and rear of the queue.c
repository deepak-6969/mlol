#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 5

// Structure to represent a node in the deque
struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

// Structure to represent a circular double-ended queue
struct Deque {
    struct Node* front;
    struct Node* rear;
};

// Function to initialize a deque
struct Deque* createDeque() {
    struct Deque* deque = (struct Deque*)malloc(sizeof(struct Deque));
    deque->front = deque->rear = NULL;
    return deque;
}

// Function to check if a deque is empty
int isDequeEmpty(struct Deque* deque) {
    return deque->front == NULL;
}

// Function to check if a deque is full
int isDequeFull() {
    return 0; // For a linked-list-based implementation, the deque is not limited in size
}

// Function to add an element to the front of the deque
void addToFront(struct Deque* deque, int data) {
    if (isDequeFull()) {
        printf("Deque is full. Cannot add to the front.\n");
        return;
    }

    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;

    if (isDequeEmpty(deque)) {
        deque->front = deque->rear = newNode;
    } else {
        newNode->next = deque->front;
        deque->front->prev = newNode;
        deque->front = newNode;
    }

    printf("%d added to the front of the deque.\n", data);
}

// Function to add an element to the rear of the deque
void addToRear(struct Deque* deque, int data) {
    if (isDequeFull()) {
        printf("Deque is full. Cannot add to the rear.\n");
        return;
    }

    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;

    if (isDequeEmpty(deque)) {
        deque->front = deque->rear = newNode;
    } else {
        newNode->prev = deque->rear;
        deque->rear->next = newNode;
        deque->rear = newNode;
    }

    printf("%d added to the rear of the deque.\n", data);
}

// Function to remove an element from the front of the deque
void removeFromFront(struct Deque* deque) {
    if (isDequeEmpty(deque)) {
        printf("Deque is empty. Cannot remove from the front.\n");
        return;
    }

    struct Node* temp = deque->front;
    int data = temp->data;

    if (deque->front == deque->rear) {
        deque->front = deque->rear = NULL;
    } else {
        deque->front = temp->next;
        deque->front->prev = NULL;
    }

    free(temp);

    printf("%d removed from the front of the deque.\n", data);
}

// Function to remove an element from the rear of the deque
void removeFromRear(struct Deque* deque) {
    if (isDequeEmpty(deque)) {
        printf("Deque is empty. Cannot remove from the rear.\n");
        return;
    }

    struct Node* temp = deque->rear;
    int data = temp->data;

    if (deque->front == deque->rear) {
        deque->front = deque->rear = NULL;
    } else {
        deque->rear = temp->prev;
        deque->rear->next = NULL;
    }

    free(temp);

    printf("%d removed from the rear of the deque.\n", data);
}

// Function to display the elements in the deque
void displayDeque(struct Deque* deque) {
    if (isDequeEmpty(deque)) {
        printf("Deque is empty.\n");
        return;
    }

    struct Node* current = deque->front;
    printf("Deque: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Function to free the memory used by the deque
void freeDeque(struct Deque* deque) {
    while (!isDequeEmpty(deque)) {
        removeFromFront(deque);
    }
    free(deque);
}

int main() {
    struct Deque* deque = createDeque();

    addToFront(deque, 1);
    addToRear(deque, 2);
    addToFront(deque, 3);
    addToRear(deque, 4);
    displayDeque(deque);

    removeFromFront(deque);
    removeFromRear(deque);
    displayDeque(deque);

    freeDeque(deque);

    return 0;
}
