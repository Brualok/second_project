/*
Заголовочный файл библиотеки для вывода содержимого файлов в шестнадцатеричном виде.

Терземан Андрей Александрович
МК-101
*/
#pragma once 


#include <stdio.h>
#include <stddef.h>
#include <sys/types.h>


/*Ввожу функцию для работы с файлом
filename - имя файла
offset - смещение 
size - количество выводимых байт
group_size - размер кусочка
count_per_line - количество кусочков в строке*/
int hexdump_file(const char* filename, off_t offset, size_t size,
    int group_size, int count_per_line);

//Аналогичная функция для работы с директориями
int hexdump_directory(const char* dirname, off_t offset, size_t size,
    int group_size, int count_per_line);



