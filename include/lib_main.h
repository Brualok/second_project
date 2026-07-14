/*
Заголовочный файл библиотеки для вывода содержимого файлов в шестнадцатеричном виде.

Терземан Андрей Александрович
МК-101
*/
#ifndef HEXDUMP_H
#define HEXDUMP_H

#include <stdio.h>
#include <stddef.h>
#include <sys/types.h>

int hexdump_file(const char* filename, off_t offset, size_t size,
    int group_size, int count_per_line);


int hexdump_directory(const char* dirname, off_t offset, size_t size,
    int group_size, int count_per_line);


#endif
