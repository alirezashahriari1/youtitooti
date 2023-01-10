#include "user.h"


User_ptr create_user(String name, String password) {
    User_ptr userPtr = malloc(sizeof(User));
    userPtr->name = malloc(sizeof(name) * string_len(name));
    strcpy(userPtr->name, name);

    userPtr->password = malloc(sizeof(name) * string_len(password));
    strcpy(userPtr->password, password);

    userPtr->posts = create_list();

    return userPtr;
}


void delete_user(User_ptr userPtr) {
    free(userPtr->name);
    free(userPtr->password);

    while (userPtr->posts->size > 0) {
        delete_post((Post_ptr) delete_node(userPtr->posts, 0));
    }
    free(userPtr->posts);
}

bool user_Eq(User_ptr user1, User_ptr user2) {
    return (strcmp(user1->name, user2->name) == 0);
}


User_ptr find_user_from_username(LinkedList_ptr users, String str) {
    User_ptr userPtr = NULL;

    Node_ptr current_node = users->start;

    while (current_node != NULL) {

        userPtr = (User_ptr) current_node->data;

        if (strcmp(userPtr->name, str) == 0) {
            return userPtr;
        }

        current_node = current_node->next;
    }

    return NULL;
}