
#include <stdio.h>
#include <stdlib.h>
#include "youtitooti.h"
#include <string.h>
#include <ctype.h>
#include "defs.h"
#include "database.h"

#define is_signup_cmd(_str) (strcmp(_str, "signup") == 0)
#define is_login_cmd(_str) (strcmp(_str, "login") == 0)
#define is_post_cmd(_str) (strcmp(_str, "post") == 0)
#define is_like_cmd(_str) (strcmp(_str, "like") == 0)
#define is_logout_cmd(_str) (strcmp(_str, "logout") == 0)
#define is_delete_cmd(_str) (strcmp(_str, "delete") == 0)
#define is_info_cmd(_str) (strcmp(_str, "info") == 0)
#define is_finduser_cmd(_str) (strcmp(_str, "finduser") == 0)

void invalid_argument_err(String command) {
    printf("\ninvalid argument or argument number for command {%s}\n", command);

}

void not_login_error() {
    puts("\nyou are not online  --- login first ---\n");
}

void wrong_value_error() {
    puts("\n wrong value inserted!!! \n");
}

void no_user_found_eer(){
    puts("\n user not found!!! \n");

}

void post_not_found_eer(){
    puts("\n post not found or wrong post_id !!! \n");
}

void execute_command(LinkedList_ptr tokenList, app_state_ptr appStatePtr) {
    String command = (String) tokenList->start->data;

    if (is_signup_cmd(command)) {
        if (tokenList->size != 3) {
            invalid_argument_err(command);
            return;
        }

        String username = (String) get_data_by_index(tokenList, 1)->data;
        String password = (String) get_data_by_index(tokenList, 2)->data;
        signup(appStatePtr, username, password);

    } else if (is_login_cmd(command)) {
        if (tokenList->size != 3) {
            invalid_argument_err(command);
            return;
        }

        String username = (String) get_data_by_index(tokenList, 1)->data;
        String password = (String) get_data_by_index(tokenList, 2)->data;
        login(appStatePtr, username, password);

    } else if (is_post_cmd(command)) {
        if (tokenList->size < 2) {
            invalid_argument_err(command);
            return;
        }

        String message = malloc(sizeof(char));
        *message = '\0';

        for (int i = 1; i < tokenList->size; ++i) {
            String temp = (String) get_data_by_index(tokenList, i)->data;
            message = realloc(message, sizeof(char) * (strlen(message) + strlen(temp) + 2));
            if (i > 1)
                strcat(message, " ");
            strcat(message, temp);
        }


        bool result = create_new_post(appStatePtr->current_session, message);

        if (!result) {
            not_login_error();
        }


    } else if (is_like_cmd(command)) {
        if (tokenList->size != 3) {
            invalid_argument_err(command);
            return;
        }

        String username = (String) get_data_by_index(tokenList, 1)->data;
        char *endPtr;
        uint64_t post_id = strtoll((String) get_data_by_index(tokenList, 2)->data, &endPtr, 10);

        if (endPtr == NULL) {
            wrong_value_error();
            return;
        }

        User_ptr userPtr = find_user_from_username(appStatePtr->users, username);
        if(userPtr == NULL){
            no_user_found_eer();
            return;
        }
        if (post_id >= userPtr->posts->size){
            post_not_found_eer();
            return;
        }



        bool result = like_post(appStatePtr->current_session, userPtr, post_id);

        if (!result) {
            not_login_error();
            return;
        }

    } else if (is_logout_cmd(command)) {
        if (tokenList->size != 1) {
            invalid_argument_err(command);
            return;
        }

        bool result = logout(appStatePtr->current_session);

        if (!result) {
            not_login_error();
            return;
        }

    } else if (is_delete_cmd(command)) {
        if (tokenList->size != 2) {
            invalid_argument_err(command);
            return;
        }
        char *endPtr;


        uint64_t post_id = strtoll((String) get_data_by_index(tokenList, 1), &endPtr, 10);

        if (endPtr == NULL) {
            wrong_value_error();
            return;
        }

        bool result = delete_current_session_post(appStatePtr->current_session, post_id);

        if (!result) {
            not_login_error();
            return;
        }

    } else if (is_info_cmd(command)) {
        if (tokenList->size != 1) {
            invalid_argument_err(command);
            return;
        }

        bool result = print_user_info(appStatePtr->current_session);

        if (!result) {
            not_login_error();
            return;
        }


    } else if (is_finduser_cmd(command)) {
        if (tokenList->size != 2) {
            invalid_argument_err(command);
            return;
        }

        String username = (String) get_data_by_index(tokenList, 1)->data;
        print_find_user_info(*appStatePtr, username);

    } else {
        printf("invalid command --  {%s}!!!! \n", command);
        return;
    }


}

String str_tolow(String str) {

    for (int i = 0; i < strlen(str); ++i) {
        str[i] = (char) tolower(str[i]);
    }
    return str;
}

String get_input() {


    char buffer[(BUFSIZ)] = {'\0'};
    String input = malloc(sizeof(char) * (1));
    *input = '\0';

    while (fgets(buffer, BUFSIZ, stdin) != NULL) {

        input = realloc(input, (string_len(input) + BUFSIZ + 1));
        strcat(input, buffer);

        if (strlen(buffer) < BUFSIZ) {
            break;
        }

    }

    return input;

}


int main() {

    app_state_ptr youtitootiState = create_app();
    Session_ptr currsentSession = youtitootiState->current_session;

    String input;

    LinkedList_ptr token_list = create_list();
    String token;


    while (true) {

        if (currsentSession->is_login){
            printf("%s@YoutiTooti",currsentSession->userPtr->name);
        } else{
            printf("@YoutiTooti");
        }
        printf(">>> ");
        input = get_input();

        token = strtok(input, " \n");

        while (token != NULL) {

            insert_DATA(token_list, (DATA) token);
            token = strtok(NULL, " \n");

        }


        if (!is_empty_list(token_list)) {
            str_tolow((String) token_list->start->data);
        } else continue;

        if (strcmp((String) token_list->start->data, "exit") == 0) {
            puts("Exit YoutiTooti ....");
            break;
        }

        execute_command(token_list, youtitootiState);

        clear(token_list);

        if (input != NULL) {
            free(input);
            input = NULL;
        }


        write_to_DB(youtitootiState);
    }


    write_to_DB(youtitootiState);

    //free all alocated memory befor exit !!!!

    for (uint64_t i = youtitootiState->users->size; i > 0; --i) {

        User_ptr userPtr = (User_ptr) youtitootiState->users->start->data;


        for (uint64_t j = userPtr->posts->size; j > 0; --j) {
            Post_ptr postPtr = (Post_ptr) userPtr->posts->start->data;
            delete_node(userPtr->posts, 0);
            free(postPtr->message);
            free(postPtr);

        }

        free(userPtr->name);
        free(userPtr->password);
        delete_node(youtitootiState->users, 0);
        free(userPtr);
    }
    clear(youtitootiState->users);

    if (input != NULL) {
        free(input);
        input = NULL;
    }

    free(youtitootiState->current_session);
    free(youtitootiState);
    return 0;
}