#include <stdio.h>
#include <stdlib.h>

// Structure to represent a node in the queue
struct Node {
    int data;
    struct Node* next;
};

// Structure to represent a queue
struct Queue {
    struct Node* front;
    struct Node* rear;
};

// Function to initialize a queue
struct Queue* createQueue() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = queue->rear = NULL;
    return queue;
}

// Function to check if a queue is empty
int isQueueEmpty(struct Queue* queue) {
    return queue->front == NULL;
}

// Function to enqueue a passenger into the queue
void enqueue(struct Queue* queue, int passenger) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = passenger;
    newNode->next = NULL;

    if (isQueueEmpty(queue)) {
        queue->front = queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

// Function to dequeue a passenger from the queue
int dequeue(struct Queue* queue) {
    if (isQueueEmpty(queue)) {
        printf("Queue is empty. Cannot dequeue.\n");
        return -1;
    }

    struct Node* temp = queue->front;
    int passenger = temp->data;
    queue->front = temp->next;

    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    free(temp);
    return passenger;
}

// Function to simulate serving passengers and calculate average waiting time
void simulateAirlineService(struct Queue* regularQueue, struct Queue* frequentQueue, int numCustomers, int numFrequentFlyers) {
    int totalTime = 0;
    int currentTime = 0;

    // Enqueue regular customers
    for (int i = 1; i <= numCustomers; i++) {
        enqueue(regularQueue, i);
    }

    // Enqueue frequent flyers
    for (int i = 1; i <= numFrequentFlyers; i++) {
        enqueue(frequentQueue, i);
    }

    printf("Simulation Results:\n");

    // Serve regular customers first
    while (!isQueueEmpty(regularQueue)) {
        int passenger = dequeue(regularQueue);
        printf("Serving Regular Passenger %d at time %d\n", passenger, currentTime);
        totalTime += currentTime;
        currentTime++;
    }

    // Serve frequent flyers next
    currentTime = 0; // Reset time for frequent flyers
    while (!isQueueEmpty(frequentQueue)) {
        int passenger = dequeue(frequentQueue);
        printf("Serving Frequent Flyer %d at time %d\n", passenger, currentTime);
        totalTime += currentTime;
        currentTime++;
    }

    // Calculate and display average waiting time
    int totalPassengers = numCustomers + numFrequentFlyers;
    double averageWaitingTime = (double)totalTime / totalPassengers;
    printf("\nAverage Waiting Time: %.2f\n", averageWaitingTime);
}

int main() {
    int numRegularCustomers, numFrequentFlyers;

    printf("Enter the number of regular customers: ");
    scanf("%d", &numRegularCustomers);

    printf("Enter the number of frequent flyers: ");
    scanf("%d", &numFrequentFlyers);

    struct Queue* regularQueue = createQueue();
    struct Queue* frequentQueue = createQueue();

    simulateAirlineService(regularQueue, frequentQueue, numRegularCustomers, numFrequentFlyers);

    return 0;
}
