#include <stdio.h>
#include <string.h>
#include "TODO.h"
#include "myShell.h"

int main() {
    char action;

    while (1){
        printf("\e[1;1H\e[2J");
        printf("What project do you want to run?\n1. TODO\n2. my cmd\nAnything else to exit\n");
        scanf("%c", &action);
        getchar(); // Remove the \n character from stdin
        printf("\e[1;1H\e[2J");

        switch (action) {
            case '1':
                mainMenu();
                break;

            case '2':
                printf("\e[1;1H\e[2J");
                myCmd();
                printf("\e[1;1H\e[2J");
                break;


            default:
                printf("Goodbye");
                return 0;
        }
    } 

    return 0;
}
