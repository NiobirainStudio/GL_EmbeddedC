#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*============================================================//
    LINKED LIST STRUCT PAGE BEGIN
//============================================================*/
typedef struct SizedArray {
    void* data;
    unsigned int length;
} SizedArray;

typedef struct LinkedListNode {
    struct LinkedListNode* next;   // Ptr to the next node
    void* data;             // Ptr to node data
} LinkedListNode;

typedef struct LinkedList {
    LinkedListNode* first;   // Ptr to the first node
    unsigned int length;     // Length of the list
    unsigned int type_size;  // Size of the node type
} LinkedList;
/*============================================================//
    LINKED LIST STRUCTS END
//============================================================*/




/*============================================================//
    LINKED LIST FUNCTION PAGE BEGIN
//============================================================*/
LinkedList* linked_list_create(unsigned int type_size) {
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedListNode));
    list->length     = 0;
    list->type_size  = type_size;
    list->first      = NULL;
    return list;
}

void linked_list_free(LinkedList* target) {
    LinkedListNode* current = target->first;
    LinkedListNode* next = NULL;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }

    free(target);
}

void linked_list_push(LinkedList* target, void* data) {
    LinkedListNode* prev_start = target->first;
    LinkedListNode* new_start = (LinkedListNode*)malloc(target->type_size);

    new_start->data = data;
    new_start->next = prev_start;

    target->first = new_start;
    target->length++;
}

SizedArray* linked_list_to_arr(LinkedList* target) {
    
    SizedArray* s_arr = (SizedArray*)malloc(sizeof(SizedArray));
    s_arr->data = malloc(target->length * target->type_size);
    s_arr->length = target->length;

    LinkedListNode* node = target->first;


    for (unsigned int i = 0; i < target->length; i++)
    {
        memcpy(s_arr->data + i*target->type_size, &node->data, target->type_size);
        node = node->next;
    }

    return s_arr;
}
/*============================================================//
    LINKED LIST FUNCTION PAGE END
//============================================================*/