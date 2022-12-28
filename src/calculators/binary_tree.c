#include <stdio.h>
#include <stdlib.h>

#define bool int
#define true 1
#define false 0

typedef struct binary_tree
{
    int value;
    struct binary_tree *left;
    struct binary_tree *right;
} binary_tree;

binary_tree *create_leaf(int value)
{
    binary_tree *new = malloc(sizeof(binary_tree));
    new->left = NULL;
    new->right = NULL;
    new->value = value;
}

void insert_leaf(binary_tree **root, int value)
{
    if ((*root) == NULL)
    {
        (*root) = create_leaf(value);
    }
    else
    {
        if (value <= (*root)->value)
        {
            insert_leaf(&((*root)->left), value);
        }
        else
        {
            insert_leaf(&((*root)->right), value);
        }
    }
}

bool remove_node(binary_tree **root, int value)
{
    binary_tree *to_be_removed = *(root), *before;
    while (to_be_removed != NULL && to_be_removed->value != value)
    {
        before = to_be_removed;
        if (value <= to_be_removed->value)
        {
            to_be_removed = to_be_removed->left;
        }
        else
        {
            to_be_removed = to_be_removed->right;
        }
    }

    if (to_be_removed == NULL)
    {
        return false;
    }

    if (to_be_removed->left == NULL && to_be_removed->right == NULL)
    {
        if (value <= before->value)
        {
            before->left = NULL;
        }
        else
        {
            before->right = NULL;
        }
    }
    else
    {
        if (to_be_removed->left == NULL || to_be_removed->right == NULL)
        {
            if (to_be_removed->left == NULL)
            {
                if (value <= before->value)
                {
                    before->left = to_be_removed->right;
                }
                else
                {
                    before->right = to_be_removed->right;
                }
            }
            else
            {
                if (value <= before->value)
                {
                    before->left = to_be_removed->left;
                }
                else
                {
                    before->right = to_be_removed->left;
                }
            }
        }
        else
        {
            binary_tree *substitute = to_be_removed->right;
            binary_tree *most_left = substitute->left;
            if (most_left == NULL)
            {
                substitute->left = to_be_removed->left;
            }
            else
            {
                while (most_left->left != NULL)
                {
                    most_left = most_left->left;
                }
                most_left->left = to_be_removed->left;
            }

            if (value <= before->value)
            {
                before->left = substitute;
            }
            else
            {
                before->right = substitute;
            }
        }
    }
    free(to_be_removed);
    return true;
}

void print_tree_in_order(binary_tree *root)
{
    if (root == NULL)
        return;

    print_tree_in_order(root->left);
    printf("%d ", root->value);
    print_tree_in_order(root->right);
}

void print_tree(binary_tree *root)
{
    printf("\n");
    print_tree_in_order(root);
    printf("\n");
}

void load_tree_from_txt(binary_tree **root, char filename[])
{
    FILE *file;
    file = fopen(filename, "r");

    if (file == NULL)
    {
        printf("can't open %s", filename);
        return;
    }

    int number_size = 0;
    char *value = malloc(sizeof(char) * (number_size + 1)), current;
    do
    {
        current = fgetc(file);
        if (current != ' ' && current != EOF)
        {
            value[number_size] = current;
            number_size++;
            value = realloc(value, sizeof(number_size + 1));
        }
        else
        {
            insert_leaf(root, atoi(value));
            free(value);
            number_size = 0;
            value = malloc(sizeof(char) * (number_size + 1));
        }

    } while (current != EOF);

    fclose(file);
}