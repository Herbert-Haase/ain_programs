#ifndef FILEINFO_H
#define FILEINFO_H

#define _POSIX_C_SOURCE 200112L
#include <dirent.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <assert.h>
#include <stdbool.h>

extern int errno;
enum filetype {
  filetype_regular,
  filetype_directory,
  filetype_other,
};

typedef struct fileinfo {
  enum filetype type;
  union {
    size_t size;
    struct fileinfo *contains;
  };
  char f_name[NAME_MAX + 1];
  struct fileinfo *next;
} fileinfo;

fileinfo *fileinfo_create(const char *filename);
void fileinfo_print(fileinfo *fi);
void fileinfo_destroy(fileinfo *fi);

#endif
