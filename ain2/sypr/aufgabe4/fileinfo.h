#ifndef FILEINFO_H
#define FILEINFO_H


#include <stddef.h> // size_t
#include <limits.h>   // NAME_MAX

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
void fileinfo_print(const fileinfo *fi);
void fileinfo_destroy(fileinfo *fi);

#endif
