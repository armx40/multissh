/* 

    USAGE: multissh user@127.0.0.1 5
    *asks for the password and opens five gnome-terminal

 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        write(STDOUT_FILENO, "Specify server! exiting...\n", 27);
        exit(EXIT_FAILURE);
    }
    if (argc == 2)
    {
        write(STDOUT_FILENO, "Specify number of terminals! exiting...\n", 40);
        exit(EXIT_FAILURE);
    }
    char *server = argv[1];
    int count = atoi(argv[2]);
    int server_str_len = strlen(server);

    char *pass_prompt = (char *)malloc(server_str_len + 13 + 1);
    snprintf(pass_prompt, server_str_len + 14, "%s's password: ", server);
    char *pass_ = getpass(pass_prompt);
    int pass_str_len = strlen(pass_);

    int cmd_str_len = server_str_len + pass_str_len + 36 + 1;
    char *cmd = malloc(cmd_str_len);
    snprintf(cmd, cmd_str_len, "gnome-terminal -e \"sshpass -p %s ssh %s\"", pass_, server);

    int i = 0;
    for (i; i < count; i++)
    {
        system(cmd);
    }
}