#include <stdio.h>

#include "stack.h"

#define SUCCESS 0
#define FAIL 1

static int test_push_pop(void)
{
    int result = SUCCESS;
    struct stack* head = init(10);
    head = push(head, 20);
    int value = pop(&head);
    if (value != 20) {
        result = FAIL;
    }
    value = pop(&head);
    if (value != 10) {
        result = FAIL;
    }
    if (head != NULL) {
        result = FAIL;
    }
    head = push(head, 42);
    value = pop(&head);
    if (value != 42 || head != NULL) {
        result = FAIL;
    }
    destroy(head);
    return result;
}

int main(void)
{
    int result = SUCCESS;
    if (test_push_pop() == FAIL) {
        result = FAIL;
    }
    printf("%s\n", result == SUCCESS ? "SUCCESS" : "FAIL");
    return result;
}
