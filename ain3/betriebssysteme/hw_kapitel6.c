#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define ITERATIONS 1000000
#define CTX_ITERATIONS 100000

// Measure timer precision
void measure_timer_precision() {
  struct timeval start, end;
  int i;
  long min_diff = 999999999;

  printf("Measuring timer precision...\n");

  for (i = 0; i < 1000; i++) {
    gettimeofday(&start, NULL);
    gettimeofday(&end, NULL);

    long diff =
        (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);

    if (diff > 0 && diff < min_diff) {
      min_diff = diff;
    }
  }

  printf("Timer precision: ~%ld microseconds\n\n", min_diff);
}

// Measure system call cost
void measure_syscall_cost() {
  struct timeval start, end;
  int i;
  char buf[1];

  printf("Measuring system call cost (%d iterations)...\n", ITERATIONS);

  gettimeofday(&start, NULL);

  for (i = 0; i < ITERATIONS; i++) {
    read(0, buf, 0); // 0-byte read system call
  }

  gettimeofday(&end, NULL);

  long elapsed =
      (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);

  double cost_per_call = (double)elapsed / ITERATIONS;

  printf("Total time: %ld microseconds\n", elapsed);
  printf("Cost per system call: %.3f microseconds\n\n", cost_per_call);
}

// Measure context switch cost
void measure_context_switch_cost() {
  int pipe1[2], pipe2[2];
  pid_t pid;
  char buf = 'X';
  struct timeval start, end;
  cpu_set_t set;

  printf("Measuring context switch cost (%d iterations)...\n", CTX_ITERATIONS);

  // Create two pipes
  if (pipe(pipe1) < 0 || pipe(pipe2) < 0) {
    perror("pipe");
    exit(1);
  }

  // Pin to CPU 0
  CPU_ZERO(&set);
  CPU_SET(0, &set);

  if (sched_setaffinity(0, sizeof(set), &set) < 0) {
    perror("sched_setaffinity");
    exit(1);
  }

  pid = fork();

  if (pid < 0) {
    perror("fork");
    exit(1);
  }

  if (pid == 0) {
    // Child process - also pin to CPU 0
    if (sched_setaffinity(0, sizeof(set), &set) < 0) {
      perror("child sched_setaffinity");
      exit(1);
    }

    // Close unused pipe ends
    close(pipe1[1]);
    close(pipe2[0]);

    for (int i = 0; i < CTX_ITERATIONS; i++) {
      read(pipe1[0], &buf, 1);  // Read from parent
      write(pipe2[1], &buf, 1); // Write to parent
    }

    close(pipe1[0]);
    close(pipe2[1]);
    exit(0);

  } else {
    // Parent process
    // Close unused pipe ends
    close(pipe1[0]);
    close(pipe2[1]);

    gettimeofday(&start, NULL);

    for (int i = 0; i < CTX_ITERATIONS; i++) {
      write(pipe1[1], &buf, 1); // Write to child
      read(pipe2[0], &buf, 1);  // Read from child
    }

    gettimeofday(&end, NULL);

    close(pipe1[1]);
    close(pipe2[0]);

    wait(NULL); // Wait for child to finish

    long elapsed =
        (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);

    // Each iteration involves 2 context switches (parent->child, child->parent)
    double cost_per_switch = (double)elapsed / (CTX_ITERATIONS * 2);

    printf("Total time: %ld microseconds\n", elapsed);
    printf("Cost per context switch: %.3f microseconds\n\n", cost_per_switch);
  }
}

int main() {
  printf("========================================\n");
  printf("System Call and Context Switch Benchmark\n");
  printf("========================================\n\n");

  measure_timer_precision();
  measure_syscall_cost();
  measure_context_switch_cost();

  printf("Benchmark complete.\n");

  return 0;
}
