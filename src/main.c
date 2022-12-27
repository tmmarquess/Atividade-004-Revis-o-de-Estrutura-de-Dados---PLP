#include "stack.c"
#include "hash_table.c"

int main()
{
    stack *new = NULL;
    load_stack_from_txt(&new, "arq_teste.txt");
    print_stack(new);

    hash_table table;
    init_table(table);
    load_table_from_txt(table, "arq_teste.txt");
    print_table(table);
}