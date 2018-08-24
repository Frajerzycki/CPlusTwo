
#include <sys/stat.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#define FILE_SEPARATOR '\\'
#else
#define FILE_SEPARATOR '/'
#endif

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
    // Add terminator at the end and read file into buffer.
    buffer[fread(buffer, 1, LENGTH, file)] = 0;
    // Close stream.
    fclose(file);
    return buffer;
}

void write_file(const char *path, const char *to_write)
{
    // Open file.
    FILE *file = fopen(path, "wb");
    // If can't open file.
    if (!file)
    {
        fprintf(stderr, "Can't open file %s.", path);
        return;
    }
    // Write to file.
    fwrite(to_write, strlen(to_write), 1, file);
    // Close stream.
    fclose(file);
}

void read_structure_from_file(const char *path, void *variable)
{
    // Open file.
    FILE *file = fopen(path, "rb");
    // If can't open file.
    if (!file)
    {
        fprintf(stderr, "Can't open file %s.", path);
        return;
    }
    // Allocates buffer with size LENGTH+1 to add terminator at the end.
    fread(variable, sizeof(variable), 1, file);
    // Close stream.     access(const char *path, int amode);
    fclose(file);
}

void write_structure_to_file(const char *path, const void *to_write)
{
    // Open file.
    FILE *file = fopen(path, "wb");
    // If can't open file.
    if (!file)
    {
        fprintf(stderr, "Can't open file %s.", path);
        return;
    }
    // Write to file.
    fwrite(to_write, sizeof(to_write), 1, file);
    // Close stream.
    fclose(file);
}

void process_file(void(process)(char *), const char *path, size_t buffer_size)
{
    // Open file.
    FILE *file = fopen(path, "rb");
    // If can't open file.
    if (!file)
    {
        fprintf(stderr, "Can't open file %s.", path);
        return;
    }
    // Allocate memory for buffer plus one, beacuse of terminator.
    char *buffer = malloc(buffer_size + 1);
    // Length of readed bytes.
    size_t len;
    // Process file.
    while ((len = fread(buffer, buffer_size, 1, file)) != 0)
    {
        //Add terminator
        buffer[len] = 0;
        process(buffer);
    }
    // Free memory.
    free(buffer);
    // Close stream.
    fclose(file);
}

bool is_absolute(const char *path)
{
    if (strlen(path) < 2)
        return false;
#ifdef _WIN32
    return path[1] == ':';
#else
    return path[0] == '/';
#endif
}