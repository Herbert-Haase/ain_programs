// wgrep.c
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
  if (argc < 3) {
    fprintf(stderr, "%s: searchterm [file ...]\n", argv[0]);
    exit(1);
  }
  for (int i = 2; i < argc; ++i) {

    FILE *fp = fopen(argv[i], "r");
    if (fp == NULL) {
      perror("Reading file failed");
      exit(1);
    }
    char *string = NULL;
    size_t size = 0;
    unsigned long line_num = 0;
    bool found = false;
    ssize_t chars_read;

    // list all lines
    printf("%s\n", argv[i]);
    while ((chars_read = getline(&string, &size, fp)) >= 0) {
      line_num++;
      if (strstr(string, argv[1]) != NULL) {
        found = true;
        printf("Line %ld: %s", line_num, string);
      }
    }
    if (!found) {
      puts("Nothing found");
    }
    fclose(fp);
    free(string);
  }
  return 0;
}
