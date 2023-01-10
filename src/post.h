
#ifndef YOUTITOOTI_POST_H
#define YOUTITOOTI_POST_H

#include <stdlib.h>
#include <strings.h>

#include "linkedlist.h"
#include "defs.h"


typedef struct Post {

    String message;
    uint64_t likes;
    uint64_t id;

} Post;
typedef Post *Post_ptr;

Post_ptr new_post(String message);

void delete_post(Post_ptr postPtr);

void remove_post(LinkedList_ptr listPtr,uint64_t index);

bool post_message_Eq(Post_ptr p1, Post_ptr p2);

Post_ptr find_post_inuser_posts(LinkedList_ptr plist, uint64_t id);

bool contain_post(LinkedList_ptr plist, Post_ptr postPtr);

Post_ptr get_postfrom_user_with_index(LinkedList_ptr posts, uint64_t index);

#endif //YOUTITOOTI_POST_H
