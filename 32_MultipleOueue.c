#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10

// Structure for a queue
typedef struct {
    int front, rear;
    int array[MAX_SIZE];
} Queue;

// Function to initialize a queue
void initializeQueue(Queue *q) {
    q->front = q->rear = -1;
}

// Function to check if the queue is empty
int isEmpty(Queue *q) {
    return (q->front == -1 && q->rear == -1);
}

// Function to check if the queue is full
int isFull(Queue *q) {
    return ((q->rear + 1) % MAX_SIZE == q->front);
}

// Function to add an element to the queue (Addq)
void enqueue(Queue *q, int value, char queueName) {
    if (isFull(q)) {
        printf("Queue %c is full. Cannot add more elements.\n", queueName);
        return;
    }

    if (isEmpty(q)) {
        q->front = q->rear = 0;
    } else {
        q->rear = (q->rear + 1) % MAX_SIZE;
    }

    q->array[q->rear] = value;
    printf("Added %d to Queue %c.\n", value, queueName);
}

// Function to delete an element from the queue (Delq)
void dequeue(Queue *q, char queueName) {
    if (isEmpty(q)) {
        printf("Queue %c is empty. Cannot delete from an empty queue.\n", queueName);
        return;
    }

    printf("Deleted %d from Queue %c.\n", q->array[q->front], queueName);

    if (q->front == q->rear) {
        // Last element in the queue
        initializeQueue(q);
    } else {
        q->front = (q->front + 1) % MAX_SIZE;
    }
}

// Function to display the contents of the queue
void displayQueue(Queue *q, char queueName) {
    if (isEmpty(q)) {
        printf("Queue %c is empty.\n", queueName);
        return;
    }

    printf("Queue %c: ", queueName);

    int i = q->front;
    do {
        printf("%d ", q->array[i]);
        i = (i + 1) % MAX_SIZE;
    } while (i != (q->rear + 1) % MAX_SIZE);

    printf("\n");
}

int main() {
    Queue queueA, queueB;
    initializeQueue(&queueA);
    initializeQueue(&queueB);

    // Example operations on queues
    enqueue(&queueA, 10, 'A');
    enqueue(&queueA, 20, 'A');
    enqueue(&queueB, 30, 'B');
    enqueue(&queueB, 40, 'B');

    displayQueue(&queueA, 'A');
    displayQueue(&queueB, 'B');

    dequeue(&queueA, 'A');
    enqueue(&queueA, 50, 'A');

    dequeue(&queueB, 'B');
    enqueue(&queueB, 60, 'B');

    displayQueue(&queueA, 'A');
    displayQueue(&queueB, 'B');

    return 0;
}
