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
int deleteTask();
int editTask();

// main logic loop
int mainMenu() {
    FILE *fileExists = fopen("tasks.csv", "r");
    if (fileExists != NULL) {
        FILE *fptr = fopen("tasks.csv", "w");
        fprintf(fptr, "Name;Description\n");
        fclose(fptr);
    }

    // Loop the program
    while (1) {
        // Initialize variables
        char action;
        struct taskStruct task;
        int result;

        // Get what action to preform
        printf("Chose a action: \n1. Create a new task\n2. Get all tasks\n3. Delete task\n4. Edit a task\nAnything else to close\n");
        scanf("%s", &action);
        getchar(); // Remove the \n character from stdin

        switch (action) {
            case '1': // Create a new task
                printf("\e[1;1H\e[2J");
                task = createTask();

                result = writeToFile(task); // Write it to the file

                if (result == 1) {
                    printf("\nSuccessfully written to file\n");
                }
                else if (result == -1) {
                    printf("\nError writing to file\n");
                }

                printf("\nPress enter to continue\n");
                scanf("%c");
                printf("\e[1;1H\e[2J");
                break;

            case '2':
                printf("\e[1;1H\e[2J");
                result = getTasks();

                if (result == -1) {
                    printf("\nError reading from file\n");
                }
                printf("Press enter to continue\n");
                scanf("%c");
                printf("\e[1;1H\e[2J");
                break;

            case '3':
                printf("\e[1;1H\e[2J");

                getTasks();

                result = deleteTask();
                if (result == -1) {
                    printf("Error opening file");
                } else if (result == -2) {
                    printf("\nCannot delete line 0\n");
                }
                getchar();
                printf("Press enter to continue\n");
                scanf("%c");
                printf("\e[1;1H\e[2J");
                break;
 
            case '4':
                printf("\e[1;1H\e[2J");

                getTasks();

                result = editTask();
                if (result == -1) {
                    printf("Error opening tasks file");
                } else if (result == -2) {
                    printf("Cannot delete line 0\n");
                }
                printf("Press any key to continue\n");
                scanf("%c");
                printf("\e[1;1H\e[2J");
                break;

            default: // If the users chosen action is not supported
                printf("Goodbye!\n");
                return 0;
        }
    }
}

// Write a task to the csv file
int writeToFile(struct taskStruct task) {
    // Open the file in append mode
    FILE *fptr = fopen("tasks.csv", "a+");
    if (!fptr) return -1; // Return -1 if the file pointer is null

    fprintf(fptr, "%s;%s\n", task.name, task.description); // Write the content of the struct to the file

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
    FILE *fptr = fopen("tasks.csv", "r");
    if (!fptr) return -1;

    int pass = 1;
    int lineNumber = 0;
    char line[512];
    char *name;
    char *description;

    printf("\n");
    while (fgets(line, sizeof(line), fptr)) {
        char *token = strtok(line, ";");

        while (token != NULL) {
            if (pass == 1) {
                name = padStringRight(token, 32);
                pass++;
            }
            else if (pass == 2) {
                description = token;
                pass = 1;
            }
            token = strtok(NULL, ";");
        }
        char temp[3];
        //itoa(lineNumber, temp, 10);
        sprintf(temp, "%d", lineNumber);
        printf("%s | %s | %s", padStringRight(temp, 3), name, description);
        free(name);
        lineNumber++;
    }
    printf("\n");

    fclose(fptr);
    return 1;
}

char* padStringRight(char *str, const int finalLength) {
    char *paddedString = malloc(finalLength);
    if (!paddedString) return NULL;

    sprintf(paddedString, "%-*s", finalLength -1, str);

    return paddedString;
}

int deleteTask() {
    FILE *fptr = fopen("tasks.csv", "r");
    FILE *fptr2 = fopen("temp.csv", "w");
    if (!fptr) return -1;

    printf("What task do you want to delete?\n");
    int deleteLine = 1;
    int temp = 0;
    char c;
    scanf("%d", &deleteLine);
    if (deleteLine == 0) return -2;

    c = getc(fptr);
    while (c != EOF) {
        if (c =='\n') temp++;

        if (temp != deleteLine && c != EOF) {
            putc(c, fptr2);
        }
        c = getc(fptr);
    }

    fclose(fptr2);
    fclose(fptr);

    remove("tasks.csv");
    rename("temp.csv", "tasks.csv");
    remove ("temp.csv");

    return 1;
}

 int editTask() {
    FILE *fptr = fopen("tasks.csv", "r");
    FILE *fptr2 = fopen("temp.csv", "w");
    if (!fptr) return -1;

    printf("What task do you want to edit?\n");
    int editLine = 1;
    int temp = 0;
    char c;
    scanf("%d", &editLine);
    getchar(); // Get the '\n'
    if (editLine == 0) return -2;
 
    struct taskStruct task = createTask();

    c = getc(fptr);
    while (c != EOF) {

        if (temp != editLine && c != EOF) {
            putc(c, fptr2);
        } else if (temp == editLine && c != EOF) {
            fprintf(fptr2, "%s;%s", task.name, task.description);
            fscanf(fptr, "%*[^\n]");
            temp++;
        }

        if (c == '\n') temp++;
        c = getc(fptr);
    }

    fclose(fptr);
    fclose(fptr2);

    remove("tasks.csv");
    rename("temp.csv", "tasks.csv");
    remove("temp.csv");

    return 1;
}
