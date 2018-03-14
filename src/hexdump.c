#include <stdio.h>
#include <stdlib.h>

#define CHUNK_SIZE 0x10

unsigned long get_file_size(FILE *file_ptr);
int hexdump(FILE *f_buffer);


int hexdump(FILE *f_buffer)
{
    unsigned long f_size = get_file_size(f_buffer);
    unsigned int chunks = (f_size / CHUNK_SIZE);
    unsigned int leftover_chunk_size = (f_size % CHUNK_SIZE);
    unsigned int chunk_seg;
    
    unsigned int c = 0;
    while (c < chunks)
    {
        //  Calculate the offset into the file
        chunk_seg = c * CHUNK_SIZE;
        c++;
        
        // Allocate memory and ensure there were no errors
        unsigned char *chunk_buf = NULL;
        chunk_buf = (unsigned char *)malloc(((CHUNK_SIZE)*sizeof(unsigned char)));

        if (!chunk_buf)
        {
            printf("Allocation of memory failed\n");
            return 0;
        }

        // Read bytes into the newly allocated buffer
        fread(chunk_buf, 1, CHUNK_SIZE, f_buffer);
        
        // Print the file offset and begin looping through the bytes in the buffer
        printf("0x%08x:| ", chunk_seg);
        for (int i = 0; i < CHUNK_SIZE; i+=2)
        {
            unsigned char a, b;
            a = (unsigned char)chunk_buf[i];
            b = (unsigned char)chunk_buf[i+1];
            
            printf("%02x%02x ", a, b);
        }

        printf("\n");
        free(chunk_buf);

    }

    if (leftover_chunk_size)
    {
        //  Calculate the offset into the file
        chunk_seg = c * CHUNK_SIZE;

        // Allocate memory and ensure there were no errors
        unsigned char *chunk_buf = NULL;
        chunk_buf = (unsigned char *)malloc(((leftover_chunk_size)*sizeof(unsigned char)));

        if (!chunk_buf)
        {
            printf("Allocation of memory failed\n");
            return 0;
        }

        fread(chunk_buf, 1, CHUNK_SIZE, f_buffer);
        printf("0x%08x:| ", chunk_seg);
        for (int i = 0; i < leftover_chunk_size; i+=2)
        {
            unsigned char a, b;
            a = (unsigned char)chunk_buf[i];
            b = (unsigned char)chunk_buf[i+1];
            printf("%02x%02x ", a, b);
        }
        printf("\n");
        free(chunk_buf);

    }

    printf("[+] File size: %lu\n", f_size);
    return 1;
}

// Calculate the file size
unsigned long get_file_size(FILE *file_ptr)
{
    unsigned long file_len;

    fseek(file_ptr, 0, SEEK_END);                // seek to end of file
    file_len = ftell(file_ptr);
    rewind(file_ptr);
    return file_len;
}


int main(int argc, char *argv[])
{
    if (argc > 2 || argc < 2)
    {
        printf("usage: %s <filename>\n", argv[0]);
        return 0;
    }

    FILE *fileptr;
    char *target_file_path = argv[1];

    fileptr = fopen(target_file_path, "rb");    // fopen in binary mode
    if (!fileptr)
    {
        printf("Error: file could not be opened for reading. Exiting.\n");
        return 0;
    }

    if (hexdump(fileptr) == 0)
    {
        fclose(fileptr);
        return 0;
    }

    fclose(fileptr);
    return 1;
}
