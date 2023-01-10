#ifndef YOUTITOOTI_LINKEDLIST_H
#define YOUTITOOTI_LINKEDLIST_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

#define DATA void*

typedef struct Node Node;
typedef Node* Node_ptr;



struct Node {
    DATA data;
    Node_ptr next;
    Node_ptr perv;
};


typedef struct LinkedList {
    Node_ptr start;
    Node_ptr end;
    uint64_t size;
} LinkedList;

typedef LinkedList* LinkedList_ptr;


LinkedList_ptr create_list();

Node_ptr create_node(DATA data);

bool insert_node(LinkedList_ptr list,Node_ptr node);

bool insert_DATA(LinkedList_ptr listPtr, DATA data);

Node_ptr delete_node(LinkedList_ptr list,uint64_t index);

bool contain(LinkedList_ptr listPtr, Node_ptr nodePtr);

bool node_Eq(Node_ptr node1, Node_ptr node2);

Node_ptr get_data_by_index(LinkedList_ptr listPtr,uint64_t index);

bool is_empty_list(LinkedList_ptr listPtr);

void clear(LinkedList_ptr listPtr);




#endif //YOUTITOOTI_LINKEDLIST_H
