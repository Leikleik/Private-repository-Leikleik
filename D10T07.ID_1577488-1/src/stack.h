#ifndef STACK_H
#define STACK_H

struct stack {
    int value;
    struct stack* next;
};

struct stack* init(int value);
struct stack* push(struct stack* head, int value);
int pop(struct stack** head);
void destroy(struct stack* head);

#endif  // STACK_H
