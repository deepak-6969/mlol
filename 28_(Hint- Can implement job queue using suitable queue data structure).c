#include <stdio.h>
#include <stdlib.h>

// Structure to represent a print job
struct PrintJob {
    int jobId;
    int numPages;
};

// Structure to represent a node in the priority queue
struct Node {
    struct PrintJob data;
    struct Node* next;
};

// Structure to represent a priority queue
struct PriorityQueue {
    struct Node* front;
};

// Function to initialize a priority queue
struct PriorityQueue* createPriorityQueue() {
    struct PriorityQueue* queue = (struct PriorityQueue*)malloc(sizeof(struct PriorityQueue));
    queue->front = NULL;
    return queue;
}

// Function to check if a priority queue is empty
int isPriorityQueueEmpty(struct PriorityQueue* queue) {
    return queue->front == NULL;
}

// Function to enqueue a print job into the priority queue
void enqueue(struct PriorityQueue* queue, struct PrintJob job) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = job;
    newNode->next = NULL;

    if (isPriorityQueueEmpty(queue) || job.numPages < queue->front->data.numPages) {
        newNode->next = queue->front;
        queue->front = newNode;
    } else {
        struct Node* temp = queue->front;
        while (temp->next != NULL && job.numPages >= temp->next->data.numPages) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }
}

// Function to dequeue a print job from the priority queue
struct PrintJob dequeue(struct PriorityQueue* queue) {
    struct PrintJob emptyJob = {-1, -1}; // Empty job indicating an error

    if (isPriorityQueueEmpty(queue)) {
        printf("Priority Queue is empty. Cannot dequeue.\n");
        return emptyJob;
    }

    struct Node* temp = queue->front;
    struct PrintJob job = temp->data;
    queue->front = temp->next;
    free(temp);

    return job;
}

// Function to simulate processing print jobs with a given number of printers
void simulatePrintJobs(int numPrinters) {
    struct PriorityQueue* jobQueue = createPriorityQueue();
    struct PrintJob job;
    int currentTime = 0;

    // Enqueue 100 print jobs with varying number of pages
    for (int i = 1; i <= 100; i++) {
        job.jobId = i;
        job.numPages = rand() % 50 + 1; // Random number of pages between 1 and 50
        enqueue(jobQueue, job);
        printf("Job %d (Pages: %d) added to the queue at time %d\n", job.jobId, job.numPages, currentTime);
        currentTime++;
    }

    // Process print jobs
    while (!isPriorityQueueEmpty(jobQueue)) {
        job = dequeue(jobQueue);
        if (job.jobId == -1) {
            break; // Stop simulation if an error occurs
        }
        printf("Printing Job %d (Pages: %d) at time %d", job.jobId, job.numPages, currentTime);

        // Time required to print the job based on the number of pages and printers
        int timeRequired = (job.numPages / (10 * numPrinters)) + 1;
        currentTime += timeRequired;

        if (numPrinters > 1) {
            printf(" on Printer %d", (job.jobId % numPrinters) + 1);
        }

        printf("\n");
    }

    printf("Total time required to process print jobs with %d printer(s): %d minutes\n\n", numPrinters, currentTime);
}

int main() {
    // Simulate print jobs with 1, 2, and 3 printers
    simulatePrintJobs(1);
    simulatePrintJobs(2);
    simulatePrintJobs(3);

    return 0;
}
