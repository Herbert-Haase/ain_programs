#include "fileinfo.h"

static void list_directory(const char *filename, fileinfo *cd);
static void print_regular(const char *f_name, const size_t groesse);
static void fin_print(const char *path, fileinfo *in, bool pMode);
static void print_directory(const char *path, const char *f_name, fileinfo *in);
static void print_other(const char *f_name);
static void f_destroy(fileinfo *fi);

fileinfo *fileinfo_create(const char *filename) {
  errno = 0;

  fileinfo *file_i = malloc(sizeof(fileinfo));
  assert(file_i != NULL);
  if (strlen(filename) > NAME_MAX) {
    errno = ENAMETOOLONG;
    perror(filename);
    free(file_i);
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
    perror("chdir");
    exit(EXIT_FAILURE);
  }
  DIR *d = opendir(".");
  if (!d) {
    perror(filename);
    exit(EXIT_FAILURE);
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
    perror(filename);
    closedir(d);
    exit(EXIT_FAILURE);
  }
  chdir("../");
  if (closedir(d) == -1) {
    perror(filename);
    exit(EXIT_FAILURE);
  }
}

static void print_regular(const char *f_name, const size_t groesse) {
  printf("%s (regular, %zu Byte)\n", f_name, groesse);
}

static void f_destroy(fileinfo *fi) {
  if (fi == NULL) {
    return;
  }
  if (fi->type == filetype_directory) {
    f_destroy(fi->contains);
  }
  f_destroy(fi->next);
  free(fi);
}
void fileinfo_destroy(fileinfo *fi) {
  if (fi == NULL) {
    return;
  }
  if (fi->type == filetype_directory) {
    f_destroy(fi->contains);
  }
  free(fi);
}

static void print_directory(const char *path, const char *f_name,
                            fileinfo *fi) {
  char *n_path = malloc(strlen(path) + strlen(f_name) + 2);
  if (!n_path) {
    perror("malloc p");
    exit(1);
  }
  strcpy(n_path, path);
  if (strcmp("", path) != 0) {
    strcat(n_path, "/");
  }
  strcat(n_path, f_name);
  printf("\n%s:\n", n_path);
  fileinfo *in_ = fi;
  in_ = in_->contains;
  if (in_ != NULL) {
    fin_print(n_path, in_, false);
    while ((in_ = in_->next) != NULL) {
      fin_print(n_path, in_, false);
    }
  }
  fi = fi->contains;
  if (fi != NULL) {
    fin_print(n_path, fi, true);
    while ((fi = fi->next) != NULL) {
      fin_print(n_path, fi, true);
    }
  }
  free(n_path);
}

static void fin_print(const char *path, fileinfo *fi, bool pMode) {
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

void fileinfo_print(fileinfo *fi) {
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
