#include <stdio.h>
#include <stdlib.h>

#include "bst.h"

#define SUCCESS 0
#define FAIL 1

static int compare(int left, int right)
{
    return left - right;
}

static void destroy_tree(t_btree* root)
{
    if (root != NULL) {
        destroy_tree(root->left);
        destroy_tree(root->right);
        free(root);
    }
}

static int test_insert_case_one(void)
{
    int result = SUCCESS;
    t_btree* root = bstree_create_node(4);

    bstree_insert(root, 2, compare);
    bstree_insert(root, 6, compare);

    if (root == NULL || root->left == NULL || root->right == NULL) {
        result = FAIL;
    } else if (root->left->item != 2 || root->right->item != 6) {
        result = FAIL;
    }

    destroy_tree(root);
    return result;
}

static int test_insert_case_two(void)
{
    int result = SUCCESS;
    t_btree* root = bstree_create_node(8);

    bstree_insert(root, 3, compare);
    bstree_insert(root, 10, compare);
    bstree_insert(root, 1, compare);
    bstree_insert(root, 6, compare);

    if (root->left == NULL || root->right == NULL) {
        result = FAIL;
    } else if (root->left->left == NULL || root->left->right == NULL) {
        result = FAIL;
    } else if (root->left->left->item != 1 || root->left->right->item != 6 || root->right->item != 10) {
        result = FAIL;
    }

    destroy_tree(root);
    return result;
}

int main(void)
{
    int result = SUCCESS;
    if (test_insert_case_one() == FAIL) {
        result = FAIL;
    }
    if (result == SUCCESS && test_insert_case_two() == FAIL) {
        result = FAIL;
    }

    printf("%s\n", result == SUCCESS ? "SUCCESS" : "FAIL");
    return result;
}
