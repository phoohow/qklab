#include "Lzlib.h"
#include <iostream>
#include <string>

int main()
{
    const char *src_path = "xx/input.txt";
    const char *dst_path = "xx/compressed.txt";
    const char *dec_path = "xx/decompressed.txt";

    compress_file(src_path, dst_path);
    decompress_file(dst_path, dec_path);
    return 0;
}
