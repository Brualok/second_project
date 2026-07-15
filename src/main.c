/*
Главный модуль программы getopt.

Терземан Андрей Александрович
МК-101
*/


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "lib_main.h"
#include "getopt.h"



static void print_usage(const char* prog_name)
{
	printf("Use: %s -i file [-o offset] [-l size] [-g chunk_size] [-n chunk_count]\n", prog_name);
	printf("       %s -d directory [-o offset] [-l size] [-g chunk_size] [-n chunk_count]\n", prog_name);
}


int main (int argc, char *argv[]) 
{

	int opt;
	char* filename = NULL;
	char* dirname = NULL;
	off_t offset = 0;
	size_t size = (size_t)-1;   // -1 означает "до конца файла" 
	int group_size = 1;
	int count_per_line = 16;
	//while ((opt = getopt (argc, argv, "i:o:l:g:n:d")) != -1) 
	//{
	//	switch (opt)
	//	{
	//		case 'i':
	//			filename = optarg;
	//			break;

	//		case 'o': 
	//		{
	//			char* endptr;
	//			offset = strtoll(optarg, &endptr, 0);
	//			if (*endptr != '\0' || offset < 0) 
	//			{
	//				fprintf(stderr, "Неверное значение смещения: %s\n", optarg);
	//				return EXIT_FAILURE;
	//			}
	//			break;
	//		}
	//		case 'l': 
	//		{
	//			char* endptr;
	//			long val = strtol(optarg, &endptr, 0);
	//			/* разрешаем -1 (означает весь файл) */
	//			if (*endptr != '\0' || val < -1) 
	//			{
	//				fprintf(stderr, "Неверный размер: %s\n", optarg);
	//				return EXIT_FAILURE;
	//			}
	//			size = (size_t)val;  // если val == -1, то size станет (size_t)-1
	//			break;
	//		}
	//		case 'g': 
	//		{
	//			char* endptr;
	//			long val = strtol(optarg, &endptr, 0);
	//			if (*endptr != '\0' || val <= 0) 
	//			{
	//				fprintf(stderr, "Неверный размер кусочка: %s\n", optarg);
	//				return EXIT_FAILURE;
	//			}
	//			group_size = (int)val;
	//			break;
	//		}
	//		case 'n': 
	//		{
	//			char* endptr;
	//			long val = strtol(optarg, &endptr, 0);
	//			if (*endptr != '\0' || val <= 0) 
	//			{
	//				fprintf(stderr, "Неверное количество кусочков в строке: %s\n", optarg);
	//				return EXIT_FAILURE;
	//			}
	//			count_per_line = (int)val;
	//			break;
	//		}
	//		case 'd':
	//			dirname = optarg;
	//			break;
	//		default:
	//			print_usage(argv[0]);
	//			return EXIT_FAILURE;
	//	}
	//}
	while ((opt = getopt(argc, argv, "i:o:l:g:n:d:f:")) != -1) {
		switch (opt) {
		case 'i':
			filename = optarg;
			break;
		case 'o':
			if (sscanf(optarg, "%ld", &offset) != 1) {
				fprintf(stderr, "Error: Option -o requires an integer argument.\n");
				return 1;
			}
			break;
		case 'l':
			if (sscanf(optarg, "%lld", &size) != 1) {
				fprintf(stderr, "Error: Option -l requires an integer argument.\n");
				return 1;
			}
			break;
		case 'g':
			if (sscanf(optarg, "%d", &group_size) != 1) {
				fprintf(stderr, "Error: Option -g requires an integer argument.\n");
				return 1;
			}
			break;
		case 'n':
			if (sscanf(optarg, "%d", &count_per_line) != 1) {
				fprintf(stderr, "Error: Option -n requires an integer argument.\n");
				return 1;
			}
			break;
		case 'd':
			dirname = optarg;
			break;
		default:
			fprintf(stderr, "Error: invalid arguments.\n");
			return 1;
		}
	}

	if (dirname != NULL) {
		if (hexdump_directory(dirname, offset, size, group_size, count_per_line) != 0)
			return 1;
	}
	if (filename != NULL) {
		if (hexdump_file(filename, offset, size, group_size, count_per_line) != 0)
			return 1;
	}
	else {
		fprintf(stderr, "Needed -i, or -d.\n");
		print_usage(argv[0]);
		return 1;
	}

	return 0;
}


