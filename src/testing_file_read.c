#include "stack.c"
#include "hash_table.c"
#include "binary_tree.c"

int main()
{
    printf(">>Stack<<\n");
    stack *new = NULL;
    load_stack_from_txt(&new, "arq_teste.txt");
    print_stack(new);

    printf("\n>>Hash Table<<\n");
    hash_table table;
    init_table(table);
    load_table_from_txt(table, "arq_teste.txt");
    print_table(table);

    printf("\n>>Binary Tree<<\n");
    binary_tree *root = NULL;
    load_tree_from_txt(&root, "arq_teste.txt");
    print_tree(root);
}