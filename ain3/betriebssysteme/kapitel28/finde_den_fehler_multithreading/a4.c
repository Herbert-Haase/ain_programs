#include <stdio.h>
#include <pthread.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
int resource = 0;

void *worker(void *arg) {
    pthread_mutex_lock(&lock);
    if (resource == 0) {
        printf("worker: error, resource is 0\n");
        return NULL;
    }
    resource++;
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main(void) {
    pthread_t t1, t2;

    resource = 0;
    pthread_create(&t1, NULL, worker, NULL);
    pthread_create(&t2, NULL, worker, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}
