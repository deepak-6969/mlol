#include <stdio.h>
#include <stdlib.h>

// Structure to represent a stack
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

// Function to calculate the factorial of a number using a stack
unsigned long long factorial(int n) {
    struct Stack* stack = createStack(n);
    unsigned long long result = 1;

    while (n > 1) {
        push(stack, n--);
    }

    while (!isStackEmpty(stack)) {
        result *= pop(stack);
    }

    free(stack->array);
    free(stack);

    return result;
}

// Function to generate Fibonacci series using a stack
void fibonacciSeries(int n) {
    struct Stack* stack = createStack(n);
    int a = 0, b = 1;

    printf("Fibonacci Series: ");

    for (int i = 0; i < n; i++) {
        printf("%d ", a);
        push(stack, a);
        int next = a + b;
        a = b;
        b = next;
    }

    printf("\n");

    // Display Fibonacci series using stack
    printf("Fibonacci Series using Stack: ");
    while (!isStackEmpty(stack)) {
        printf("%d ", pop(stack));
    }

    free(stack->array);
    free(stack);
}

int main() {
    int num;

    // Calculate factorial
    printf("Enter a number to calculate its factorial: ");
    scanf("%d", &num);
    printf("Factorial of %d: %llu\n", num, factorial(num));

    // Generate Fibonacci series
    printf("\nEnter the number of terms for Fibonacci series: ");
    scanf("%d", &num);
    fibonacciSeries(num);

    return 0;
}
