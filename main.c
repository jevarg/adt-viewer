#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define NUMBER_OF_FILES 135

typedef struct __attribute__((__packed__)) adt_file
{
  unsigned char fname[15];
  int start;
  int length;
} adt_file_t;

adt_file_t *read_adt_file(FILE *stream)
{
    adt_file_t *adt_file = malloc(sizeof(adt_file_t));
    if (adt_file == NULL)
    {
        return NULL;
    }

    size_t nb_reads = fread(adt_file, sizeof(adt_file_t), 1, stream);
    if (!nb_reads)
    {
        return NULL;
    }

    if (adt_file->fname[0] != '*')
    {
        for (size_t i = 0; adt_file->fname[i]; i++)
        {
            adt_file->fname[i] =~ adt_file->fname[i];
        }
    }

    return adt_file;
}

int main(int argc, char const *argv[])
{
    adt_file_t *adt1[NUMBER_OF_FILES];
    FILE* file = fopen("hyper1r.adt", "rb");
    if (file == NULL)
    {
        fprintf(stderr, "Error: could not open file\n");
        return 1;
    }

    for (size_t i = 0; i < NUMBER_OF_FILES; i++)
    {
        adt1[i] = read_adt_file(file);
        if (adt1[i] != NULL)
        {
            printf("%zu: %s\n", i, adt1[i]->fname);
        }
    }

    fclose(file);

    for (size_t i = 0; i < NUMBER_OF_FILES; i++)
    {
        if (adt1[i] == NULL)
            continue;

        free(adt1[i]);
    }

    return 0;
}
