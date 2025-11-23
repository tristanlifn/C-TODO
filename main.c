#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// create the taskStruct to hold the task data
struct taskStruct {
    char name[32];
    char description[256];
};

// Initialize the functions
int writeToFile(struct taskStruct task);
struct taskStruct createTask();
int getTasks();
char* padStringRight(char *str, int finalLength);
int getLastId();

// main logic loop
int main(void) {
    // Loop the program
    while (1) {
        // Initialize variables
        int action;
        struct taskStruct task;
        int result;

        // Get what action to preform
        printf("Chose a action: \n1. Create a new task\n2. Get all tasks\n0. Close program\n");
        scanf("%d", &action);
        getchar(); // Remove the \n character from stdin

        switch (action) {
            case 1: // Create a new task
                task = createTask();

                result = writeToFile(task); // Write it to the file

                if (result == 1) {
                    printf("\nSuccessfully written to file\n");
                    break;
                }
                printf("\nError writing to file\n");
                break;
            case 2:
                result = getTasks();

                if (result == -1) {
                    printf("\nError reading from file\n");
                }
                break;
                
            case 0: //Exit the program
                printf("Goodbye!\n");
                return 0;

            default: // If the users chosen action is not supported
                printf("\nNot a valid input, try again\nPress enter to continue\n");
                scanf("%c");
                break;
        }
    }
}

// Write a task to the csv file
int writeToFile(struct taskStruct task) {
    // Open the file in append mode
    FILE *fptr = fopen("C:/Users/trist/CLionProjects/untitled/tasks.csv", "a+");
    if (!fptr) return -1; // Return -1 if the file pointer is null

    const int lastId = getLastId();

    fprintf(fptr, "%d;%s;%s\n", lastId + 1, task.name, task.description); // Write the content of the struct to the file

    fclose(fptr); // Close the file
    return 1;
}

// Gets the info for a new task
struct taskStruct createTask() {
    // Initialize it
    struct taskStruct task;

    printf("Task name: \n");
    fgets(task.name, sizeof(task.name), stdin); // Assigns the input to the name field of the struct
    task.name[strcspn(task.name, "\n")] = '\0'; // Removes the \n, replaces it with a \0

    printf("\nTask description: \n");
    fgets(task.description, sizeof(task.description), stdin);
    task.description[strcspn(task.description, "\n")] = '\0';

    return task; // Return the task struct
}

int getTasks() {
    FILE *fptr = fopen("C:/Users/trist/CLionProjects/untitled/tasks.csv", "r");
    if (!fptr) return -1;

    int pass = 1;
    char line[288];
    char *id;
    char *name;
    char *description;

    printf("\n");
    while (fgets(line, sizeof(line), fptr)) {
        char *token = strtok(line, ";");

        while (token != NULL) {
            if (pass == 1) {
                id = padStringRight(token, 3);
                pass++;
            }
            else if (pass == 2) {
                name = padStringRight(token, 32);
                pass++;
            }
            else if (pass == 3) {
                description = token;
                pass = 1;
            }
            token = strtok(NULL, ";");
        }
        printf("%s | %s | %s", id, name, description);
        free(name);
    }
    printf("\n\n");

    fclose(fptr);
    return 1;
}

char* padStringRight(char *str, const int finalLength) {
    char *paddedString = malloc(32 + 1);
    if (!paddedString) return NULL;

    sprintf(paddedString, "%-*s", finalLength, str);

    return paddedString;
}

int getLastId() {
    FILE *file = fopen("C:/Users/trist/CLionProjects/untitled/tasks.csv", "r");

    char line[256];
    char lastLine[256];

    while (fgets(line, sizeof(line), file)) {
        strcpy(lastLine, line);
    }

    fclose(file);
    if (strtok(lastLine, ";") == "ID") return 0;

    char *token = strtok(lastLine, ";");
    int lastId = atoi(token);

    return lastId;
}