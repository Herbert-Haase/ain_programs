/*
 * list.c
 *
 * Listet Verzeichnisse auf.
 * Verwendet Funktionen nach POSIX-Standard.
 * Wegen S_IFMT und S_IFDIR mit -D_XOPEN_SOURCE uebersetzen!
 *
 * Author H.Drachenfels
 * Erstellt am: 6.6.2013
 */

#include <stdio.h>  /* fprintf, printf */
#include <string.h> /* strerror */

#include <sys/stat.h>  /* struct stat, S_IFMT, S_IFDIR */
#include <dirent.h>    /* DIR, struct dirent, opendir, readdir */
#include <errno.h>     /* errno */

int main(int argc, char *argv[])
{
    struct stat s;    /* Dateistatus */
    DIR *d;           /* geoeffnetes Verzeichnis */
    struct dirent *e; /* gelesener Verziechniseintrag */
    int i;

    for (i = 1; i < argc; ++i)
    {
        if (stat(argv[i], &s) == -1)
        {
            fprintf(stderr, "%s existiert nicht (errno %d: %s)\n",
                    argv[i], errno, strerror(errno));
            continue;
        }

        if ((s.st_mode & S_IFMT) != S_IFDIR)
        {
            fprintf(stderr, "%s ist kein Verzeichnis\n", argv[i]);
            continue;
        }

        d = opendir(argv[i]);
        if (d == NULL)
        {
            fprintf(stderr, "%s kann nicht geoeffnet werden (errno %d: %s)\n",
                    argv[i], errno, strerror(errno));
            continue;
        }

        errno = 0;

        while ((e = readdir(d)) != NULL)
        {
            printf("%s/%s\n", argv[i], e->d_name);
        }

        if (errno)
        {
            fprintf(stderr, "Lesefehler in %s (errno %d: %s)\n",
                    argv[i], errno, strerror(errno));
        }

        closedir(d);
    }

    return 0;
}

