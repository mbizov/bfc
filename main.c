#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <getopt.h>

#include "asm.h"

#define ERROR_NONE 0
#define ERROR_LITE 1
#define ERROR_BAD  2

enum file_formats {
	RAW_BINARY = 0, PE_X86 = 1, BAD_FORMAT = -1
};

void help(char **argv) {
	printf("usage: %s [options...] infile...\n", argv[0]);
	printf("  -o outfile\twrite to outfile\n");
	printf("  -f format \toutput file format\n");
	printf("  -h        \tprint help message\n\n");
	
	printf("file formats:\n");
	printf("  bin\traw binary file\n");
	printf("  win32\twindows x86 binary\n");
	return;
}


char *outfile = "a.bin";
int fileformat = RAW_BINARY;

int main(int argc, char **argv) {
	
	if (argc == 1) {
		printf("error: no input file\n");
		printf("try '%s -h' for help\n", argv[0]);
		return ERROR_LITE;
	}
	
	opterr = 0;
	int c;
	while ((c = getopt(argc, argv, "o:f:h")) != -1) {
		switch (c) {
			case 'o': outfile = optarg; break;
			case 'f':
				if (!strcmp(optarg, "bin")) fileformat = RAW_BINARY;
				else if (!strcmp(optarg, "win32")) fileformat = PE_X86;
				else fileformat = BAD_FORMAT;
				break;
			case 'h': help(argv); return ERROR_NONE;
			default:
				printf("error: invalid argument\n");
				printf("try '%s -h' for help\n", argv[0]);
				return ERROR_LITE;
		}
	}
	
	/* handle user input errors */
	
	if (fileformat == BAD_FORMAT) {
		printf("error: invalid output file format\n");
		return ERROR_LITE;
	}
	if (optind == argc) {
		printf("error: no input files\n");
		return ERROR_LITE;
	}
	
	FILE *ifp = NULL; /* input file pointer */
	
	FILE *ofp = fopen(outfile, "ab"); /* output file pointer */
	
	for (int i = optind; i < argc; i++) {
		ifp = fopen(argv[i], "r");
		if (ifp == NULL) {
			printf("error: cannot open file '%s'", argv[i]);
			return ERROR_LITE;
		}
		asm_asm(ifp, ofp);
		fclose(ifp);
	}
}
