#include "asm.h"




int asm_write(FILE *f, int ic) {
	switch (ic) {
		case '>': fwrite(MOVR, sizeof(char) * 3, 1, f); return 3;
		case '<': fwrite(MOVL, sizeof(char) * 3, 1, f); return 3;
		case '+': fwrite(INCR, sizeof(char) * 3, 1, f); return 3;
		case '-': fwrite(DECR, sizeof(char) * 3, 1, f); return 3;
		default: return 0;
	}
}

int asm_asm(FILE *ifp, FILE *ofp) {
	int c;
	
	long size = 0;
	
	int count = 0;
	
	while ((c = fgetc(ifp)) != EOF) {
		if (c == '[') count++;
		if (c == ']') count--;
		
			
		
		size += asm_write(ofp, c);
	}
}
