/*
Реализация функций для вывода содержимого файлов в шестнадцатеричном виде.

Терземан Андрей Александрович
МК-101
*/
#include "hexdump.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <sys/stat.h>
#include <dirent.h>
#include <limits.h>
#include <unistd.h>

/* Преобразование одного байта в два шестнадцатеричных символа */
static void byte_to_hex(unsigned char b, char out[2]) {
    static const char hexchars[] = "0123456789ABCDEF";
    out[0] = hexchars[b >> 4];
    out[1] = hexchars[b & 0x0F];
}
static void print_line(off_t offset, const unsigned char* data, size_t len,
    int group_size, int count_per_line) 
{
    printf("%08x ", (unsigned int)offset);

    size_t i, j;
    for (i = 0; i < len; i += group_size) 
    {
        size_t chunk_len = group_size;
        if (i + chunk_len > len)
            chunk_len = len - i;
        for (j = 0; j < (size_t)(group_size - chunk_len); ++j) 
        {
            putchar('0');
            putchar('0');
        }
        for (j = chunk_len; j > 0; --j) 
        {
            unsigned char b = data[i + j - 1];
            char hex[2];
            byte_to_hex(b, hex);
            putchar(hex[0]);
            putchar(hex[1]);
        }
        if (i + group_size < len)
            putchar(' ');
    }
    if (group_size == 1) 
    {
        printf(" | ");
        for (i = 0; i < len; ++i) 
        {
            unsigned char c = data[i];
            putchar(isprint(c) ? c : '.');
        }
    }

    putchar('\n');
}
int hexdump_file(const char* filename, off_t offset, size_t size,
    int group_size, int count_per_line) 
{
    FILE* file = fopen(filename, "rb");
    if (!file) 
    {
        perror("fopen");
        return -1;
    }
    if (fseek(file, 0, SEEK_END) != 0) 
    {
        perror("fseek");
        fclose(file);
        return -1;
    }
    long file_size = ftell(file);
    if (file_size < 0) 
    {
        perror("ftell");
        fclose(file);
        return -1;
    }
    rewind(file);
    if (offset >= file_size) 
    {
        fclose(file);
        return 0;
    }

    if (fseek(file, offset, SEEK_SET) != 0) 
    {
        perror("fseek");
        fclose(file);
        return -1;
    }
    size_t remaining;
    if (size == (size_t)-1) {
        remaining = (size_t)(file_size - offset);
    }
    else {
        remaining = size;
        if (remaining > (size_t)(file_size - offset))
            remaining = (size_t)(file_size - offset);
    }

    off_t current_offset = offset;
    size_t line_bytes = (size_t)group_size * count_per_line;
    unsigned char* buffer = malloc(line_bytes);
    if (!buffer) {
        perror("malloc");
        fclose(file);
        return -1;
    }

    while (remaining > 0) {
        size_t to_read = line_bytes;
        if (to_read > remaining)
            to_read = remaining;

        size_t read_count = fread(buffer, 1, to_read, file);
        if (read_count == 0) {
            if (feof(file))
                break;
            perror("fread");
            free(buffer);
            fclose(file);
            return -1;
        }

        print_line(current_offset, buffer, read_count,
            group_size, count_per_line);

        current_offset += read_count;
        remaining -= read_count;
    }

    free(buffer);
    fclose(file);
    return 0;
}