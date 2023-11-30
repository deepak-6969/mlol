#include <stdio.h>
#include <stdlib.h>

#define MAX_ROOMS 5

struct Stack {
    int top;
    unsigned capacity;
    int* array;
};

struct Stack* createStack(unsigned capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}

int isStackEmpty(struct Stack* stack) {
    return stack->top == -1;
}

int isStackFull(struct Stack* stack) {
    return stack->top == stack->capacity - 1;
}

void push(struct Stack* stack, int item) {
    if (!isStackFull(stack)) {
        stack->array[++stack->top] = item;
    } else {
        printf("Stack overflow\n");
    }
}

int pop(struct Stack* stack) {
    if (!isStackEmpty(stack)) {
        return stack->array[stack->top--];
    }
    printf("Stack underflow\n");
    return -1;
}

void convertDecimalToBinary(int decimal) {
    struct Stack* forwardStack = createStack(MAX_ROOMS);
    struct Stack* backwardStack = createStack(MAX_ROOMS);

    // Move forward
    for (int i = 1; i <= MAX_ROOMS; i++) {
        push(forwardStack, i);
    }

    // Move backward and convert decimal to binary
    while (!isStackEmpty(forwardStack)) {
        int room = pop(forwardStack);
        push(backwardStack, room);

        if (room == 1) {
            // Convert decimal to binary and open the treasure
            printf("Decimal Number in Room 1: %d\n", decimal);
            printf("Binary Representation: ");
            while (decimal > 0) {
                int remainder = decimal % 2;
                push(forwardStack, remainder);
                printf("%d", remainder);
                decimal /= 2;
            }
            printf("\n");
        }
    }

    // Move backward
    while (!isStackEmpty(backwardStack)) {
        int room = pop(backwardStack);
        printf("Moved to Room %d\n", room);
    }

    free(forwardStack->array);
    free(forwardStack);
    free(backwardStack->array);
    free(backwardStack);
}

int main() {
    int decimal;

    // Input decimal number from the box in the last room
    printf("Enter the decimal number written in the box in the last room: ");
    scanf("%d", &decimal);

    // Call function to convert decimal to binary and open the treasure
    convertDecimalToBinary(decimal);

    return 0;
}
