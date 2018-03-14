# hexdump clone

The objective of this project is to build a simple hexdump clone. It may support different display formats, such as hex values in groups of 2/4/8 bytes.

Here is an example of the default hexdump output format:

```
0000000 2023 6568 6478 6d75 2070 6c63 6e6f 0a65
0000010 540a 6568 6f20 6a62 6365 6974 6576 6f20
0000020 2066 6874 7369 7020 6f72 656a 7463 6920
0000030 2073 6f74 6220 6975 646c 6120 6720 6e65
0000040 7265 6369 6820 7865 7564 706d 632d 6f6c
0000050 656e 6c20 6269 6172 7972 7420 6168 2074
0000060 6977 6c6c 7420 6b61 2065 2061 7562 6666
0000070 7265 6320 6e6f 6174 6e69 6e69 2067 6874
0000080 2065 7962 6574 2073 666f 6120 6620 6c69
0000090 2065 7361 6920 706e 7475 6120 646e 6420
00000a0 7369 6c70 7961 7420 6568 6820 7865 7564
00000b0 706d 6f20 2066 6874 7365 2065 7962 6574
00000c0 2e73 4920 2074 616d 2079 7573 7070 726f
00000d0 2074 6964 6666 7265 6e65 2074 6f66 6d72
00000e0 7461 2c73 7320 6375 2068 7361 6420 7369
00000f0 6c70 7961 6e69 2067 6f77 6472 2073 726f
0000100 6420 756f 6c62 2d65 6f77 6472 2e73 
```

Basic tasks:  
- Open file for reading
- Calculate the size of the file
- Use a pointer to move forward in the file in 16-byte chunks
    - Find modulo to calculate size of last chunk in case its <16 bytes
- Pass these 16 byte chunks to the display function
- Format the output of these bytes to resemble the output above
- Print one line per 16 byte chunk

