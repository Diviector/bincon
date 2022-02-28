#include "file_conversion.h"
#include <stdio.h>
#include <stdlib.h>

typedef unsigned char u_byte;
typedef unsigned short u_short;

#define BUFFER_SIZE 256

static const char *bin_buf_to_text_buf(u_byte *bin_buf, u_short fullness)
{
	static char *text_buf[BUFFER_SIZE * 2];

	for (u_byte *code = bin_buf; code < bin_buf + fullness; ++code)
		snprintf(text_buf + (size_t)(code - bin_buf) * 2, 1, 2, "%02X", *code);

	return (const char*)text_buf;
}

static void bin_to_text(char *in_bin_filename, char *out_text_filename)
{
	FILE *in_file = fopen(in_bin_filename, "r+b");
	if (!in_file) {
		printf("The binary file does not exist!\n");
		exit(ENOENT);
	}

	FILE *out_file = fopen(out_text_filename, "w");
	if (!out_file) {
		printf("Unable to create a text file!\n");
		fclose(in_file);
		exit(ETXTBSY);
	}

	u_byte buffer[BUFFER_SIZE];
	u_short read_u_bytes;
	while ((read_u_bytes = fread(buffer, 1, BUFFER_SIZE, in_file))
		fwrite(bin_buf_to_text_buf(buffer, read_u_bytes), 1, (size_t)read_u_bytes * 2, out_file);

	fclose(in_file);
	fclose(out_file);
}

static void text_to_bin(char *in_text_filename, char *out_bin_filename)
{
}

