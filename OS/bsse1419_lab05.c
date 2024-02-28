#include <stdio.h>

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

void fcfs(char process[][4],int at[],int bt[], int n) {
    int ct[n],wt[n],turn_t[n];
    // asume that process arrival time are in order 
    int endtime = at[0];
    for(int i=0;i<n;i++){
        ct[i] = (endtime+=bt[i]);
        turn_t[i] = ct[i] - at[i];
        wt[i] = (turn_t[i] - bt[i] < 0) ? 0 : (turn_t[i] - bt[i]);
    }
    display(process,ct,turn_t,wt,n);
}


void sjf(char process[][4], int at[], int bt[], int n) {
    int ct[n], wt[n], turn_t[n];

    // Initialize sort_index with initial order
    int sort_index[n];
    for (int i = 0; i < n; i++) {
        sort_index[i] = i;
    }

    // Sort indexes based on burst times
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (bt[sort_index[i]] > bt[sort_index[j]]) {
                // Swap indexes
                int temp = sort_index[i];
                sort_index[i] = sort_index[j];
                sort_index[j] = temp;
            }
        }
    }
    
    // Take the first element
    int endtime = at[0];
    ct[0] = (endtime += bt[0]);
    turn_t[0] = ct[0] - at[0];
    wt[0] = (turn_t[0] - bt[0] < 0) ? 0 : (turn_t[0] - bt[0]);

    // Process the rest of the elements
    for (int i = 0; i < n; i++) {
        int index = sort_index[i];
        if (index != 0) {
            ct[index] = (endtime += bt[index]);
            turn_t[index] = ct[index] - at[index];
            wt[index] = (turn_t[index] - bt[index] < 0) ? 0 : (turn_t[index] - bt[index]);
        }
    }
    display(process,ct,turn_t,wt,n);
}
void priority_scheduling(char process[][4], int at[], int bt[],int pr[], int n){
    int ct[n], wt[n], turn_t[n];

    // Initialize sort_index with initial order
    int sort_index[n];
    for (int i = 0; i < n; i++) {
        sort_index[i] = i;
    }
    // Sort indexes based on priority ( high p.num is high priority )
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (pr[sort_index[i]] < pr[sort_index[j]]) {
                // Swap indexes
                int temp = sort_index[i];
                sort_index[i] = sort_index[j];
                sort_index[j] = temp;
            }
        }
    }
   
    // Take the first element
    int endtime = at[0];
    ct[0] = (endtime += bt[0]);
    turn_t[0] = ct[0] - at[0];
    wt[0] = (turn_t[0] - bt[0] < 0) ? 0 : (turn_t[0] - bt[0]);
    // Process the rest of the elements
    for (int i = 0; i < n; i++) {
        int index = sort_index[i];
        if(index !=0){
            ct[index] = (endtime += bt[index]);
            turn_t[index] = ct[index] - at[index];
            wt[index] = (turn_t[index] - bt[index] < 0) ? 0 : (turn_t[index] - bt[index]);
        }
    }
    display(process,ct,turn_t,wt,n);
}
void round_robin(char process[][4], int at[], int bt[], int n) {
    int ct[n], wt[n], turn_t[n];
    for(int i=0;i<n;i++){
        ct[i] = 0;
        wt[i] = 0;
        turn_t[i] = 0;
    }
    int qt, inRound = 1;
    printf("Enter the quantum number: ");
    scanf("%d", &qt);

    int finished_process[n];
    for (int i = 0; i < n; i++) finished_process[i] = 0;
    int endtime = at[0];

    while (inRound) {
        for (int i = 0; i < n; i++) {
            if (!finished_process[i] && bt[i] > 0) {
                if (qt < bt[i]) {
                    // need another round
                    for (int j = 0; j < n; j++){
                        if (finished_process[j] == 0 && endtime >= at[j]){
                            ct[j] += qt;
                            if(i!=j) wt[j] += qt;
                        }
                    }
        
                    int pre_endtime = endtime;
                    endtime += qt;
                    // some process arrived between qt
                    for(int j=0;j<n;j++){
                        if(endtime > at[j] && pre_endtime < at[j] && i!=j ) {
                            ct[j] += qt;
                            wt[j] += (endtime-at[j]);
                        }
                    }
                    bt[i] -= qt;
                } else {
                    // round completed
                    for (int j = 0; j < n; j++){
                        if (finished_process[j] == 0 && endtime >= at[j]){
                            ct[j] += bt[i];
                            if(i!=j)
                                wt[j] += bt[i];
                        }
                    }
                    endtime += bt[i];
                    finished_process[i] = 1;
                    turn_t[i] = ct[i] - at[i];
                }
            }
        }

        // check all processes are finished or not
        inRound = 0;
        for (int i = 0; i < n; i++)
            if (!finished_process[i])
                inRound = 1;
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
        printf("\nSelect scheduling algorithm:\n");
        printf("1. FCFS\n");
        printf("2. SJF\n");
        printf("3. Priority Scheduling\n");
        printf("4. Round Robin\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                fcfs(process, arrival_time, burst_time, n);
                break;
            case 2:
                sjf(process, arrival_time, burst_time, n);
                break;
            case 3:
                priority_scheduling(process, arrival_time, burst_time, priority, n);
                break;
            case 4:
                round_robin(process, arrival_time, burst_time, n);
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

