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
    listOfOwnCmds[4] = "exit";

    char command[10], arg1[200], arg2[200];
    sscanf(cmd, "%s %s %s", command, arg1, arg2);

    for (int i = 0; i < noOfOwnCmds; i++) {
      if (mystrcmp(command, listOfOwnCmds[i]) == 0) {
        switchOwnArg = 1 + i;
        break;
      }
    }

    switch (switchOwnArg) {
        case 1:
            printf("%d\n", mystrlen(arg1));
            break;

        case 2:
            printf("%s\n", mystrcpy(arg1, arg2));
            break;

        case 3:
            printf("%d\n", mystrcmp(arg1, arg2));
            break;

        case 4:
            return -1;
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
