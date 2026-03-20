#include <stdio.h>
#include <pthread.h>

pthread_mutex_t lockA = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lockB = PTHREAD_MUTEX_INITIALIZER;

void *thread1(void *arg) {
    pthread_mutex_lock(&lockA);
    printf("thread1: got A\n");
    for (volatile int i = 0; i < 1000000; i++);
    pthread_mutex_lock(&lockB);
    printf("thread1: got B\n");
    pthread_mutex_unlock(&lockB);
    pthread_mutex_unlock(&lockA);
    return NULL;
}

void *thread2(void *arg) {
    pthread_mutex_lock(&lockB);
    printf("thread2: got B\n");
    for (volatile int i = 0; i < 1000000; i++);
    pthread_mutex_lock(&lockA);
    printf("thread2: got A\n");
    pthread_mutex_unlock(&lockA);
    pthread_mutex_unlock(&lockB);
    return NULL;
}

int main(void) {
    pthread_t t1, t2;
    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}
