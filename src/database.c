#include "database.h"



void write_to_DB(app_state_ptr appState){

    LinkedList_ptr userList = appState->users;

    User_ptr tUser = NULL;
    Post_ptr tPost = NULL;

    FILE* afp = fopen(ACOUNT_FILE, "w");
    FILE* pfp = fopen(POST_FILE, "w");


    for (uint64_t i = 0; i < userList->size; i++)
    {
        tUser =(User_ptr) get_data_by_index(userList, i)->data;
        fprintf(afp, "%s %s %llu\n",tUser->name, tUser->password, tUser->posts->size);
         for (uint64_t j = 0; j < tUser->posts->size; j++)
        {
            tPost = get_postfrom_user_with_index(tUser->posts, j);
            fprintf(pfp, "%s %s %llu\n",tPost->message, tUser->name, tPost->likes);

        }
    }

    fclose(afp);
    fclose(pfp);

}