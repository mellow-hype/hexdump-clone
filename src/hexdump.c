#include <stdio.h>
#include <stdlib.h>



int hexdump(char * byte_buffer)
{

    return 0;
}

unsigned long get_file_size(FILE *file_ptr)
{
    unsigned long file_len;

    fseek(file_ptr, 0, SEEK_END);                // seek to end of file
    file_len = ftell(file_ptr);
    rewind(file_ptr);
    printf("File size: %lu\n", file_len);
    return file_len;
}


int main(int argc, char *argv[])
{
    if (argc > 2 || argc < 2)
    {
        printf("usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *fileptr;
    unsigned long file_len;
    char *target_file_path = argv[1];

    fileptr = fopen(target_file_path, "rb");    // fopen in binary mode
    file_len = get_file_size(fileptr);

    fclose(fileptr);
    return 0;
}