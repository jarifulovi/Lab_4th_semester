#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include<stdlib.h>

#define NUM_READERS 3
#define NUM_WRITERS 2

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t writeMutex = PTHREAD_MUTEX_INITIALIZER;
int readersCount = 0;

int readFromFile(){
    FILE *file = fopen("shared_data.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(-1);
    }
    int data;
    fscanf(file, "%d", &data);
    fclose(file);
    return data;
}
void writeFromFile(int data){
    FILE *file = fopen("shared_data.txt","w");
    if(file == NULL){
        perror("error openning file");
        exit(-1);
    }
    
    fprintf(file,"%d",data);
    fclose(file);
}

void *reader(void *arg) {
    while(1) {
        pthread_mutex_lock(&mutex);
        readersCount++;
        if(readersCount == 1) {
            pthread_mutex_lock(&writeMutex);
        }
        pthread_mutex_unlock(&mutex);
        
       
        // Read from file
        intptr_t thread_num = (intptr_t)arg;
        printf("Reader %d reads shared data: %d\n", (int)thread_num, readFromFile());
        
        pthread_mutex_lock(&mutex);
        readersCount--;
        if(readersCount == 0) {
            pthread_mutex_unlock(&writeMutex);
        }
        pthread_mutex_unlock(&mutex);
        
        
        sleep(1);
    }
    
}

void *writer(void *arg) {
    while(1) {
        pthread_mutex_lock(&writeMutex);
        
        // Writing
        int dataToWrite = rand()%100;
        writeFromFile(dataToWrite);


        intptr_t thread_num = (intptr_t)arg;
        printf("Writer %d writes shared data: %d\n", (int)thread_num, dataToWrite);
        
        pthread_mutex_unlock(&writeMutex);
        
       
        sleep(2);
    }
}

int main() {
    pthread_t readers[NUM_READERS];
    pthread_t writers[NUM_WRITERS];
    
    // The reader and writer functions
    // only read and write an integer
    // variable from the file


    // Create reader threads
    for(long i = 0; i < NUM_READERS; i++) {
        pthread_create(&readers[i], NULL, reader, (void *)(intptr_t)i);
    }
    
    // Create writer threads
    for(long i = 0; i < NUM_WRITERS; i++) {
        pthread_create(&writers[i], NULL, writer, (void *)(intptr_t)i);
    }
    
    // Join reader threads
    for(int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }
    
    // Join writer threads
    for(int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }
    
    pthread_mutex_destroy(&mutex);
    pthread_mutex_destroy(&writeMutex);
    
    return 0;
}
