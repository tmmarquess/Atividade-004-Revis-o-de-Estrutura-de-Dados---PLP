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

int main()
{
    stack *new = NULL;
    print_stack(new);
    enqueue(&new, 5);
    print_stack(new);
    enqueue(&new, 10);
    print_stack(new);
    enqueue(&new, -1);
    print_stack(new);
    printf("apagado = %d\n", dequeue(&new));
    print_stack(new);
    printf("apagado = %d\n", dequeue(&new));
    print_stack(new);
    printf("apagado = %d\n", dequeue(&new));
    print_stack(new);
}