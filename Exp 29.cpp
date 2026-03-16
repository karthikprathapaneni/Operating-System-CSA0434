#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

sem_t empty;      // Counts empty slots
sem_t full;       // Counts filled slots
pthread_mutex_t mutex; // Ensures mutual exclusion

void *producer(void *arg) {
    int item = 1;
    while(1) {
        sem_wait(&empty); // Wait for empty slot
        pthread_mutex_lock(&mutex);

        buffer[in] = item;
        printf("Producer produced: %d at %d\n", item, in);
        in = (in + 1) % BUFFER_SIZE;
        item++;

        pthread_mutex_unlock(&mutex);
        sem_post(&full); // Increase filled slot count
        
        sleep(1);
    }
}

void *consumer(void *arg) {
    while(1) {
        sem_wait(&full); // Wait for full slot
        pthread_mutex_lock(&mutex);

        int item = buffer[out];
        printf("Consumer consumed: %d from %d\n", item, out);
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty); // Increase empty slot count
        
        sleep(1);
    }
}

int main() {
    pthread_t p, c;

    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);

    pthread_join(p, NULL);
    pthread_join(c, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
