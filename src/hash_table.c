#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define bool int
#define true 1
#define false 0

#define SIZE 21

typedef struct node
{
    int value;
    struct node *next;
} node;

typedef node *hash_table[SIZE];

void init_table(hash_table table)
{
    for (int i = 0; i < SIZE; i++)
    {
        table[i] = NULL;
    }
}

node *new_node(int value)
{
    node *new = malloc(sizeof(node));
    new->value = value;
    new->next = NULL;
    return new;
}

int get_hash(int value)
{
    int hash_value = 0, mod = 10, index = 1, aux;
    char numbers[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    while (value != 0)
    {
        aux = value % 10;
        int ascii = numbers[aux];
        hash_value += (ascii * pow(11, index));
        value -= aux;
        value /= 10;
        index++;
    }
    return hash_value;
}

int get_index(int hash_value)
{
    return hash_value % SIZE;
}

void insert_value_in_table(hash_table table, int value)
{
    int hash_value = get_hash(value);
    int index = get_index(hash_value);
    node *new = new_node(value);

    if (table[index] == NULL)
    {
        table[index] = new;
    }
    else
    {
        node *actual = table[index];
        while (actual->next != NULL)
        {
            actual = actual->next;
        }
        actual->next = new;
    }
}

bool remove_value_from_table(hash_table table, int value)
{
    int hash_value = get_hash(value);
    int index = get_index(hash_value);

    bool value_exists = false;
    node *actual = table[index], *before = NULL;
    while (actual != NULL)
    {
        if (actual->value == value)
        {
            value_exists = true;
            break;
        }
        before = actual;
        actual = actual->next;
    }
    if (value_exists)
    {
        if (before == NULL)
        {
            table[index] = actual->next;
        }
        else
        {
            before->next = actual->next;
        }
        free(actual);
        return true;
    }
    else
    {
        return false;
    }
}

void print_table(hash_table table)
{
    for (int i = 0; i < SIZE; i++)
    {
        bool empty = true;
        printf("[%d] ->", i);
        node *actual = table[i];
        while (actual != NULL)
        {
            printf(" (%d) ->", actual->value);
            actual = actual->next;
            empty = false;
        }
        if (empty)
        {
            printf(" ()");
        }
        printf("\n");
    }
}


void load_table_from_txt(hash_table table, char filename[]){
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
            insert_value_in_table(table, atoi(value));
            free(value);
            number_size = 0;
            value = malloc(sizeof(char) * (number_size + 1));
        }

    } while (current != EOF);

    fclose(file);
}