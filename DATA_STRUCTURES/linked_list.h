#include <stdio.h>
#include <stdlib.h>
typedef struct List
{
    void *element;
    struct List *next;
} List;

void *element_at(List *list, int index)
{
    // If index == 0 return first element.
    if (index == 0)
        return list->element;
    // If index is last, but index isn't 0 throw error.
    if (list->next == NULL)
    {
        fprintf(stderr, "Index out of range %d.", index);
        return NULL;
    }
    return element_at(list->next, index - 1);
}

void insert_element(List *list, void *element)
{
    List *new_list = (List *)malloc(sizeof(List));
    new_list->element = element;
    new_list->next = list;
    list = new_list;
}

void append_element(List *list, void *element)
{
    List *last = (List *)malloc(sizeof(List));
    last->element = element;
    last->next = NULL;
    while (list->next != NULL)
        list = list->next;
    list->next = last;
}

void extend_array(List *list1, List *list2)
{
    while (list1->next != NULL)
        list1 = list1->next;
    list1->next = list2;
}

int length_of_list(List *list)
{
    int length;
    // While list has next element add one to length.
    for (length = 1; (list = list->next) != NULL; length++)
        ;
    return length;
}
