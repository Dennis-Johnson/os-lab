#include "common.h"

void checkPalindrome(char *s, int n)
{
    for (int i = 0; i < n / 2; i++)
    {
        if (s[i] != s[n - i - 1])
        {
            printf("Not Palindrome\n");
            return;
        }
    }
    printf("Palindrome\n");
}

int main()
{
    int running = 1;
    int msg_id;

    struct Message_Struct Data;
    long int msg_to_recv = 0;

    msg_id = msgget((key_t)1235, 0666 | IPC_CREAT);
    if (msg_id == -1)
    {
        fprintf(stderr, "mssgget failed with error %d\n", errno);
        exit(EXIT_FAILURE);
    }

    while (running)
    {
        if (msgrcv(msg_id, &Data, LEN_BUFFER, msg_to_recv, 0) == -1)
        {
            perror(" ");
            fprintf(stderr, "msgrcv failed with error %d\n", errno);
            exit(EXIT_FAILURE);
        }

        printf("Received %s\n", Data.Message_Text);

        if (strncmp(Data.Message_Text, "end", 3) == 0)
            running = 0;

        checkPalindrome(Data.Message_Text, strlen(Data.Message_Text) - 1);
    }

    if (msgctl(msg_id, IPC_RMID, 0) == -1)
    {
        fprintf(stderr, "msgctl(IPC_RMID) failed\n");
        exit(EXIT_FAILURE);
    }
}
