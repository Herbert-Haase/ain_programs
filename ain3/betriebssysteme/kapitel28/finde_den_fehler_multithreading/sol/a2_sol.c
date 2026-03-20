#include <stdio.h>
#include <pthread.h>

typedef struct {
    int balance;
} Account;

Account a = {1000};
Account b = {1000};
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *transfer_ab(void *arg) {
    for (int i = 0; i < 100000; i++) {
        pthread_mutex_lock(&lock);     // fix: atomic transfer
        a.balance -= 1;
        b.balance += 1;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

void *transfer_ba(void *arg) {
    for (int i = 0; i < 100000; i++) {
        pthread_mutex_lock(&lock);    // fix: atomic transfer
        b.balance -= 1;
        a.balance += 1;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main(void) {
    pthread_t t1, t2;

    pthread_create(&t1, NULL, transfer_ab, NULL);
    pthread_create(&t2, NULL, transfer_ba, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("a = %d, b = %d, total = %d\n",
           a.balance, b.balance, a.balance + b.balance);
    return 0;
}
