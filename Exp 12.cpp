#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5   // Number of philosophers

sem_t forks[N];
sem_t room;   // To avoid deadlock

void* philosopher(void* num) {
    int id = *(int*)num;

    while (1) {
        printf("Philosopher %d is thinking...\n", id);
        sleep(1);

        // Enter room (max 4 philosophers)
        sem_wait(&room);

        // Pick left fork
        sem_wait(&forks[id]);
        printf("Philosopher %d picked left fork.\n", id);

        // Pick right fork
        sem_wait(&forks[(id + 1) % N]);
        printf("Philosopher %d picked right fork.\n", id);

        // Eating
        printf("Philosopher %d is eating...\n", id);
        sleep(2);

        // Release forks
        sem_post(&forks[(id + 1) % N]);
        sem_post(&forks[id]);
        sem_post(&room);

        printf("Philosopher %d has finished eating.\n", id);
    }
}

int main() {
    pthread_t tid[N];
    int philosopher_ids[N];

    // Initialize semaphores
    sem_init(&room, 0, 4); // Allow only 4 philosophers to avoid deadlock
    for (int i = 0; i < N; i++)
        sem_init(&forks[i], 0, 1);

    // Create philosopher threads
    for (int i = 0; i < N; i++) {
        philosopher_ids[i] = i;
        pthread_create(&tid[i], NULL, philosopher, &philosopher_ids[i]);
    }

    // Join threads (infinite loop)
    for (int i = 0; i < N; i++)
        pthread_join(tid[i], NULL);

    return 0;
}
