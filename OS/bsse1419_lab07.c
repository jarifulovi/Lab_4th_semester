#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define NUM_POINTS 1000
#define NUM_THREADS 100

int total_points_in_circle = 0;


void* monte_carlo_simulation(void* arg) {
    int points_in_circle = 0;
    int i;
    double x, y;
    
    srand(time(NULL) + *((int*)arg)); // Seed of random number generator
    
    for (i = 0; i < NUM_POINTS; i++) {
        x = (double)rand() / RAND_MAX * 2 - 1;  // Random x-coordinate between -1 and 1
        y = (double)rand() / RAND_MAX * 2 - 1;  // Random y-coordinate between -1 and 1
        
        // Check if the point lies within the circle
        if (x * x + y * y <= 1) {
            points_in_circle++;
        }
    }
    // Add the points in the circle
    total_points_in_circle += points_in_circle; 
    
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_args[NUM_THREADS];
    int i;
    
    
    // Create threads
    for (i = 0; i < NUM_THREADS; i++) {
        thread_args[i] = i;
        pthread_create(&threads[i], NULL, monte_carlo_simulation, &thread_args[i]);
    }
    
    // Join threads
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    
    // Calculate Pi
    double pi_estimate = 4.0 * total_points_in_circle / (NUM_POINTS * NUM_THREADS);
    printf("Estimated value of Pi: %f\n", pi_estimate);
    
    
    return 0;
}
