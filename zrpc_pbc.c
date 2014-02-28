#include "pbc.h"
#include "zrpc_pbc.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

static void
zrpc_pbc_read_file (const char *filename , struct pbc_slice *slice) {
	FILE *f = fopen(filename, "rb");
	if (f == NULL) {
		slice->buffer = NULL;
		slice->len = 0;
		return;
	}
	fseek(f,0,SEEK_END);
	slice->len = ftell(f);
	fseek(f,0,SEEK_SET);
	slice->buffer = malloc(slice->len);
	fread(slice->buffer, 1 , slice->len , f);
	fclose(f);
}


static void
zrpc_pbc_dump(uint8_t *buffer, int sz) {
	int i , j;
	for (i=0;i<sz;i++) {
		printf("%02X ",buffer[i]);
		if (i % 16 == 15) {
			for (j = 0 ;j <16 ;j++) {
				char c = buffer[i/16 * 16+j];
				if (c>=32 && c<127) {
					printf("%c",c);
				} else {
					printf(".");
				}
			}
			printf("\n");
		}
	}

	printf("\n");
}

