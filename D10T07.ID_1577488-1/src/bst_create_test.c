#include <stdio.h>
#include <stdlib.h>

#include "bst.h"

#define SUCCESS 0
#define FAIL 1

static int test_create_node(void)
{
    int result = SUCCESS;
    t_btree* node_a = bstree_create_node(4);
    t_btree* node_b = bstree_create_node(9);

    if (node_a == NULL || node_b == NULL) {
        result = FAIL;
    } else if (node_a->item != 4 || node_b->item != 9) {
        result = FAIL;
    } else if (node_a->left != NULL || node_a->right != NULL || node_b->left != NULL || node_b->right != NULL) {
        result = FAIL;
    }

    free(node_a);
    free(node_b);
    return result;
}

int main(void)
{
    int result = test_create_node();
    printf("%s\n", result == SUCCESS ? "SUCCESS" : "FAIL");
    return result;
}
