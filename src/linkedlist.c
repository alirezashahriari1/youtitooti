#include "linkedlist.h"


LinkedList_ptr create_list() {

    LinkedList_ptr listPtr = malloc(sizeof(LinkedList));
    listPtr->size = 0;
    listPtr->start = NULL;
    listPtr->end = NULL;
    return listPtr;
}


Node_ptr create_node(DATA data) {
    Node_ptr NodePtr = malloc(sizeof(Node));
    NodePtr->data = data;
    NodePtr->next = NULL;
    NodePtr->perv = NULL;

    return NodePtr;
}

bool insert_node(LinkedList_ptr list, Node_ptr node) {

    // Node_ptr current_node = list->start;
    // Node_ptr perv_node = NULL;

    // if (current_node == NULL) {
    //     list->start = node;
    // }

    // while (current_node != NULL) {
    //     perv_node = current_node;
    //     current_node = current_node->next;
    // }

    // current_node = node;
    // current_node->perv = perv_node;
    // if (perv_node != NULL) perv_node->next = current_node;

    // list->end = current_node;

    node->perv = list->end;

    if (!is_empty_list(list))
    {
        list->end->next = node;
    }

    list->end = node;

    if (is_empty_list(list))
    {
        list->start = node;
    }


    list->size++;

    return true;
}

bool contain(LinkedList_ptr listPtr, Node_ptr nodePtr) {
    Node_ptr current_node = listPtr->start;
    Node_ptr perv_node = NULL;

    while (current_node != NULL) {
        if (node_Eq(current_node, nodePtr)) return true;

        perv_node = current_node;
        current_node = current_node->next;
    }

    return false;
}

bool node_Eq(Node_ptr node1, Node_ptr node2) {
    if (node1 == node2)
        return true;

    return false;
}


bool insert_DATA(LinkedList_ptr listPtr, DATA data) {
    Node_ptr nodePtr = create_node(data);
    insert_node(listPtr, nodePtr);
    return true;
}

Node_ptr delete_node(LinkedList_ptr list, uint64_t index) {
    if (index >= list->size) return NULL;

    Node_ptr current_node = list->start;
    Node_ptr perv_node = NULL;
    Node_ptr next_node = NULL;

    for (int i = 0; i < index; ++i) {
        current_node = current_node->next;
    }

    perv_node = current_node->perv;
    next_node = current_node->next;

    if (perv_node != NULL) perv_node->next = next_node;
    if (next_node != NULL) next_node->perv = perv_node;

    if (index == 0)
        list->start = next_node;


    if (index == list->size - 1)
        list->end = perv_node;

    list->size--;
    return current_node;
}

Node_ptr get_data_by_index(LinkedList_ptr listPtr, uint64_t index) {
    if (index >= listPtr->size) return NULL;

    Node_ptr nodePtr = listPtr->start;

    for (int i = 0; i < index; ++i) {
        nodePtr = nodePtr->next;
    }

    return nodePtr;
}


bool is_empty_list(LinkedList_ptr listPtr) {
    return listPtr->size == 0;
}

void clear(LinkedList_ptr listPtr) {

    for (uint64_t i = listPtr->size ; i > 0; --i) {
        Node_ptr node = delete_node(listPtr, 0);
        free(node);

    }
}