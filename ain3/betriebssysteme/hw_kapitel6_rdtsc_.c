#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

// Read the Time Stamp Counter
static inline uint64_t rdtsc() {
  unsigned int lo, hi;
  // rdtsc instruction puts lower 32 bits in eax, upper 32 bits in edx
  __asm__ __volatile__("rdtsc" : "=a"(lo), "=d"(hi));
  return ((uint64_t)hi << 32) | lo;
}

// More accurate version with serializing instruction
static inline uint64_t rdtsc_serialized() {
  unsigned int lo, hi;
  // cpuid serializes - ensures all previous instructions complete
  __asm__ __volatile__("cpuid\n\t"
                       "rdtsc\n\t"
                       : "=a"(lo), "=d"(hi)::"%rbx", "%rcx");
  return ((uint64_t)hi << 32) | lo;
}

int main() {
  uint64_t start, end;
  uint64_t cycles;

  // Example 1: Measure rdtsc overhead
  printf("Measuring rdtsc overhead...\n");
  start = rdtsc();
  end = rdtsc();
  printf("rdtsc overhead: %lu cycles\n\n", end - start);

  // Example 2: Measure a system call
  printf("Measuring system call cost with rdtsc...\n");
  char buf[1];

  start = rdtsc_serialized();
  read(0, buf, 0); // 0-byte read
  end = rdtsc_serialized();

  cycles = end - start;
  printf("System call cost: %lu cycles\n\n", cycles);

  // Example 3: Average over many iterations
  printf("Measuring average over 1000 system calls...\n");
  start = rdtsc_serialized();

  for (int i = 0; i < 1000; i++) {
    read(0, buf, 0);
  }

  end = rdtsc_serialized();
  cycles = end - start;

  printf("Total cycles: %lu\n", cycles);
  printf("Average per call: %lu cycles\n\n", cycles / 1000);

  // Convert cycles to time (if you know CPU frequency)
  // Example: 3.0 GHz CPU
  double cpu_ghz = 3.0;
  double nanoseconds = (cycles / 1000.0) / cpu_ghz;
  printf("Approximate time per call: %.2f nanoseconds\n", nanoseconds);
  printf("(assuming %.1f GHz CPU)\n", cpu_ghz);

  return 0;
}
