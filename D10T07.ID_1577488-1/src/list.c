#include <stdlib.h>

#include "list.h"

struct node* init(struct door door)
{
    struct node* root = malloc(sizeof(struct node));
    if (root != NULL) {
        root->data = door;
        root->next = NULL;
    }
    return root;
}

struct node* add_door(struct node* elem, struct door door)
{
    struct node* new_node = NULL;
    if (elem != NULL) {
        new_node = init(door);
        if (new_node != NULL) {
            new_node->next = elem->next;
            elem->next = new_node;
        }
    }
    return new_node;
}

struct node* find_door(int door_id, struct node* root)
{
    struct node* result = NULL;
    for (struct node* current = root; current != NULL && result == NULL; current = current->next) {
        if (current->data.id == door_id) {
            result = current;
        }
    }
    return result;
}

struct node* remove_door(struct node* elem, struct node* root)
{
    struct node* new_root = root;
    if (root != NULL && elem != NULL) {
        if (elem == root) {
            new_root = root->next;
            free(root);
        } else {
            struct node* prev = root;
            while (prev != NULL && prev->next != elem) {
                prev = prev->next;
            }
            if (prev != NULL) {
                prev->next = elem->next;
                free(elem);
            }
        }
    }
    return new_root;
}

void destroy(struct node* root)
{
    struct node* current = root;
    while (current != NULL) {
        struct node* next = current->next;
        free(current);
        current = next;
    }
}
