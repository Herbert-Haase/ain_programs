#include "fileinfo.h"
#include <dirent.h>
#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

static void list_directory(const char *filename, fileinfo *cd);
static void print_regular(const char *f_name, const size_t groesse);
static void fin_print(const char *path, const fileinfo *in, bool pMode);
static void print_directory(const char *path, const char *f_name,
                            const fileinfo *in);
static void print_other(const char *f_name);
static void f_destroy(fileinfo *fi);

fileinfo *fileinfo_create(const char *filename) {
  errno = 0;

  if (strlen(filename) > NAME_MAX) {
    errno = ENAMETOOLONG;
    return NULL;
  }

  fileinfo *file_i = malloc(sizeof(fileinfo));
  if (file_i == NULL) {
    return NULL;
  }
  strcpy(file_i->f_name, filename);

  struct stat s;

  if (lstat(filename, &s) == -1) {
    free(file_i);
    return NULL;
  }
  file_i->next = NULL;
  if (S_ISREG(s.st_mode)) {
    file_i->size = s.st_size;
    file_i->type = filetype_regular;
  } else if (S_ISDIR(s.st_mode)) {
    file_i->type = filetype_directory;
    file_i->contains = NULL;
    list_directory(filename, file_i);
  } else {
    file_i->type = filetype_other;
  }
  return file_i;
}

static void list_directory(const char *filename, fileinfo *cd) {
  errno = 0;
  if (chdir(filename) != 0) {
    return;
  }
  DIR *d = opendir(".");
  if (!d) {
    chdir("../");
    return;
  }

  fileinfo *this = NULL;
  fileinfo *last = NULL;
  bool first = true;
  const struct dirent *e;
  while ((e = readdir(d)) != NULL) {
    if (strcmp(e->d_name, ".") == 0 || strcmp(e->d_name, "..") == 0) {
      continue;
    }
    this = fileinfo_create(e->d_name);
    if (first) {
      cd->contains = this;
      first = false;
    } else {
      last->next = this;
    }
    last = this;
  }
  if (errno) {
    closedir(d);
    return;
  }
  chdir("../");
  if (closedir(d) == -1) {
    return;
  }
}

static void print_regular(const char *f_name, const size_t groesse) {
  printf("%s (regular, %zu Byte)\n", f_name, groesse);
}

static void f_destroy(fileinfo *fi) {
  if (fi == NULL)
    return;
  if (fi->type == filetype_directory) {
    f_destroy(fi->contains);
  }
  f_destroy(fi->next);
  free(fi);
}
void fileinfo_destroy(fileinfo *fi) {
  if (fi == NULL)
    return;
  if (fi->type == filetype_directory) {
    f_destroy(fi->contains);
  }
  free(fi);
}

static void print_directory(const char *path, const char *f_name,
                            const fileinfo *fi) {
  char *n_path = malloc(strlen(path) + strlen(f_name) + 2);
  if (n_path == NULL) {
    printf("%s/... (PATHTOOLONG or OOM)\n", f_name);
  }
  strcpy(n_path ? n_path : "PATHTOOLONG", path);
  if (strcmp("", path) != 0) {
    strcat(n_path, "/");
  }
  strcat(n_path ? n_path : "PATHTOOLONG", f_name);
  printf("\n%s:\n", n_path ? n_path : "PATHTOOLONG");
  fileinfo *in_ = fi->contains;
  if (in_ != NULL) {
    fin_print(n_path ? n_path : "PATHTOOLONG", in_, false);
    while ((in_ = in_->next) != NULL) {
      fin_print(n_path ? n_path : "PATHTOOLONG", in_, false);
    }
  }
  fi = fi->contains;
  if (fi != NULL) {
    fin_print(n_path ? n_path : "PATHTOOLONG", fi, true);
    while ((fi = fi->next) != NULL) {
      fin_print(n_path ? n_path : "PATHTOOLONG", fi, true);
    }
  }
  if (n_path)
    free(n_path);
}

static void fin_print(const char *path, const fileinfo *fi, bool pMode) {
  if (fi->type == filetype_directory) {
    if (pMode) {
      print_directory(path, fi->f_name, fi);
    } else {
      printf("%s (directory)\n", fi->f_name);
    }

  } else {
    if (!pMode) {
      fileinfo_print(fi);
    }
  }
}

static void print_other(const char *f_name) { printf("%s (other)\n", f_name); }

void fileinfo_print(const fileinfo *fi) {
  if (fi == NULL) {
    return;
  }
  if (fi->type == filetype_directory) {
    print_directory("", fi->f_name, fi);
  } else if (fi->type == filetype_regular) {
    print_regular(fi->f_name, fi->size);
  } else {
    print_other(fi->f_name);
  }
}
