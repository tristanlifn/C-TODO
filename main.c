#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct taskStruct {
    char name[32];
    char description[256];
};

int writeToFile(struct taskStruct task);
struct taskStruct getTaskInfo();

int main(void) {
    while (1) {
        printf("Chose a action: \n1. Create a new task\n0. Close program\n");
        int action;
        scanf("%d", &action);
        getchar();

        if (action == 1) {
            struct taskStruct task = getTaskInfo();

            int result = writeToFile(task);

            if (result == 1) {
                printf("\nSuccessfully written to file\n");
            }
            else if (result == -1) {
                printf("\nError writing to file\n");
            }
        }
        else if (action == 0) {
            printf("Goodbye!\n");
            return 0;
        }
        else {
            printf("\nNot a valid input, try again\n");
        }
    }
}

int writeToFile(struct taskStruct task) {
    FILE *fptr = fopen("C:/Users/trist/CLionProjects/untitled/tasks.csv", "a+");
    if (!fptr) return -1;

    fprintf(fptr, "%s,%s\n", task.name, task.description);

    fclose(fptr);
    return 1;
}

struct taskStruct getTaskInfo() {
    struct taskStruct task;

    printf("Task name: \n");
    fgets(task.name, sizeof(task.name), stdin);
    task.name[strcspn(task.name, "\n")] = '\0';

    printf("Task description: \n");
    fgets(task.description, sizeof(task.description), stdin);
    task.description[strcspn(task.description, "\n")] = '\0';

    return task;
}