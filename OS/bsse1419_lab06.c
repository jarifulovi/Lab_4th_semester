#include <stdio.h>
#define INT_MAX 9999999

float avg(int arr[],int n){
    float average = 0;
    for(int i=0;i<n;i++) average += arr[i];
    return average/n;
}
void displayGrantChart(char p[][4], int arr[], int n) {
    printf("|");

    // Display process names with formatting
    for (int i = 0; i < n; i++) {
        printf("---%s---|", p[i]);
    }

    // Display time values
    printf("\n%d", 0);
    for (int i = 0; i < n; i++) {
        printf("\t %d", arr[i]);
    }
    printf("\n");
}

void display(char process[][4],int ct[],int turn_t[],int wt[], int n){
    // display the grant chart
    printf("The grant chart : \n");
    displayGrantChart(process,ct,n);

    printf("\nprocess\ttat\twaiting time\n");
    for(int i=0;i<n;i++){
        printf("%s\t%d\t%d\n",process[i],turn_t[i],wt[i]);
    }
    // display average turn around time and waiting time
    float avg_wt = avg(wt,n);
    float avg_turn_t = avg(turn_t,n);

    printf("Average turn around time : %0.2f\n",avg_turn_t);
    printf("Average waiting time : %0.2f\n",avg_wt);
}


void preemptive_sjf(char process[][4], int at[], int bt[], int n) {
    int ct[n], wt[n], turn_t[n];
    int remaining_time[n];

    // Initialize remaining_time array with burst times
    for (int i = 0; i < n; i++) {
        remaining_time[i] = bt[i];
    }

    int completed = 0;
    int time = 0;

    while (completed < n) {
        int shortest_job_index = -1;
        int shortest_time = INT_MAX;

        // The process with shortest remaining time and has arrived
        for (int i = 0; i < n; i++) {
            if (at[i] <= time && remaining_time[i] < shortest_time && remaining_time[i] > 0) {
                shortest_time = remaining_time[i];
                shortest_job_index = i;
            }
        }
        // No process has arrived
        if (shortest_job_index == -1) {
            time++;
        } 
        // Process arrived
        else {
            remaining_time[shortest_job_index]--;

            if (remaining_time[shortest_job_index] == 0) {
                // Process has completed
                completed++;
                ct[shortest_job_index] = time + 1;
                turn_t[shortest_job_index] = ct[shortest_job_index] - at[shortest_job_index];
                wt[shortest_job_index] = turn_t[shortest_job_index] - bt[shortest_job_index];
            }

            time++;
        }
    }

    display(process, ct, turn_t, wt, n);
}

void priority_scheduling(char process[][4], int at[], int bt[],int pr[], int n){
    int ct[n], wt[n], turn_t[n];
    int remaining_time[n];

    int completed = 0;
    int time = 0;

    // Initialize remaining_time array with burst times
    for (int i = 0; i < n; i++) {
        remaining_time[i] = bt[i];
    }

    while(completed < n){
        int shortest_priority_index = -1;
        int shortest_priority = INT_MAX;

        // The process with shortest priority which has arrived
        for (int i = 0; i < n; i++){

            if(at[i]<=time && pr[i] < shortest_priority && remaining_time[i]>0){
                shortest_priority = pr[i];
                shortest_priority_index = i;
            }
        }
        // No arrived process
        if(shortest_priority_index == -1){
            time++;
        }
        // Process arrived
        else {
            remaining_time[shortest_priority_index]--;
           
            if(remaining_time[shortest_priority_index] == 0){
                // Executing the process
                completed++;
                ct[shortest_priority_index] = time + 1;
                turn_t[shortest_priority_index] = ct[shortest_priority_index] - at[shortest_priority_index];
                wt[shortest_priority_index] = turn_t[shortest_priority_index] - bt[shortest_priority_index];
            }
            time++;
        }
    }
    display(process,ct,turn_t,wt,n);
}



int main() {
    
    int n;
    printf("Select number of processes: ");
    scanf("%d", &n);

    int burst_time[n], arrival_time[n], priority[n];
    char process[n][4];

    printf("Enter processes (like p1, p2, etc): ");
    for (int i = 0; i < n; i++) {
        scanf("%3s", process[i]);
    }

    printf("Enter arrival time: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arrival_time[i]);
    }

    printf("Enter burst time: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &burst_time[i]);
    }

    printf("Enter priority: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &priority[i]);
    }

    int choice;
    
    do {
        printf("\nSelect scheduling algorithm (preemptive):\n");
        printf("1. SJF\n");
        printf("2. Priority scheduling\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                preemptive_sjf(process,arrival_time,burst_time,n);
                break;
            case 2:
                priority_scheduling(process,arrival_time,burst_time,priority,n);
                break;
            case 0:
                printf("Thank you...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);



    return 0;
}