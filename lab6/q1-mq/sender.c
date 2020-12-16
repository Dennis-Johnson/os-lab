#include "common.h"

int main()
{
    int running = 1;
    struct Message_Struct Data;
    int msg_id;

    char buffer[LEN_BUFFER];

    msg_id = msgget((key_t)1235, 0666 | IPC_CREAT);
    if (msg_id == -1)
    {
        fprintf(stderr, "mssgget failed with error %d\n", errno);
        exit(EXIT_FAILURE);
    }

    while (running)
    {
        memset(buffer, '\0', sizeof(buffer));
        printf("Enter a number to send to a receiver\n");
        fgets(buffer, LEN_BUFFER, stdin);

        Data.Message_Type = 1;
        strcpy(Data.Message_Text, buffer);

        if (msgsnd(msg_id, &Data, MAX_TEXT, 0) == -1)
        {
            fprintf(stderr, "msgrsnd failed with error %d\n", errno);
            exit(EXIT_FAILURE);
        }

        if (strncmp(buffer, "end", 3) == 0)
            running = 0;
    }

    return 0;
}
