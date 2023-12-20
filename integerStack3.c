#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

bool checkParentheses(const char* expression) {
    stack parenStack = createIntegerStack(100); // Use a reasonable size

    for (int i = 0; expression[i] != '\0'; i++) {
        if (expression[i] == '(' || expression[i] == '[' || expression[i] == '{') {
            pushIntegerStack(parenStack, expression[i]);
        } else if (expression[i] == ')' || expression[i] == ']' || expression[i] == '}') {
            if (isIntegerStackEmpty(parenStack)) {
                freeIntegerStack(parenStack);
                return false; // Unmatched closing parenthesis
            }

            char openParen = expression[i] == ')' ? '(' : (expression[i] == ']' ? '[' : '{');
            int poppedValue;
            popIntegerStack(parenStack, &poppedValue);

            if (poppedValue != openParen) {
                freeIntegerStack(parenStack);
                return false; // Mismatched parenthesis
            }
        }
    }

    bool isExpressionValid = isIntegerStackEmpty(parenStack); // If stack is empty, all parentheses matched
    freeIntegerStack(parenStack);
    return isExpressionValid;
}

int main() {
    char expression[100];
    printf("Enter a mathematical expression: ");
    scanf("%[^\n]", expression);

    if (checkParentheses(expression)) {
        printf("Expression has correct matching parentheses.\n");
    } else {
        printf("Expression has incorrect or mismatched parentheses.\n");
    }

    return 0;
}
