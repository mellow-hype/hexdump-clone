#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHUNK_SIZE 0x10

//  Function declarations
unsigned long get_file_size(FILE *file_ptr);
unsigned char * hex_chunk_alloc(int chunk_size);
int hexdump(FILE *f_buffer);


int hexdump_chunk_print(char *chunk, unsigned int chunk_s, int chunk_seg)
{
        // Print the file offset and begin looping through the bytes in the buffer
        printf("%08x: ", chunk_seg);
        for (int i = 0; i < chunk_s; i+=2)
        {
            unsigned char a, b;
            a = (unsigned char)chunk[i];
            b = (unsigned char)chunk[i+1];
            printf("%02x%02x ", b, a);
        }
        printf("\n");
}


unsigned char * hex_chunk_alloc(int chunk_size)
{
    // Allocate memory and ensure there were no errors
    unsigned char *chunk_buf = NULL;
    chunk_buf = (unsigned char *)malloc(((chunk_size)*sizeof(unsigned char)));
    if (!chunk_buf)
    {
        printf("Allocation of memory failed\n");
        return 0;
    }
    return chunk_buf;

}


int hexdump(FILE *f_buffer)
{
    unsigned long f_size = get_file_size(f_buffer);
    unsigned int chunks = (f_size / CHUNK_SIZE);
    unsigned int leftover_chunk_size = (f_size % CHUNK_SIZE);
    unsigned int chunk_seg;
    unsigned char *chunk_buf = NULL;
    
    // Print the header
    printf("%-8s|  0 1  2 3  4 5  6 7  8 9  A B  C D  E F \n", "-offset-");

    for (unsigned int c = 0; c < chunks; c++)
    {
        //  Calculate the offset into the file
        chunk_seg = c * CHUNK_SIZE;
        
        // Allocate memory and ensure there were no errors
        chunk_buf = hex_chunk_alloc(CHUNK_SIZE);

        // Read 16 bytes from the file pointer into the newly allocated buffer
        fread(chunk_buf, 1, CHUNK_SIZE, f_buffer);
        
        hexdump_chunk_print(chunk_buf, CHUNK_SIZE, chunk_seg);
        free(chunk_buf);
    }

    if (leftover_chunk_size)
    {
        //  Calculate the offset into the file
        chunk_seg += CHUNK_SIZE;

        // Allocate memory and ensure there were no errors
        chunk_buf = hex_chunk_alloc(leftover_chunk_size);

        // Read 16 bytes from the file pointer into the newly allocated buffer
        fread(chunk_buf, 1, leftover_chunk_size, f_buffer);
        
        hexdump_chunk_print(chunk_buf, leftover_chunk_size, chunk_seg);
        free(chunk_buf);
    }

    printf("[+] File size: %lu\n", f_size);
    return 1;
}

// Calculate the file size
unsigned long get_file_size(FILE *file_ptr)
{
    unsigned long file_len;
    fseek(file_ptr, 0, SEEK_END);               // seek to end of file
    file_len = ftell(file_ptr);                 // get position to calculate size
    rewind(file_ptr);                           // move position back to start
    return file_len;
}


int main(int argc, char *argv[])
{
    char *target_file_path = argv[1];
    FILE *fileptr;
    // Ensure two arguments were given
    if (argc > 2 || argc < 2)
    {
        printf("usage: %s <filename>\n", argv[0]);
        return 0;
    }

    // Open the file for reading in binary mode
    fileptr = fopen(target_file_path, "rb");
    if (!fileptr)
    {
        printf("Error: file could not be opened for reading. Exiting.\n");
        return 0;
    }

    // Call hexdump, return
    if (hexdump(fileptr) == 0)
    {
        fclose(fileptr);
        return 0;
    }

    fclose(fileptr);
    return 1;
}
