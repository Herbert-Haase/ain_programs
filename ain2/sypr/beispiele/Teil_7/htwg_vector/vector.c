#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int *data;
  int size;     // Current number of elements
  int capacity; // Total allocated space
} Vector;

Vector *vector_create() {
  Vector *v = malloc(sizeof(Vector));
  v->size = 0;
  v->capacity = 10; // Start with capacity for 10 elements
  v->data = malloc(v->capacity * sizeof(int));
  return v;
}

void vector_push(Vector *v, int value) {
  if (v->size >= v->capacity) {
    // Need to grow the vector
    v->capacity *= 2; // Double the capacity
    v->data = realloc(v->data, v->capacity * sizeof(int));
    if (v->data == NULL) {
      fprintf(stderr, "realloc failed!\n");
      exit(1);
    }
    printf("Grew vector to capacity %d\n", v->capacity);
  }
  v->data[v->size] = value;
  v->size++;
}

int vector_get(Vector *v, int index) {
  if (index < 0 || index >= v->size) {
    fprintf(stderr, "Index out of bounds!\n");
    return -1;
  }
  return v->data[index];
}

void vector_print(Vector *v) {
  printf("Vector (size=%d, capacity=%d): ", v->size, v->capacity);
  for (int i = 0; i < v->size; i++) {
    printf("%d ", v->data[i]);
  }
  printf("\n");
}

void vector_free(Vector *v) {
  free(v->data);
  free(v);
}

int main(int argc, char *argv[]) {
  Vector *v = vector_create();

  // Add elements to trigger reallocations
  for (int i = 0; i < 50; i++) {
    vector_push(v, i * 10);
  }

  vector_print(v);

  printf("Element at index 25: %d\n", vector_get(v, 25));

  vector_free(v);

  return 0;
}
