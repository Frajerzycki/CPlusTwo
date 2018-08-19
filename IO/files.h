#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int length_of_file(const char *path)
{
    struct stat st;
    stat(path, &st);
    return st.st_size;
}

char *read_file(const char *path)
{
    // Open file.
    FILE *file = fopen(path, "rb");
    // If can't open file.
    if (!file)
    {
        fprintf(stderr, "Can't open file %s.", path);
        return NULL;
    }
    // Length of file.
    const size_t LENGTH = length_of_file(path);
    // Allocates buffer with size LENGTH+1 to add terminator at the end.
    char *buffer = malloc(LENGTH + 1);
    // Add terminator at the end.
    const size_t len = fread(buffer, 1, LENGTH, file);
    buffer[len] = 0;
    return buffer;
}