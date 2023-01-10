#include "post.h"


Post_ptr new_post(String message) {
    static uint64_t counter = 1;

    Post_ptr postPtr = malloc(sizeof(Post));
    postPtr->message = malloc(sizeof(char) * (string_len(message) + 1));
    strcpy(postPtr->message, message);
    postPtr->likes = 0;
    postPtr->id = counter++;

    counter++;

    return postPtr;
}


void delete_post(Post_ptr postPtr) {
    free(postPtr->message);
    free(postPtr);
}

bool post_message_Eq(Post_ptr p1, Post_ptr p2) {
    return p1->id == p2->id;
}


void remove_post(LinkedList_ptr listPtr, uint64_t index) {
    Post_ptr postPtr = (Post_ptr) delete_node(listPtr, index);
    delete_post(postPtr);
}

Post_ptr get_postfrom_user_with_index(LinkedList_ptr posts, uint64_t index) {
    if (index >= posts->size) return NULL;

    Node_ptr nodePtr = posts->start;

    for (int i = 0; i < index; ++i) {
        nodePtr = nodePtr->next;
    }

    Post_ptr postPtr = (Post_ptr) nodePtr->data;

    return postPtr;
}

