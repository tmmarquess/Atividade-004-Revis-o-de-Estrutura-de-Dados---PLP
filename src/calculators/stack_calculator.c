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

int execute_expression(int a, int b, char operator)
{
    int result;
    switch (operator)
    {
    case '+':
        result = a + b;
        break;
    case '-':
        result = a - b;
        break;
    case '/':
        result = a / b;
        break;
    case '*':
        result = a * b;
        break;
    default:
        printf("Invalid Operator!");
        exit(0);
        break;
    }
    return result;
}

int calculate(char expression[])
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
                int a, b;
                b = pop(&values);
                a = pop(&values);
                final_value = execute_expression(a, b, current_partition[0]);
                push(&values, final_value);
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
    return final_value;
}

int main()
{
    char expressao[TAMANHO];
    printf("> Digite a expressao: ");
    fflush(stdin);
    scanf("%[^\n]%*c", expressao);
    printf("Resultado: %d\n", calculate(expressao));
}