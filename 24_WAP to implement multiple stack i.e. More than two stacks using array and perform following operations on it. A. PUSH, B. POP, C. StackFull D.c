#include <stdio.h>
#include <stdlib.h>

#define MAX_STACKS 5
#define STACK_SIZE 10

struct MultipleStacks {
    int top[MAX_STACKS];
    int data[MAX_STACKS * STACK_SIZE];
};

// Function to initialize multiple stacks
void initialize(struct MultipleStacks* stacks) {
    for (int i = 0; i < MAX_STACKS; i++) {
        stacks->top[i] = -1;
    }
}

// Function to check if a stack is full
int isStackFull(struct MultipleStacks* stacks, int stackNumber) {
    return stacks->top[stackNumber] == STACK_SIZE - 1;
}

// Function to check if a stack is empty
int isStackEmpty(struct MultipleStacks* stacks, int stackNumber) {
    return stacks->top[stackNumber] == -1;
}

// Function to push an element onto a stack
void push(struct MultipleStacks* stacks, int stackNumber, int value) {
    if (!isStackFull(stacks, stackNumber)) {
        int index = stackNumber * STACK_SIZE + stacks->top[stackNumber] + 1;
        stacks->data[index] = value;
        stacks->top[stackNumber]++;
        printf("Pushed %d onto Stack %d\n", value, stackNumber + 1);
    } else {
        printf("Stack %d is full. Cannot push %d.\n", stackNumber + 1, value);
    }
}

// Function to pop an element from a stack
int pop(struct MultipleStacks* stacks, int stackNumber) {
    if (!isStackEmpty(stacks, stackNumber)) {
        int index = stackNumber * STACK_SIZE + stacks->top[stackNumber];
        int value = stacks->data[index];
        stacks->top[stackNumber]--;
        printf("Popped %d from Stack %d\n", value, stackNumber + 1);
        return value;
    } else {
        printf("Stack %d is empty. Cannot pop.\n", stackNumber + 1);
        return -1; // indicating failure
    }
}

// Function to display elements of a stack
void displayStack(struct MultipleStacks* stacks, int stackNumber) {
    printf("Stack %d: ", stackNumber + 1);
    if (!isStackEmpty(stacks, stackNumber)) {
        for (int i = 0; i <= stacks->top[stackNumber]; i++) {
            int index = stackNumber * STACK_SIZE + i;
            printf("%d ", stacks->data[index]);
        }
    } else {
        printf("Empty");
    }
    printf("\n");
}

int main() {
    struct MultipleStacks stacks;
    initialize(&stacks);

    int choice, stackNumber, value;

    do {
        printf("\n1. Push\n2. Pop\n3. Display Stack\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the stack number (1 to %d): ", MAX_STACKS);
                scanf("%d", &stackNumber);
                stackNumber--; // Convert to 0-based index
                if (stackNumber >= 0 && stackNumber < MAX_STACKS) {
                    printf("Enter the value to push: ");
                    scanf("%d", &value);
                    push(&stacks, stackNumber, value);
                } else {
                    printf("Invalid stack number.\n");
                }
                break;
            case 2:
                printf("Enter the stack number (1 to %d): ", MAX_STACKS);
                scanf("%d", &stackNumber);
                stackNumber--; // Convert to 0-based index
                if (stackNumber >= 0 && stackNumber < MAX_STACKS) {
                    pop(&stacks, stackNumber);
                } else {
                    printf("Invalid stack number.\n");
                }
                break;
            case 3:
                for (int i = 0; i < MAX_STACKS; i++) {
                    displayStack(&stacks, i);
                }
                break;
            case 4:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 4);

    return 0;
}
