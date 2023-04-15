#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <zlib.h>

#define CHUNK_SIZE 16384

int compress_file(const char *src_path, const char *dst_path)
{
    std::ifstream ifs(src_path, std::ios::binary);
    if (!ifs)
    {
        std::cerr << "Failed to open input file: " << src_path << std::endl;
        return -1;
    }

    std::ofstream ofs(dst_path, std::ios::binary);
    if (!ofs)
    {
        std::cerr << "Failed to open output file: " << dst_path << std::endl;
        return -1;
    }

    std::ostringstream oss;
    oss << ifs.rdbuf();
    std::string data = oss.str();

    z_stream stream;
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;

    if (deflateInit(&stream, Z_DEFAULT_COMPRESSION) != Z_OK)
    {
        std::cerr << "Failed to initialize zlib" << std::endl;
        return -1;
    }

    stream.avail_in = data.size();
    stream.next_in = (Bytef *)data.c_str();

    char out[CHUNK_SIZE];
    do
    {
        stream.avail_out = CHUNK_SIZE;
        stream.next_out = (Bytef *)out;
        if (deflate(&stream, Z_FINISH) == Z_STREAM_ERROR)
        {
            std::cerr << "Failed to compress data using zlib" << std::endl;
            deflateEnd(&stream);
            return -1;
        }
        std::streamsize count = CHUNK_SIZE - stream.avail_out;
        ofs.write(out, count);
    } while (stream.avail_out == 0);

    deflateEnd(&stream);
    return 0;
}

int decompress_file(const char *src_path, const char *dst_path)
{
    std::ifstream ifs(src_path, std::ios::binary);
    if (!ifs)
    {
        std::cerr << "Failed to open input file: " << src_path << std::endl;
        return -1;
    }
    std::ofstream ofs(dst_path, std::ios::binary);
    if (!ofs)
    {
        std::cerr << "Failed to open output file: " << dst_path << std::endl;
        return -1;
    }
    z_stream stream;
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;
    if (inflateInit(&stream) != Z_OK)
    {
        std::cerr << "Failed to initialize zlib" << std::endl;
        return -1;
    }
    char buffer[CHUNK_SIZE];
    do
    {
        stream.avail_in = ifs.read(buffer, CHUNK_SIZE).gcount();
        if (stream.avail_in == 0)
        {
            break;
        }
        stream.next_in = (Bytef *)buffer;
        do
        {
            stream.avail_out = CHUNK_SIZE;
            stream.next_out = (Bytef *)buffer;
            if (inflate(&stream, Z_NO_FLUSH) == Z_STREAM_ERROR)
            {
                std::cerr << "Failed to decompress data using zlib" << std::endl;
                inflateEnd(&stream);
                return -1;
            }
            std::streamsize count = CHUNK_SIZE - stream.avail_out;
            ofs.write(buffer, count);
        } while (stream.avail_out == 0);
    } while (true);
    inflateEnd(&stream);
    return 0;
}