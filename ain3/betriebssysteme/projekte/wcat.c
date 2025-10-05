// wcat.c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "%s <file>\n", argv[0]);
    exit(1);
  }
  FILE *file = fopen(argv[1], "r");
  if (file == NULL) {
    perror("Reading file failed");
    exit(1);
  }
  fseek(file, 0, SEEK_END);
  long size = ftell(file);
  rewind(file);
  char *buf = malloc((sizeof(char) * size) + 1);
  if (buf == NULL) {
    perror("out of memory");
    return 1;
  }
  size_t read = fread(buf, sizeof(char), size, file);
  while (read != size) {
    if (feof(file))
      printf("Unexpected end of file\n");
    else if (ferror(file))
      perror("Error reading file\n");
  }
  buf[read] = '\0';
  fprintf(stdout, "%s", buf);
  fclose(file);
  free(buf);

  return 0;
}
