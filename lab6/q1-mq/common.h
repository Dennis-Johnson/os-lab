#ifndef COMMON_H_
#define COMMON_H_

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <stdlib.h>

#define LEN_BUFFER 512
#define MAX_TEXT 512

struct Message_Struct
{
    long int Message_Type;
    char Message_Text[LEN_BUFFER];
};

#endif //COMMON_H_
