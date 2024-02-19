#include <stdio.h>
#include "unistd.h"
#include "stdlib.h"

void creatingProcessImage(){
    // this overlay a process and creates a new process image
    // a process image consists code,data,heap,env var etc

    // needs to specify the file path to be exe
    // the command and any environment variable
    char *args[] = {"ls","-aF","/",0};
    char *env[] = {0};

    printf("About to run /bin/ls\n");
    execve("/bin/ls",args,env);
    perror("execve");
}

void creatingChildProcess(){
    int pid;
    // pid value will be 0 in chid process
    // and the value will be (child pid) in child process
    switch (pid = fork())
    {
    case 0:
        // this calls in the child process
        // conbining execve and fork will create a new process and 
        // overlay a different program
        creatingProcessImage();
        break;
    
    default:
        // this calls in the parent process
        sleep(5);
        printf("i am the parent process : pid = %d,child pid = %d\n",getpid(),pid);
        break;
    case -1:
        perror("fork");
        exit(1);
    }
}


int main() {
    /// getppid() is the parent process of the current process
    //printf("This is my process id : %d\n",getpid());
    //printf("This is my parent process id : %d\n",getppid());

    creatingChildProcess();

    return 0;
}