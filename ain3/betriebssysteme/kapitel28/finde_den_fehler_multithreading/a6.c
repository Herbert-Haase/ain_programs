#include <stdio.h>
#include <pthread.h>

pthread_mutex_t lock;
int shared = 0;

void *worker(void *arg) {
    pthread_mutex_lock(&lock);
    pthread_mutex_lock(&lock);
    shared++;
    printf("shared: %d",shared);
    pthread_mutex_unlock(&lock);
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main(void) {
    pthread_t t1, t2;
    pthread_create(&t1, NULL, worker, NULL);
    pthread_create(&t2, NULL, worker, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    printf("shared = %d\n", shared);
    return 0;
}
