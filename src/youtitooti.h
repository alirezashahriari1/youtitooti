//
// Created by hosein nahari on 12/30/22.
//

#ifndef YOUTITOOTI_YOUTITOOTI_H
#define YOUTITOOTI_YOUTITOOTI_H


#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"
#include "user.h"
#include "post.h"
#include "defs.h"

typedef struct Session {
    User_ptr userPtr;
    bool is_login;
} Session;
typedef Session *Session_ptr;

typedef struct app_state {
    Session_ptr current_session;
    LinkedList_ptr users;
} app_state;

typedef app_state *app_state_ptr;


app_state_ptr create_app();

void login(app_state_ptr statePtr, String username, String password);

bool signup(app_state_ptr statePtr, String username, String password);

void create_session(User_ptr userPtr, Session_ptr sessionPtr);

bool create_new_post(Session_ptr sessionPtr, String message);

bool like_post(Session_ptr sessionPtr,User_ptr userPtr, uint64_t post_index);

bool logout(Session_ptr sessionPtr);

bool delete_current_session_post(Session_ptr sessionPtr, uint64_t index);

bool print_user_info(Session_ptr sessionPtr);

void print_find_user_info(app_state state, String username);

#endif //YOUTITOOTI_YOUTITOOTI_H
