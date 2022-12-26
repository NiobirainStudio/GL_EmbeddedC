#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*============================================================//
    LINKED LIST STRUCT PAGE BEGIN
//============================================================*/
// An array of undefined types with size
typedef struct SizedArray {
    void* data;
    unsigned int length;
} SizedArray;

// A single node of a list
typedef struct LinkedListNode {
    struct LinkedListNode* next;    // Ptr to the next node
    void* data;                     // Ptr to node data
} LinkedListNode;

// List head structure
typedef struct LinkedList {
    LinkedListNode* first;   // Ptr to the first node
    unsigned int length;     // Length of the list
    unsigned int type_size;  // Size of the node type
} LinkedList;
/*============================================================//
    LINKED LIST STRUCT PAGE END
//============================================================*/




/*============================================================//
    LINKED LIST FUNCTION PAGE BEGIN
//============================================================*/
// Initializes the list
LinkedList* linked_list_create(unsigned int type_size) {
    LinkedList* list = malloc(sizeof(LinkedList));
    
    if (list != NULL) {
        list->length     = 0;
        list->type_size  = type_size;
        list->first      = NULL;
    }

    return list;
}

// Destroy the entire list
void linked_list_free(LinkedList* target) {
    LinkedListNode* head = target->first;

    while (head != NULL)
    {
        LinkedListNode* node = head;
        head = head->next;
        free(node->data);
        free(node);
    }

    free(target);
}

// Add an element to the head of the list
void linked_list_push(LinkedList* target, void* data) {
    LinkedListNode* new_head = malloc(target->type_size);

    // Memory check
    if (new_head == NULL)
        return;
    
    // Enough memory
    new_head->data = data;
    new_head->next = target->first;

    target->first = new_head;
    target->length++;
}

// Add an element to the tail of the list
void linked_list_append(LinkedList* target, void* data) {
    LinkedListNode* new_head = malloc(target->type_size);

    // Memory check
    if (new_head == NULL)
        return;

    // Enough memory
    new_head->data = data;
    new_head->next = NULL;

    // If the node is first
    if (target->first == NULL) {
        target->first = new_head;
        
    } else {
        LinkedListNode* navi = target->first;
        while (navi->next != NULL)
            navi = navi->next;
        
        navi->next = new_head;
    }

    target->length++;
}

// Convert list to SizedArray
// SizedArray* linked_list_to_arr(LinkedList* target) {
    
//     SizedArray* s_arr = (SizedArray*)malloc(sizeof(SizedArray));
//     s_arr->data = malloc(target->length * target->type_size);
//     s_arr->length = target->length;

//     LinkedListNode* node = target->first;


//     for (unsigned int i = 0; i < target->length; i++)
//     {
//         memcpy(s_arr->data + i*target->type_size, &node->data, target->type_size);
//         node = node->next;
//     }

//     return s_arr;
// }
/*============================================================//
    LINKED LIST FUNCTION PAGE END
//============================================================*/