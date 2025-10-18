#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  if(argc != 2) {
    fprintf(stderr, "%s <amount mebibytes>\n",argv[0]);
    exit(1);
  }
  int m_bytes = atoi(argv[1]) * 10e5;
  char *arr = calloc(m_bytes, sizeof(char));
  while (1) {
    int a = 1;
    for (int i = 0; i < m_bytes; i++) {
      arr[i] += a;
    }
  }
  free(arr);
}
