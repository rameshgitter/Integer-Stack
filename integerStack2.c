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
    int N, M;
    printf("Enter the size of stack1: ");
    scanf("%d", &N);

    printf("Enter the size of stack2: ");
    scanf("%d", &M);

    stack stack1 = createIntegerStack(N);
    stack stack2 = createIntegerStack(M);

    if (stack1 == NULL || stack2 == NULL) {
        printf("Failed to create stacks.\n");
        return 1;
    }

    printf("Enter integers to push into stack1 and stack2 (Enter -1 to stop):\n");
    int value;
    while (1) {
        scanf("%d", &value);
        if (value == -1) {
            break;
        }

        if (!pushIntegerStack(stack1, value)) {
            if (!pushIntegerStack(stack2, value)) {
                printf("Both stacks are full. Cannot push more.\n");
                break;
            }
        }
    }

    printf("Popping elements from stack2:\n");
    int poppedValue;
    while (!isIntegerStackEmpty(stack2)) {
        popIntegerStack(stack2, &poppedValue);
        printf("Popped: %d\n", poppedValue);
    }

    printf("Popping elements from stack1:\n");
    while (!isIntegerStackEmpty(stack1)) {
        popIntegerStack(stack1, &poppedValue);
        printf("Popped: %d\n", poppedValue);
    }

    freeIntegerStack(stack1);
    freeIntegerStack(stack2);
    
    return 0;
}
