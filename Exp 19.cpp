#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int counter = 0;
pthread_mutex_t lock;

void *increment(void *arg)
{
    int id = *(int*)arg;   // get thread ID safely

    for (int i = 0; i < 5; i++) {
        pthread_mutex_lock(&lock);

        counter++;
        printf("Thread %d incremented counter to: %d\n", id, counter);

        pthread_mutex_unlock(&lock);
        sleep(1);
    }
    return NULL;
}

int main()
{
    pthread_t t1, t2;

    int id1 = 1, id2 = 2;  // thread IDs

    pthread_mutex_init(&lock, NULL);

    pthread_create(&t1, NULL, increment, &id1);
    pthread_create(&t2, NULL, increment, &id2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&lock);

    printf("Final Counter Value: %d\n", counter);

    return 0;
}
