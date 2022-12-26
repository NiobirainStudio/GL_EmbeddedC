#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"


// Struct of interest
typedef struct
{//Type           Name           Size  Padding  Struct size
   char*          title;         // 8  0        8
   float          price;         // 4  4        16
   unsigned short page_num;      // 2  2        16
   unsigned short release_year;  // 2  0        16
   char*          lang;          // 8  0        24
   float          weight;        // 4  4        32
} Book;


// Printing function for defined types
void linked_list_print(LinkedList* target) {
   LinkedListNode* current = target->first;

   while (current != NULL)
   {
      Book* item = (Book*)current->data;
      
      printf("Title:             %s\n", item->title);
      printf("Price:             %.2f$\n", item->price);
      printf("Number of pages:   %d\n", item->page_num);
      printf("Release year:      %d\n", item->release_year);
      printf("Language:          %s\n", item->lang);
      printf("Weight:            %.2flb\n\n", item->weight);

      current = current->next;
   }
}


int main()
{
   // Initializing a linked list of books
   LinkedList* l_list = linked_list_create(sizeof(Book));

   // Inserting books
   Book* b1 = malloc(sizeof(Book));
   b1->title = "Harry Potter and the Sorcerer's Stone";
   b1->price = 12.0f;
   b1->page_num = 309;
   b1->release_year = 1997;
   b1->lang = "English";
   b1->weight = 1.55f;
   linked_list_append(l_list, b1);

   Book* b2 = malloc(sizeof(Book));
   b2->title = "Harry Potter and the Chamber of Secrets";
   b2->price = 15.0f;
   b2->page_num = 341;
   b2->release_year = 1998;
   b2->lang = "English";
   b2->weight = 1.14f;
   linked_list_append(l_list, b2);

   Book* b3 = malloc(sizeof(Book));
   b3->title = "Harry Potter and the Prisoner of Azkaban";
   b3->price = 10.50f;
   b3->page_num = 435;
   b3->release_year = 1999;
   b3->lang = "English";
   b3->weight = 2.05f;
   linked_list_append(l_list, b3);

   Book* b4 = malloc(sizeof(Book));
   b4->title = "Harry Potter and the Goblet of Fire";
   b4->price = 11.99f;
   b4->page_num = 752;
   b4->release_year = 2000;
   b4->lang = "English";
   b4->weight = 2.47f;
   linked_list_append(l_list, b4);

   Book* b5 = malloc(sizeof(Book));
   b5->title = "Harry Potter and the Order of the Phoenix";
   b5->price = 9.99f;
   b5->page_num = 766;
   b5->release_year = 2003;
   b5->lang = "English";
   b5->weight = 1.6f;
   linked_list_append(l_list, b5);

   Book* b6 = malloc(sizeof(Book));
   b6->title = "Harry Potter and the Half-Blood Prince";
   b6->price = 8.56f;
   b6->page_num = 672;
   b6->release_year = 2005;
   b6->lang = "English";
   b6->weight = 2.2f;
   linked_list_append(l_list, b6);

   Book* b7 = malloc(sizeof(Book));
   b7->title = "Harry Potter and the The Deathly Hallows";
   b7->price = 18.42f;
   b7->page_num = 607;
   b7->release_year = 2007;
   b7->lang = "English";
   b7->weight = 1.33f;
   linked_list_append(l_list, b7);

   Book* b8 = malloc(sizeof(Book));
   b8->title = "Harry Potter and the Cursed Child, Parts One and Two";
   b8->price = 9.98f;
   b8->page_num = 336;
   b8->release_year = 2016;
   b8->lang = "English";
   b8->weight = 0.5f;
   linked_list_append(l_list, b8);

   // Printing the list
   linked_list_print(l_list);

   // Freeing up memory
   linked_list_free(l_list);

   return 0;
}