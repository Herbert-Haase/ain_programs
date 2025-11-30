#include <assert.h>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

unsigned long long count = 0;

// pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock;
pthread_t a, b;
pthread_attr_t attr;
unsigned long long ra, rb;
// pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
// unsigned char ready = 0;

void *worker(void *arg __attribute__((unused)))
{
  unsigned long long value = (unsigned long long)arg;
  for (int i = 0; i < 1e5; i++)
  {
    pthread_mutex_lock(&lock);
    count++;
    pthread_mutex_unlock(&lock);
  }
  return (void *)(count + value);
}

int main(void)
{
  pthread_mutex_init(&lock, NULL);
  pthread_attr_init(&attr);
  pthread_attr_setschedpolicy(&attr, SCHED_RR);
  int s = pthread_attr_setstacksize(&attr, 16384);
  assert(s != EINVAL);

  pthread_create(&a, &attr, worker, (void *)1);
  pthread_create(&b, &attr, worker, (void *)1);

  pthread_join(a, (void **)&ra);
  pthread_join(b, (void **)&rb);
  pthread_cond_wait(&cond, &lock);

  printf("count is: %llu\n", count);
  printf("worker a returned: %llu\n", ra);
  printf("worker b returned: %llu\n", rb);

  pthread_mutex_destroy(&lock);
  pthread_attr_destroy(&attr);
}
