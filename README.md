# hexdump clone

This is a basic clone of the Linux utility `hexdump`. It takes a path to a target file as it's single argument at the command-line. It then displays the contents of the file in hex, 16 bytes per line. It is meant to simulate the default output of `hexdump` with no extra flags passed.

## Code

The program consists of a single source file that contains five functions:

```c
int main(int argc, char *argv[]);
unsigned long get_file_size(FILE *file_ptr);
unsigned char * hex_chunk_alloc(int chunk_size);
int hexdump_chunk_print(char *chunk, unsigned int chunk_s, int chunk_seg);
int hexdump(FILE *f_buffer);
```
