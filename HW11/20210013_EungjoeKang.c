#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<sys/wait.h>
#include <unistd.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

#define MAX_COMMAND_LEN 2000
#define MAX_ARG_NUM 10


int main(void)
{
    int i, pid;
    char *token, command[MAX_COMMAND_LEN], *arguments[MAX_ARG_NUM];

    while(1) {
        fprintf(stdout, "enter command: ");

        // get the command
        char *fgets_rtn = fgets(command, sizeof(command), stdin);

        if (fgets_rtn == NULL) {
            fprintf(stderr, "fgets failed\n");
            exit(EXIT_FAILURE); // exit the shell when fgets fails
        }

        command[strlen(command)-1] = '\0'; // replace '\n' with '\0'


        // delimit command by space
        token = strtok(command, " ");
        if (token == NULL) {
            fprintf(stderr, "recieved no command\n");
            exit(EXIT_FAILURE); // exit the shell when it receives nothing
        }
        else if (strcmp(token, "exit") == 0) {
            fprintf(stdout, "recieved exit\n");
            exit(EXIT_SUCCESS); // exit the shell when it receives exit            
        }
        arguments[0] = token;
        for (i = 1; i < MAX_ARG_NUM; i++) {
            token = strtok(NULL, " ");
            if (token == NULL)
                break;
            arguments[i] = token;
        }
        arguments[i] = NULL;


        // fork child process
        pid = fork();
        if (pid != 0) {
            // parent process
            wait(NULL); // make parent process wait
        } 
        else {
            // child process
            execvp(arguments[0], arguments); // invoke a new program

            fprintf(stderr, "exec failed\n");\
            exit(EXIT_FAILURE); // exit child process when exec fails            
        }
    }
}