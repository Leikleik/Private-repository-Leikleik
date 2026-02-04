#include <stdio.h>

#include "list.h"

#define SUCCESS 0
#define FAIL 1

static int test_add_door(void)
{
    int result = SUCCESS;
    struct door first = {1, 0};
    struct door second = {2, 1};
    struct node* root = init(first);
    struct node* added = add_door(root, second);
    if (root == NULL || added == NULL) {
        result = FAIL;
    } else if (root->next != added || added->data.id != second.id) {
        result = FAIL;
    }
    destroy(root);
    return result;
}

static int test_remove_door(void)
{
    int result = SUCCESS;
    struct door first = {1, 0};
    struct door second = {2, 0};
    struct door third = {3, 1};
    struct node* root = init(first);
    struct node* middle = add_door(root, second);
    struct node* last = add_door(middle, third);
    root = remove_door(middle, root);
    if (root == NULL || root->next != last) {
        result = FAIL;
    }
    root = remove_door(root, root);
    if (root == NULL || root->data.id != third.id) {
        result = FAIL;
    }
    destroy(root);
    return result;
}

int main(void)
{
    int result = SUCCESS;
    if (test_add_door() == FAIL) {
        result = FAIL;
    }
    if (result == SUCCESS && test_remove_door() == FAIL) {
        result = FAIL;
    }
    printf("%s\n", result == SUCCESS ? "SUCCESS" : "FAIL");
    return result;
}
