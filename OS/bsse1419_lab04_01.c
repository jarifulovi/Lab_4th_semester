#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int n;
    printf("Enter the value of n: ");
    scanf("%d", &n);

    int pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } 
    else if (pid == 0) {
        // Child process
        int oddSum = 0;
        for (int i = 1; i <= n; i += 2) {
            oddSum += i;
        }
        printf("Child Process (Odd Sum): %d\n", oddSum);
    } 
    else {
        // Parent process
        int evenSum = 0;
        for (int i = 2; i <= n; i += 2) {
            evenSum += i;
        }
        printf("Parent Process (Even Sum): %d\n", evenSum);
    }

    return 0;
}
