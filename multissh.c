/* 

    USAGE: multissh user@127.0.0.1 [ssh options...] 5
    It will ask for the password and open five gnome-terminal

 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv)
{
    char port[6];
    memset(port, 0, 6);
    int port_str_len = 0;

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

    int i;
    int arg_len = 0;

    for (i = 1; i < argc; i++)
    {
        arg_len += strlen(argv[i]) + 1;
    }

    char *cmd = (char *)malloc(arg_len);
    memset(cmd, 0, arg_len);

    char *server;
    int server_len,got_server_flag=0;

    int count = atoi(argv[argc - 1]);

    int counter = 0;
    for (i = 1; i < argc - 1; i++)
    {
        int argv_len = strlen(argv[i]);
        memcpy(cmd + counter, argv[i], argv_len);
        char *space = " ";
        memcpy(cmd + counter + argv_len, space, 1);

        if (argv[i][0] != '-' && got_server_flag==0)
        {
            server_len = strlen(argv[i]);
            server = (char *)malloc(server_len);
            memcpy(server, cmd + counter, server_len);
            got_server_flag = 1;
        }

        counter = counter + argv_len + 1;
    }

    // generate password prompt

    char *pass_prompt = (char *)malloc(server_len + 13 + 1);
    snprintf(pass_prompt, server_len + 14, "%s's password: ", server);

    char *pass_ = getpass(pass_prompt);
    int pass_str_len = strlen(pass_);

    // generate complete gnome-terminal command

    char *complete_cmd = (char *)malloc(36 + pass_str_len + arg_len);

    snprintf(complete_cmd, 36 + pass_str_len + arg_len, "gnome-terminal -e \"sshpass -p %s ssh %s\"", pass_, cmd);
    
    // execute complete command

    i = 0;
    for (i; i < count; i++)
    {
        system(complete_cmd);
    }
}