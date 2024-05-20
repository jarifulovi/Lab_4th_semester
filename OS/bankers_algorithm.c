#include "stdio.h"

void bankers_algo(int num_pro,int num_res,int alloc[num_pro][num_res],int max[num_pro][num_res],int max_res[num_res]){

    int need[num_pro][num_res];
    int avail[num_res];
    

    printf("This is bankers algorithm : \n\n");
    for(int j=0;j<num_res;j++){
        int total_alloc = 0;
        for(int i=0;i<num_pro;i++) total_alloc += alloc[i][j];
        avail[j] = max_res[j] - total_alloc; 
        if(avail[j]<0) {
            printf("Maximum resource cannot be less than total allocated resource\n");
        }
    }

    int index = 0;
    int pro_flag[num_pro];
    int process_schedule[num_pro];
    // Initialize finished process
    for(int i=0;i<num_pro;i++){
        process_schedule[i] = -1;
        pro_flag[i] = 0;
    }
    // Initialze resource need
    for(int i=0;i<num_pro;i++){
        for(int j=0;j<num_res;j++){
            need[i][j] = max[i][j] - alloc[i][j];
            if(need[i][j]<0){
                printf("Resource allocation cannot be greater than max need\n");
            }
        }
    }
    while(index < num_pro){
        // Check all process and their need
        int flag = 1;
        // If one process found then break the loop
        for(int i=0;i<num_pro;i++){
            flag = 1;
            if(pro_flag[i]==0){
                for(int j=0;j<num_res;j++){
                    if(need[i][j]>avail[j]){
                        flag = 0;
                        break;
                    }
                }
                // Found a process
                if(flag==1){
                    // Release process allocated resouces
                    for(int j=0;j<num_res;j++){
                        avail[j] += alloc[i][j];
                    }
                    process_schedule[index++] = i;
                    pro_flag[i] = 1;
                    break;
                }
            }
        }
        if(flag==0) {
            break;
        }

    }
    // Check if all process finished
    if(index >= num_pro){
        printf("Deadlock will never happen\n");
        printf("The process scheduling : ");
        for(int i=0;i<num_pro;i++) printf("%d ",process_schedule[i]);
        
    }
    else {
        printf("Deadlock will happen\n");
    }
}

int main() {
    FILE *file = fopen("ban_algo_input.txt", "r"); // Open the file for reading
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    int num_res, num_pro;
    fscanf(file, "%d", &num_res); // Read number of resources
    fscanf(file, "%d", &num_pro); // Read number of processes

    int alloc[num_pro][num_res];
    int max[num_pro][num_res];
    int max_res[num_res];

    // Read allocation for each process
    for (int i = 0; i < num_pro; i++) {
        for (int j = 0; j < num_res; j++) {
            fscanf(file, "%d", &alloc[i][j]);
        }
    }

    // Read maximum resources for each process
    for (int i = 0; i < num_pro; i++) {
        for (int j = 0; j < num_res; j++) {
            fscanf(file, "%d", &max[i][j]);
        }
    }

    // Read maximum resources
    for (int i = 0; i < num_res; i++) {
        fscanf(file, "%d", &max_res[i]);
    }

    fclose(file); // Close the file

    bankers_algo(num_pro, num_res, alloc, max, max_res);

    return 0;
}