#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t wrt;          // semaphore for writers
pthread_mutex_t m;  // mutex for reader count

int readcount = 0;  // number of readers
int shared_data = 0;

void *reader(void *arg)
{
    int id = *(int*)arg;

    pthread_mutex_lock(&m);
    readcount++;
    if (readcount == 1)
        sem_wait(&wrt);    // first reader locks writer
    pthread_mutex_unlock(&m);

    printf("Reader %d reads data: %d\n", id, shared_data);
    sleep(1);

    pthread_mutex_lock(&m);
    readcount--;
    if (readcount == 0)
        sem_post(&wrt);    // last reader releases writer
    pthread_mutex_unlock(&m);

    return NULL;
}

void *writer(void *arg)
{
    int id = *(int*)arg;

    sem_wait(&wrt);     // writer locks access

    shared_data++;
    printf("Writer %d writes data: %d\n", id, shared_data);
    sleep(1);

    sem_post(&wrt);     // writer releases access

    return NULL;
}

int main()
{
    pthread_t r1, r2, r3, w1, w2;

    int R1 = 1, R2 = 2, R3 = 3;
    int W1 = 1, W2 = 2;

    sem_init(&wrt, 0, 1);
    pthread_mutex_init(&m, NULL);

    // Create threads
    pthread_create(&r1, NULL, reader, &R1);
    pthread_create(&w1, NULL, writer, &W1);
    pthread_create(&r2, NULL, reader, &R2);
    pthread_create(&r3, NULL, reader, &R3);
    pthread_create(&w2, NULL, writer, &W2);

    // Wait for all threads to finish
    pthread_join(r1, NULL);
    pthread_join(w1, NULL);
    pthread_join(r2, NULL);
    pthread_join(r3, NULL);
    pthread_join(w2, NULL);

    sem_destroy(&wrt);
    pthread_mutex_destroy(&m);

    return 0;
}
