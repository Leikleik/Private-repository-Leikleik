#include <stdlib.h>

#include "stack.h"

struct stack* init(int value)
{
    struct stack* head = malloc(sizeof(struct stack));
    if (head != NULL) {
        head->value = value;
        head->next = NULL;
    }
    return head;
}

struct stack* push(struct stack* head, int value)
{
    struct stack* new_head = init(value);
    if (new_head != NULL) {
        new_head->next = head;
    }
    return new_head;
}

int pop(struct stack** head)
{
    int value = 0;
    if (head != NULL && *head != NULL) {
        struct stack* next = (*head)->next;
        value = (*head)->value;
        free(*head);
        *head = next;
    }
    return value;
}

void destroy(struct stack* head)
{
    struct stack* current = head;
    while (current != NULL) {
        struct stack* next = current->next;
        free(current);
        current = next;
    }
}
