#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, const char **argv) {
  if (argc < 2) {
    perror("format: rm <arg>");
  }
  for (int i = 1; i < argc; i++) {
    if (unlink(argv[i]) != 0) {
      fprintf(stderr, "deleting '%s' failed: %s", argv[i], strerror(errno));
    }
  }
}
