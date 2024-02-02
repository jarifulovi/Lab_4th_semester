#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Define a structure to store process information
struct ProcessInfo {
    pid_t processPID;
    char message[50];
    struct ProcessInfo *next;  // Pointer to the next process in the linked list
};

// Function to print the linked list
void printLinkedList(struct ProcessInfo *head) {
    struct ProcessInfo *current = head;

    while (current != NULL) {
        printf("PID: %d, Message: %s\n", current->processPID, current->message);
        current = current->next;
    }
}

int main() {
    struct ProcessInfo *head = NULL;

    // Create the first process node
    struct ProcessInfo *currentProcess = malloc(sizeof(struct ProcessInfo));
    if (currentProcess == NULL) {
        perror("Out of memory");
        exit(1);
    }

    currentProcess->processPID = getpid();
    snprintf(currentProcess->message, sizeof(currentProcess->message), "Hello from the initial process!");
    currentProcess->next = NULL;

    head = currentProcess; // Set the head of the linked list

    // Create child processes
    for (int i = 0; i < 3; ++i) {
        pid_t childPID = fork();

        if (childPID == -1) {
            perror("fork");
            free(currentProcess);
            exit(1);
        }

        if (childPID == 0) {
            // Child process
            currentProcess = malloc(sizeof(struct ProcessInfo));
            if (currentProcess == NULL) {
                perror("malloc");
                exit(1);
            }

            currentProcess->processPID = getpid();
            snprintf(currentProcess->message, sizeof(currentProcess->message), "Hello from child %d!", i + 1);
            currentProcess->next = NULL;

            // Link the child process to the parent's linked list
            currentProcess->next = head;

            // Update the head to the current child process
            head = currentProcess;

            // Print the linked list in the child process
            printf("Child Process %d:\n", i + 1);
            printLinkedList(head);

            exit(0);
        } else {
            // Parent process
            // Wait for the child to finish
            wait(NULL);
        }
    }

    // Print the final linked list in the parent process
    printf("Parent Process:\n");
    printLinkedList(head);

    // Free allocated memory
    while (head != NULL) {
        struct ProcessInfo *temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}

