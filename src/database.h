#ifndef YOUTITOOTI_DATABASE_H
#define YOUTITOOTI_DATABASE_H

#include "linkedlist.h"
#include "post.h"
#include "user.h"
#include "youtitooti.h"

#define ACOUNT_FILE "accounts.txt"
#define POST_FILE   "posts.txt"

void write_to_DB(app_state_ptr appState);


#endif /* YOUTITOOTI_DATABASE_H */
