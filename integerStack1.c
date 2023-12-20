#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* data;
    int size;
    int top;
} *stack;

stack createIntegerStack(int stackSize) {
    stack s = (stack)malloc(sizeof(struct stack));
    if (s == NULL) {
        return NULL; // Allocation failed
    }

    s->data = (int*)malloc(stackSize * sizeof(int));
    if (s->data == NULL) {
        free(s);
        return NULL; // Allocation failed
    }

    s->size = stackSize;
    s->top = -1; // Stack is empty
    return s;
}

int pushIntegerStack(stack s, int d) {
    if (s == NULL || s->top == s->size - 1) {
        return 0; // Stack is full or invalid
    }

    s->data[++s->top] = d;
    return 1;
}

int popIntegerStack(stack s, int* dp) {
    if (s == NULL || s->top == -1) {
        return 0; // Stack is empty or invalid
    }

    *dp = s->data[s->top--];
    return 1;
}

int freeIntegerStack(stack s) {
    if (s == NULL) {
        return 0; // Invalid stack
    }

    free(s->data);
    free(s);
    return 1;
}

int isIntegerStackFull(stack s) {
    if (s == NULL) {
        return 1; // Invalid stack is considered "full"
    }
    
    return s->top == s->size - 1;
}

int isIntegerStackEmpty(stack s) {
    if (s == NULL) {
        return 1; // Invalid stack is considered "empty"
    }
    
    return s->top == -1;
}

int main() {
    stack myStack = createIntegerStack(5);

    if (myStack == NULL) {
        printf("Failed to create stack.\n");
        return 1;
    }

    for (int i = 1; i <= 5; i++) {
        if (!pushIntegerStack(myStack, i * 10)) {
            printf("Push failed. Stack might be full.\n");
            break;
        }
    }

    int poppedValue;
    while (popIntegerStack(myStack, &poppedValue)) {
        printf("Popped: %d\n", poppedValue);
    }

    freeIntegerStack(myStack);
    
    return 0;
}
