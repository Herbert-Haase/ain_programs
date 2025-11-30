#include <assert.h>
#include <errno.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

unsigned long long count = 0;

pthread_t a, b;
unsigned long long ra, rb;

typedef struct __synchronizer_t
{
  pthread_mutex_t lock;
  pthread_cond_t cond;
  bool ready;
} synchronizer_t;

synchronizer_t s;

void wait(synchronizer_t *s)
{
  pthread_mutex_lock(&s->lock);
  while (s->ready == false)
    pthread_cond_wait(&s->cond, &s->lock);
  pthread_mutex_unlock(&s->lock);
}

void synchronizer_init(synchronizer_t *s)
{
  pthread_mutex_init(&s->lock, NULL);
  pthread_cond_init(&s->cond, NULL);
  s->ready = false;
}

void done(synchronizer_t *s)
{
  pthread_mutex_lock(&s->lock);
  s->ready = true;
  pthread_cond_signal(&s->cond);
  pthread_mutex_unlock(&s->lock);
}

void *worker(void *arg __attribute__((unused)))
{
  unsigned long long value = (unsigned long long)arg;
  for (int i = 0; i < 1e5; i++)
  {
    count++;
  }
  done(&s);
  return (void *)(count + value);
}

int main(void)
{
  pthread_mutex_init(&s.lock, NULL);
  // pthread_attr_init(&attr);
  // pthread_attr_setschedpolicy(&attr, SCHED_RR);
  // int s = pthread_attr_setstacksize(&attr, 16384);
  // assert(s != EINVAL);

  pthread_create(&a, NULL, worker, (void *)1);
  // pthread_create(&b, &attr, worker, (void *)1);

  // pthread_join(a, (void **)&ra);
  // pthread_join(b, (void **)&rb);
  wait(&s);

  printf("count is: %llu\n", count);
  // printf("worker a returned: %llu\n", ra);
  // printf("worker b returned: %llu\n", rb);

  pthread_mutex_destroy(&s.lock);
  pthread_cond_destroy(&s.cond);
  // pthread_attr_destroy(&attr);
}
