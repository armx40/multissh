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
    char port[6];
    memset(port, 0, 6);
    int port_str_len = 0;

    printf("%d\n", argc);
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

    char c;
    while ((c = getopt(argc, argv, "p:")) != -1)
    {
        switch (c)
        {
        case 'p':
            port_str_len = strlen(optarg) + 3;
            memcpy(port, optarg, port_str_len);
            break;
        default:
            break;
        }
    }

    char *server;
    int count =0;
    if (port_str_len > 0)
    {
        server = argv[3];
        count = atoi(argv[4]);
    }
    else
    {
        server = argv[1];
        count = atoi(argv[2]);
    }
    int server_str_len = strlen(server);

    char *pass_prompt = (char *)malloc(server_str_len + 13 + 1);
    snprintf(pass_prompt, server_str_len + 14, "%s's password: ", server);
    char *pass_ = getpass(pass_prompt);
    int pass_str_len = strlen(pass_);

    char *port_str;
    if (port_str_len > 0)
    {
        port_str = (char *)malloc(port_str_len + 1); //1+ port_str_len
        snprintf(port_str, port_str_len + 1, "-p %s", port);
    }
    int cmd_str_len = server_str_len + pass_str_len + port_str_len + 37 + 1;
    char *cmd = malloc(cmd_str_len);
    snprintf(cmd, cmd_str_len, "gnome-terminal -e \"sshpass -p %s ssh %s %s\"", pass_, port_str, server);

    //printf(cmd);
    int i = 0;
    for (i; i < count; i++)
    {
        system(cmd);
    }
}