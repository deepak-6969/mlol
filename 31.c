#include <stdio.h>
#include <stdlib.h>

// Define task types
typedef enum {
    DOWNLOAD,
    MUSIC,
    GAME
} TaskType;

// Define a task structure
typedef struct {
    TaskType type;
    char name[20];
} Task;

// Define a node for the priority queue
typedef struct {
    Task task;
    int priority; // Lower value means higher priority
} QueueNode;

// Priority queue functions
typedef struct {
    QueueNode* nodes;
    int capacity;
    int size;
} PriorityQueue;

// Function to initialize the priority queue
PriorityQueue* initializeQueue(int capacity) {
    PriorityQueue* queue = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    queue->nodes = (QueueNode*)malloc(sizeof(QueueNode) * capacity);
    queue->capacity = capacity;
    queue->size = 0;
    return queue;
}

// Function to swap two nodes in the priority queue
void swap(QueueNode* a, QueueNode* b) {
    QueueNode temp = *a;
    *a = *b;
    *b = temp;
}

// Function to heapify the priority queue
void heapify(PriorityQueue* queue, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < queue->size && queue->nodes[left].priority < queue->nodes[smallest].priority) {
        smallest = left;
    }

    if (right < queue->size && queue->nodes[right].priority < queue->nodes[smallest].priority) {
        smallest = right;
    }

    if (smallest != i) {
        swap(&queue->nodes[i], &queue->nodes[smallest]);
        heapify(queue, smallest);
    }
}

// Function to insert a task into the priority queue
void insertTask(PriorityQueue* queue, Task task, int priority) {
    if (queue->size == queue->capacity) {
        printf("Queue is full. Cannot insert more tasks.\n");
        return;
    }

    int i = queue->size;
    queue->size++;
    queue->nodes[i].task = task;
    queue->nodes[i].priority = priority;

    while (i != 0 && queue->nodes[(i - 1) / 2].priority > queue->nodes[i].priority) {
        swap(&queue->nodes[i], &queue->nodes[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// Function to extract the highest priority task from the queue
Task extractTask(PriorityQueue* queue) {
    if (queue->size <= 0) {
        printf("Queue is empty.\n");
        Task emptyTask = { -1, "" };
        return emptyTask;
    }

    if (queue->size == 1) {
        queue->size--;
        return queue->nodes[0].task;
    }

    QueueNode root = queue->nodes[0];
    queue->nodes[0] = queue->nodes[queue->size - 1];
    queue->size--;

    heapify(queue, 0);

    return root.task;
}

// Function to simulate download task
void downloadTask() {
    printf("Downloading document...\n");
    // Simulate download process
}

// Function to simulate music task
void musicTask() {
    printf("Listening to music...\n");
    // Simulate music playback
}

// Function to simulate game task
void gameTask() {
    printf("Playing game...\n");
    // Simulate game playing
}

int main() {
    // Initialize the priority queue
    PriorityQueue* queue = initializeQueue(10);

    // Insert tasks into the priority queue
    insertTask(queue, (Task){DOWNLOAD, "Download Document"}, 0);
    insertTask(queue, (Task){MUSIC, "Listen to Music"}, 1);
    insertTask(queue, (Task){GAME, "Play Game"}, 2);

    // Process tasks in priority order
    while (queue->size > 0) {
        Task currentTask = extractTask(queue);

        // Execute the task based on its type
        switch (currentTask.type) {
            case DOWNLOAD:
                downloadTask();
                break;
            case MUSIC:
                musicTask();
                break;
            case GAME:
                gameTask();
                break;
            default:
                printf("Unknown task type.\n");
        }
    }

    // Free the allocated memory
    free(queue->nodes);
    free(queue);

    return 0;
}
