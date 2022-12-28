#include "binary_tree.c"
#include "stack.c"
#include <string.h>

#define bool int
#define true 1
#define false 0

#define TAMANHO 100

bool is_number(char str[])
{
    char numbers[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

    for (int i = 0; i < strlen(str); i++)
    {
        bool digit = false;
        for (int j = 0; j < 10; j++)
        {
            if (str[i] == numbers[j])
            {
                digit = true;
                break;
            }
        }
        if (!digit)
        {
            return false;
        }
    }
    return true;
}

void generate_tree(binary_tree **tree, char expression[])
{
    stack *values = NULL;
    int partition_size = 0, final_value;
    char *current_partition = malloc(sizeof(char) * partition_size + 1);
    for (int i = 0; i < strlen(expression); i++)
    {
        if (expression[i] == ' ' || expression[i + 1] == '\0')
        {
            if (expression[i + 1] == '\0')
            {
                current_partition[partition_size] = expression[i];
            }
            if (is_number(current_partition))
            {
                push(&values, atoi(current_partition));
            }
            else
            {
                if ((*tree) == NULL)
                {
                    (*tree) = create_leaf(current_partition[0], true);
                    (*tree)->right = create_leaf(pop(&values), false);
                    (*tree)->left = create_leaf(pop(&values), false);
                }
                else
                {
                    binary_tree *new_root = create_leaf(current_partition[0], true);
                    new_root->left = (*tree);
                    new_root->right = create_leaf(pop(&values), false);
                    (*tree) = new_root;
                }
            }

            free(current_partition);
            partition_size = 0;
            current_partition = malloc(sizeof(char) * partition_size + 1);
        }
        else
        {
            current_partition[partition_size] = expression[i];
            partition_size++;
            current_partition = realloc(current_partition, sizeof(char) * partition_size + 1);
            current_partition[partition_size] = '\0';
        }
    }
}

void stack_operations(binary_tree *tree, stack **stack)
{
    if (tree == NULL)
    {
        return;
    }
    stack_operations(tree->left, stack);
    stack_operations(tree->right, stack);

    if (tree->operator)
    {
        int b = pop(stack);
        int a = pop(stack);

        switch (tree->value)
        {
        case '+':
            push(stack, a + b);
            break;
        case '-':
            push(stack, a - b);
            break;
        case '*':
            push(stack, a * b);
            break;
        case '/':
            push(stack, a / b);
            break;
        default:
            printf("Invalid Operator!");
            exit(0);
            break;
        }
    }
    else
    {
        push(stack, tree->value);
    }
}

int calculate(char expression[])
{
    binary_tree *tree = NULL;
    generate_tree(&tree, expression);
    stack *values = NULL;
    stack_operations(tree, &values);
    return values->value;
}

int main()
{
    char expressao[TAMANHO];
    printf("> Digite a expressao: ");
    fflush(stdin);
    scanf("%[^\n]%*c", expressao);
    printf("Resultado: %d\n", calculate(expressao));
}