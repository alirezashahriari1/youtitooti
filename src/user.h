
#ifndef YOUTITOOTI_USER_H
#define YOUTITOOTI_USER_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "post.h"
#include "defs.h"



typedef struct User {
    String name;
    String password;
    LinkedList_ptr posts;
} User;

typedef User* User_ptr;

User_ptr create_user(String name, String password);

void delete_user(User_ptr userPtr);

bool user_Eq(User_ptr , User_ptr);

User_ptr find_user_from_username(LinkedList_ptr users, String str);

#endif //YOUTITOOTI_USER_H
