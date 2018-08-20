
#include <sys/stat.h>
#define NULL (void *)0
struct _IO_FILE *stderr;
#define stderr stderr
typedef unsigned long size_t;
size_t strlen(const char *);
typedef struct _IO_FILE FILE;
FILE *fopen(const char *__restrict__, const char *__restrict__);
int fclose(FILE *);
size_t fread(void *__restrict__, size_t, size_t, FILE *__restrict__);
size_t fwrite(const void *__restrict__, size_t, size_t, FILE *__restrict__);
int fprintf(FILE *__restrict__, const char *__restrict__, ...);

void *malloc(size_t);

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
    // Close stream.
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