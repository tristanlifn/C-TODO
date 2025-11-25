#include <stdio.h>
#include "TODO.h"

int main() {
    char action;

    while (1){
        printf("\e[1;1H\e[2J");
        printf("What project do you want to run?\n1. TODO\nAnything else to exit\n");
        scanf("%c", &action);
        getchar(); // Remove the \n character from stdin
        printf("\e[1;1H\e[2J");

        switch (action) {
            case '1':
                mainMenu();
                break;


            default:
                printf("Goodbye");
                return 0;
        }
    } 

    return 0;
}
