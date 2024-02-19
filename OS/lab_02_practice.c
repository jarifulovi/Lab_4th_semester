#include <stdio.h>
#include "unistd.h"
#include "stdlib.h"

int main() {
    printf("This is my process id : %d\n",getpid());
    printf("This is my parent process id : %d\n",getppid());
    return 0;
}