/*
 * count.c
 *
 * Zaehlt die Zeichen in Dateien.
 *
 * Author H.Drachenfels
 * Erstellt am: 8.6.2011
 */

#include <stdio.h>  /* fopen, fgetc, fclose, ferror, perror */

int main(int argc, char *argv[])
{
    FILE *fp;
    int i;
    int n;

    for (i = 1; i < argc; ++i)
    {
        fp = fopen(argv[i], "r");
        if (fp == NULL)
        {
            perror(argv[i]);
            continue;
        }

        n = 0;

        while (fgetc(fp) != EOF)
        {
            ++n;
        }

        if (ferror(fp))
        {
            perror(argv[i]);
            fclose(fp);
            continue;
        }

        printf("%s: %d Zeichen\n", argv[i], n);

        fclose(fp);
    }

    return 0;
}

