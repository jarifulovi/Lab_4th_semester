#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h> // For sleep function

#define BUFFER_SIZE 5 // Size of the shared buffer
#define DELAY_PRODUCER 2 // Delay for producer in seconds
#define DELAY_CONSUMER 1 // Delay for consumer in seconds

sem_t empty, full; // Semaphores to control the buffer
pthread_mutex_t mutex; // Mutex to control access to the buffer

int buffer[BUFFER_SIZE]; // Shared buffer
int top = -1; // Index of the top of the stack

void display_buffer() {
    printf("Buffer: ");
    for (int i = 0; i < BUFFER_SIZE; i++) {
        printf("%d ",buffer[i]);
    }
    printf("\n");
}

void *producer(void *arg) {
    int item;
    while (1) {
        item = rand() % 100; // Generate a random item

        sem_wait(&empty); // Wait if the buffer is full
        pthread_mutex_lock(&mutex); // Lock the buffer

        top = (top + 1) % BUFFER_SIZE; // Move the top of the stack
        buffer[top] = item; // Put the item into the buffer
        printf("Produced item: %d\n", item);
        display_buffer(); // Display the buffer

        pthread_mutex_unlock(&mutex); // Unlock the buffer
        sem_post(&full); // Signal that the buffer is no longer empty

        sleep(DELAY_PRODUCER); // Introduce delay
    }
    pthread_exit(NULL);
}

void *consumer(void *arg) {
    int item;
    while (1) {
        sem_wait(&full); // Wait if the buffer is empty
        pthread_mutex_lock(&mutex); // Lock the buffer

        item = buffer[top]; // Take the item from the top of the stack
        printf("Consumed item: %d\n", item);
        display_buffer(); // Display the buffer

        buffer[top] = -1; // Mark the slot as empty
        top = (top - 1 + BUFFER_SIZE) % BUFFER_SIZE; // Move the top of the stack

        pthread_mutex_unlock(&mutex); // Unlock the buffer
        sem_post(&empty); // Signal that the buffer is no longer full

        sleep(DELAY_CONSUMER); // Introduce delay
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t producer_thread, consumer_thread;

    // Initialize buffer to indicate all slots are empty
    for (int i = 0; i < BUFFER_SIZE; i++) {
        buffer[i] = -1;
    }

    // Initialize semaphores and mutex
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    // Create producer and consumer threads
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    // Wait for threads to finish
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
