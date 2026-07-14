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