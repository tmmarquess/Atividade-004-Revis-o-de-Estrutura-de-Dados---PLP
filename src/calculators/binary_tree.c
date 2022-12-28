#include <stdio.h>
#include <stdlib.h>

#define bool int
#define true 1
#define false 0

typedef struct binary_tree
{
    int value;
    bool operator;
    struct binary_tree *left;
    struct binary_tree *right;
} binary_tree;

binary_tree *create_leaf(int value, bool operator)
{
    binary_tree *new = malloc(sizeof(binary_tree));
    new->left = NULL;
    new->right = NULL;
    new->value = value;
    new->operator= operator;
}

void print_tree_in_order(binary_tree *root)
{
    if (root == NULL)
        return;

    print_tree_in_order(root->left);
    print_tree_in_order(root->right);
    if (root->operator)
    {
        printf("%c ", root->value);
    }
    else
    {
        printf("%d ", root->value);
    }

    
}

void print_tree(binary_tree *root)
{
    printf("\n");
    print_tree_in_order(root);
    printf("\n");
}
