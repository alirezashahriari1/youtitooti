#ifndef YOUTITOOTI_DEFS_H
#define YOUTITOOTI_DEFS_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define uint64_t    unsigned long long int

#define String      char*

#define string_len(__str) (strlen(__str) + 1)

#define string_Eq(__str1, __str2) (strcmp(__str1, __str2) == 0)

#endif //YOUTITOOTI_DEFS_H
