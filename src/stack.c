#include <stdio.h>
#include <stdlib.h>

typedef struct stack
{
    int value;
    struct stack *next;
} stack;

int stack_size(stack *top)
{
    stack *actual = top;
    int size = 0;
    while (actual != NULL)
    {
        size += 1;
        actual = actual->next;
    }

    return size;
}

stack *new_item(int value)
{
    stack *new = malloc(sizeof(stack));
    new->value = value;
    new->next = NULL;
    return new;
}

void enqueue(stack **top, int value)
{
    stack *new = new_item(value);
    if (stack_size(*(top)) == 0)
    {
        *(top) = new;
    }
    else
    {
        new->next = *(top);
        *(top) = new;
    }
}

int dequeue(stack **top)
{
    if (stack_size(*(top)) != 0)
    {
        stack *item = *(top);
        int value = item->value;
        *(top) = item->next;
        free(item);
        return value;
    }
}

void print_stack(stack *top)
{
    printf("===========================================\n");
    stack *actual = top;
    while (actual != NULL)
    {
        printf("%d ", actual->value);
        actual = actual->next;
    }
    printf("\n===========================================\n");
}

void load_stack_from_txt(stack **top, char filename[])
{
    stack *aux = NULL;
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
            enqueue(&aux, atoi(value));
            free(value);
            number_size = 0;
            value = malloc(sizeof(char) * (number_size + 1));
        }

    } while (current != EOF);

    fclose(file);

    while (stack_size(aux) != 0)
    {
        enqueue(top, dequeue(&aux));
    }
}