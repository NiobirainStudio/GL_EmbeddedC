#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"


// Struct of interest
typedef struct
{//Type           Name           Size  Padding  Struct size
   //char*          title;         // 8  0        8
   //float          price;         // 4  4        16
   unsigned short page_num;      // 2  2        16
   //unsigned short release_year;  // 2  0        16
   //char*          lang;          // 8  0        24
   //float          weight;        // 4  4        32
} Book;


// Printing section
void linked_list_print_by_arr(LinkedList* target) {
   SizedArray* arr = linked_list_to_arr(target);

   for (unsigned int i = 0; i < arr->length; i++) {
      printf("item: %d\n", ((int*)arr->data)[i]);
   }

   free(arr->data);
   free(arr);
}

void linked_list_print_by_link(LinkedList* target) {
   LinkedListNode* current = target->first;

   while (current != NULL)
   {
      Book* item = (Book*)current->data;
      
      printf("Item: %d\n", item->page_num);

      current = current->next;
   }
}


int main()
{
   LinkedList* l_list = linked_list_create(sizeof(Book));

   Book* b1 = malloc(sizeof(Book));

   //b1->title = "Ass";
   //b1->price = 4.4f;
   b1->page_num = 5;
   //b1->release_year = 1999;
   //b1->lang = "en";
   //b1->weight = 4.1f;

   linked_list_push(l_list, b1);

   //linked_list_print_by_link(l_list);

   linked_list_free(l_list);

   return 0;
}