#include <stdio.h>
#include <stdlib.h>

#include "bst.h"

#define SUCCESS 0
#define FAIL 1

static int compare(int left, int right)
{
    return left - right;
}

static int output_buffer[32];
static int output_index = 0;

static void save_value(int value)
{
    output_buffer[output_index] = value;
    output_index++;
}

static void print_value(int value)
{
    printf("%d ", value);
}

static void reset_buffer(void)
{
    output_index = 0;
}

static int check_sequence(const int* expected, int expected_size)
{
    int result = SUCCESS;
    if (output_index != expected_size) {
        result = FAIL;
    } else {
        for (int i = 0; i < expected_size && result == SUCCESS; i++) {
            if (output_buffer[i] != expected[i]) {
                result = FAIL;
            }
        }
    }
    return result;
}

static void destroy_tree(t_btree* root)
{
    if (root != NULL) {
        destroy_tree(root->left);
        destroy_tree(root->right);
        free(root);
    }
}

static t_btree* build_test_tree(void)
{
    t_btree* root = bstree_create_node(8);
    if (root != NULL) {
        bstree_insert(root, 3, compare);
        bstree_insert(root, 10, compare);
        bstree_insert(root, 1, compare);
        bstree_insert(root, 6, compare);
    }
    return root;
}

int main(void)
{
    int result = SUCCESS;
    const int infix_expected[] = {1, 3, 6, 8, 10};
    const int prefix_expected[] = {8, 3, 1, 6, 10};
    const int postfix_expected[] = {1, 6, 3, 10, 8};

    t_btree* root = build_test_tree();
    if (root == NULL) {
        result = FAIL;
    }

    if (result == SUCCESS) {
        printf("INFIX: ");
        bstree_apply_infix(root, print_value);
        printf("\n");

        reset_buffer();
        bstree_apply_infix(root, save_value);
        if (check_sequence(infix_expected, 5) == FAIL) {
            result = FAIL;
        }
    }

    if (result == SUCCESS) {
        printf("PREFIX: ");
        bstree_apply_prefix(root, print_value);
        printf("\n");

        reset_buffer();
        bstree_apply_prefix(root, save_value);
        if (check_sequence(prefix_expected, 5) == FAIL) {
            result = FAIL;
        }
    }

    if (result == SUCCESS) {
        printf("POSTFIX: ");
        bstree_apply_postfix(root, print_value);
        printf("\n");

        reset_buffer();
        bstree_apply_postfix(root, save_value);
        if (check_sequence(postfix_expected, 5) == FAIL) {
            result = FAIL;
        }
    }

    destroy_tree(root);
    printf("%s\n", result == SUCCESS ? "SUCCESS" : "FAIL");
    return result;
}
