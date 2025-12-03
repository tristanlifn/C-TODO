#include <stdio.h>
#include <string.h>
#include "myShell.h"
#include "myStrLib.h"

int ownCmdHandler(char *cmd) {
    int noOfOwnCmds = 6, switchOwnArg = 0;
    char *listOfOwnCmds[noOfOwnCmds];

    listOfOwnCmds[0] = "mystrlen";
    listOfOwnCmds[1] = "mystrscp";
    listOfOwnCmds[3] = "mystrcmp";
    listOfOwnCmds[4] = "mystrcat";
    listOfOwnCmds[5] = "mystrstr";
    listOfOwnCmds[6] = "help";
    listOfOwnCmds[7] = "exit";

    char command[10], arg1[200], arg2[200];
    sscanf(cmd, "%s %s %s", command, arg1, arg2);

    for (int i = 0; i < noOfOwnCmds; i++) {
      if (mystrcmp(command, listOfOwnCmds[i]) == 0) {
        switchOwnArg = i;
        break;
      }
    }

    switch (switchOwnArg) {
        case 1:
            printf("%d\n", mystrlen(arg1));
            break;

        case 2:
            char *buffer1 = arg1;
            char *buffer2 = "";
            printf("Buffer 1: %s\nBuffer 2: %s\n", buffer1, buffer2);
            printf("Buffer 2 after copy: %s\n", mystrcpy(arg1, arg2));
            break;

        case 3:
            printf("%d\n", mystrcmp(arg1, arg2));
            break;

        case 4:
            printf("%s\n", mystrcat(arg1, arg2));
            break;

        case 5:
            printf("%s\n", mystrstr(arg1, arg2));
            break;

        case 6:
            printf("Availanble commands:\nmystrlen {string 1}\nmystrcpy {string to copy}\nmystrcmp {string 1} {string 2}\nEXIT");
            break;

        case 7:
            return -1;

        default:
            printf("command %s not found, run 'help' to see a list of availanble commands\n", command);
    }
    return 0;
}

void myCmd() {
    while (1) {
        printf("my cmd> ");
        char *input;
        fgets(input, 500, stdin);

        int output = ownCmdHandler(input);
        
        if (output == -1) {
            return;
        }
    }
}
