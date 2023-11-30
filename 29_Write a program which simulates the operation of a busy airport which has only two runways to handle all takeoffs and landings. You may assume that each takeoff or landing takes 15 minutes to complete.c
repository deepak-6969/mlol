#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Structure to represent a runway request
struct RunwayRequest {
    int timestamp;
    char type; // 'L' for landing, 'T' for takeoff
};

// Structure to represent a node in the queue
struct Node {
    struct RunwayRequest data;
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

// Function to enqueue a runway request into the queue
void enqueue(struct Queue* queue, struct RunwayRequest request) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = request;
    newNode->next = NULL;

    if (isQueueEmpty(queue)) {
        queue->front = queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

// Function to dequeue a runway request from the queue
struct RunwayRequest dequeue(struct Queue* queue) {
    struct RunwayRequest emptyRequest = {-1, '\0'}; // Empty request indicating an error

    if (isQueueEmpty(queue)) {
        return emptyRequest;
    }

    struct Node* temp = queue->front;
    struct RunwayRequest request = temp->data;
    queue->front = temp->next;

    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    free(temp);

    return request;
}

// Function to simulate airport activity for 120 minutes
void simulateAirportActivity() {
    struct Queue* takeoffQueue = createQueue();
    struct Queue* landingQueue = createQueue();
    struct RunwayRequest request;
    int currentTime = 0;
    int totalTakeoffs = 0;
    int totalLandings = 0;

    while (currentTime < 120) {
        // Generate runway request every 5 minutes
        if (currentTime % 5 == 0) {
            request.timestamp = currentTime;
            request.type = (rand() % 2 == 0) ? 'L' : 'T'; // 'L' for landing, 'T' for takeoff

            if (request.type == 'L') {
                printf("Request for landing at time %d\n", currentTime);
                enqueue(landingQueue, request);
            } else {
                printf("Request for takeoff at time %d\n", currentTime);
                enqueue(takeoffQueue, request);
            }
        }

        // Process runway requests (15 minutes for each takeoff or landing)
        if (!isQueueEmpty(landingQueue)) {
            request = dequeue(landingQueue);
            printf("Landing at time %d\n", request.timestamp);
            totalLandings++;
            currentTime += 15;
        } else if (!isQueueEmpty(takeoffQueue)) {
            request = dequeue(takeoffQueue);
            printf("Takeoff at time %d\n", request.timestamp);
            totalTakeoffs++;
            currentTime += 15;
        } else {
            currentTime++;
        }
    }

    // Display final queue contents, number of takeoffs, number of landings, and average queue times
    printf("\nFinal Queue Contents:\n");
    printf("Takeoff Queue: ");
    while (!isQueueEmpty(takeoffQueue)) {
        request = dequeue(takeoffQueue);
        printf("(%d, %c) ", request.timestamp, request.type);
    }
    printf("\n");

    printf("Landing Queue: ");
    while (!isQueueEmpty(landingQueue)) {
        request = dequeue(landingQueue);
        printf("(%d, %c) ", request.timestamp, request.type);
    }
    printf("\n");

    printf("\nNumber of Takeoffs Completed: %d\n", totalTakeoffs);
    printf("Number of Landings Completed: %d\n", totalLandings);

    // Free memory for the queues
    while (!isQueueEmpty(takeoffQueue)) {
        dequeue(takeoffQueue);
    }
    while (!isQueueEmpty(landingQueue)) {
        dequeue(landingQueue);
    }

    free(takeoffQueue);
    free(landingQueue);
}

int main() {
    // Seed for random number generation
    srand(time(NULL));

    // Simulate airport activity for 120 minutes
    simulateAirportActivity();

    return 0;
}
