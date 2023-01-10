
#include "youtitooti.h"


app_state_ptr create_app() {
    app_state_ptr statePtr = malloc(sizeof(app_state));
    statePtr->users = create_list();
    statePtr->current_session = malloc(sizeof(Session));
    statePtr->current_session->is_login = false;
    statePtr->current_session->userPtr = NULL;

    return statePtr;
}


void create_session(User_ptr userPtr, Session_ptr sessionPtr) {
    if (sessionPtr == NULL)
        sessionPtr = malloc(sizeof(Session));

    if (sessionPtr->is_login) {
        puts("you are already loged in !!! plz logout for change account !! \n");
        return;
    }

    sessionPtr->userPtr = userPtr;
    sessionPtr->is_login = true;
}

void login(app_state_ptr statePtr, String username, String password) {

    User_ptr userPtr = find_user_from_username(statePtr->users, username);
    if (userPtr != NULL && string_Eq(userPtr->password, password)) {
        create_session(userPtr, statePtr->current_session);

        if (statePtr->current_session == NULL) {
            printf("\nsesion is null\n");
        }

        puts("loged in successfully!!!\n");
        return;
    }

    puts("wrong username or password !! plz try again\n");

}

bool signup(app_state_ptr statePtr, String username, String password) {
    if (statePtr->current_session != NULL && statePtr->current_session->is_login) {
        puts("you are already loged in !!! plz logout for Create account !! \n");
        return false;
    }

    User_ptr userPtr = find_user_from_username(statePtr->users, username);
    if (userPtr != NULL) {
        puts("\nusername exist !!! plz try with another username \n");
        return false;
    }

    userPtr = create_user(username, password);


    insert_DATA(statePtr->users, (DATA) userPtr);

    puts("sign-up successfully\n");
    login(statePtr, username, password);
    return true;
}

bool create_new_post(Session_ptr sessionPtr, String message) {

    if (!sessionPtr->is_login) {
        return false;
    }

    Post_ptr postPtr = new_post(message);
    insert_DATA(sessionPtr->userPtr->posts, (DATA) postPtr);
    puts("creat new post successfully !!! ");

    printf("{\n    \"username\" : \"%s\"\n    \"post-id\" : \"%llu\"\n    \"likes\" : \"%llu\"\n    \"message\" : \"%s\"\n}\n",
           sessionPtr->userPtr->name, sessionPtr->userPtr->posts->size - 1, postPtr->likes, (String) postPtr->message);
    return true;
}


bool like_post(Session_ptr sessionPtr, User_ptr userPtr, uint64_t post_index) {
    if (!sessionPtr->is_login || userPtr == NULL || post_index >= userPtr->posts->size) {
        return false;
    }

    Post_ptr postPtr = get_postfrom_user_with_index(userPtr->posts, post_index);
    if (postPtr == NULL) {
        return false;
    }
    postPtr->likes++;
    return true;
}

bool logout(Session_ptr sessionPtr) {
    if (!sessionPtr->is_login) {
        return false;
    }

    sessionPtr->is_login = false;
    sessionPtr->userPtr = NULL;
    puts("logout successfully");
    return true;
}

bool delete_current_session_post(Session_ptr sessionPtr, uint64_t index) {
    if (!sessionPtr->is_login) {
        return false;
    }

    remove_post(sessionPtr->userPtr->posts, index);
    puts("delete post successfully !!!");
    return true;
}


bool print_user_info(Session_ptr sessionPtr) {

    if (!sessionPtr->is_login) {
        return false;
    }

    User_ptr userPtr = sessionPtr->userPtr;

    if (userPtr == NULL) {
        printf("{}\n");
        return false;
    }

    puts("{\n");
    printf("    \"username\" : \"%s\",\n    \"password\" : \"%s\",\n", userPtr->name, userPtr->password);

    printf("    \"posts\" :     [");
    for (int i = 0; i < userPtr->posts->size; ++i) {
        Post_ptr post = (Post_ptr) (get_data_by_index(userPtr->posts, i)->data);
        printf("\n                    {\n                        \"Id\" : \"%d\",\n                        \"message\" : \"%s\",\n                        \"likes\" : \"%llu\",\n                   },\n",
               i, post->message, post->likes);
    }
    printf("    ],\n}\n");

    return true;
}

void print_find_user_info(app_state state, String username) {


    LinkedList_ptr userLidt = state.users;


    User_ptr userPtr = find_user_from_username(userLidt, username);

    if (userPtr == NULL) {
        printf("{},\n");
        return;
    }

    puts("{\n");
    printf("    \"username\" : \"%s\",\n", userPtr->name);

    printf("    \"posts\" :    [");
    for (int i = 0; i < userPtr->posts->size; ++i) {
        Post_ptr post = get_postfrom_user_with_index(userPtr->posts, i);

        printf("\n                   {\n                       \"username\" : \"%s\",\n                       \"Id\":\"%d\",\n                       \"message\" : \"%s\",\n                       \"likes\" : \"%llu\",\n                   },\n",
               userPtr->name, i, post->message, post->likes);
    }
    printf("   ],\n}\n");
}
