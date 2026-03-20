#include <stdio.h>
#include <pthread.h>

int ready = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *waiter(void *arg) {
    pthread_mutex_lock(&lock);
    while (!ready) {                      // fix: re-check condition
        pthread_cond_wait(&cond, &lock);
    }
    printf("waiter: observed ready = %d\n", ready);
    pthread_mutex_unlock(&lock);
    return NULL;
}

void *signaler(void *arg) {
    pthread_mutex_lock(&lock);
    ready = 1;
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main(void) {
    pthread_t t1, t2;
    pthread_create(&t1, NULL, waiter, NULL);
    pthread_create(&t2, NULL, signaler, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}
