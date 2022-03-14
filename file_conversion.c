#include "file_conversion.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

typedef unsigned char u_byte;
typedef unsigned short u_short;

#define BUFFER_SIZE 256

const char *bin_buf_to_text_buf(u_byte *bin_buf, u_short fullness)
{
	static char text_buf[BUFFER_SIZE * 2];

	for (u_byte *code = bin_buf; code < bin_buf + fullness; ++code)
		snprintf(text_buf + (size_t)(code - bin_buf) * 2, 2, "%02X", *code);

	return (const char*)text_buf;
}

void bin_to_text(char *in_bin_filename, char *out_text_filename)
{
	FILE *in_file = fopen(in_bin_filename, "rb");
	if (!in_file) {
		printf("The binary file does not exist!\n");
		exit(ENOENT);
	}

	FILE *out_file = fopen(out_text_filename, "wb");
	if (!out_file) {
		printf("Unable to create a text file!\n");
		fclose(in_file);
		exit(ETXTBSY);
	}

	u_byte buffer[BUFFER_SIZE];
	u_short read_u_bytes;
	while (read_u_bytes = fread(buffer, 1, BUFFER_SIZE, in_file))
		fwrite(bin_buf_to_text_buf(buffer, read_u_bytes), 1, (size_t)read_u_bytes * 2, out_file);

	fclose(in_file);
	fclose(out_file);
}

u_byte symbol_to_u_byte(char symbol)
{
	switch (symbol) {
	case '0':
		return 0;
	case '1':
		return 1;
	case '2':
		return 2;
	case '3':
		return 3;
	case '4':
		return 4;
	case '5':
		return 5;
	case '6':
		return 6;
	case '7':
		return 7;
	case '8':
		return 8;
	case '9':
		return 9;
	case 'A':
		return 10;
	case 'B':
		return 11;
	case 'C':
		return 12;
	case 'D':
		return 13;
	case 'E':
		return 14;
	default:
		return 15;
	}
}

const u_byte *text_buf_to_bin_buf(char *text_buf, u_short fullness)
{
	static u_byte bin_buf[BUFFER_SIZE / 2];

	for (char *symbol = text_buf; symbol < text_buf + fullness; symbol += 2) {
		bin_buf[(symbol - text_buf) / 2] = ((symbol_to_u_byte(*symbol) << 4) & 0xF0);
		bin_buf[(symbol - text_buf) / 2] += symbol_to_u_byte(*(symbol + 1));
	}

	return bin_buf;
}

void text_to_bin(char *in_text_filename, char *out_bin_filename)
{
	FILE *in_file = fopen(in_text_filename, "rb");
	if (!in_file) {
		printf("The binary file does not exist!\n");
		exit(ENOENT);
	}

	FILE *out_file = fopen(out_bin_filename, "wb");
	if (!out_file) {
		printf("Unable to create a text file!\n");
		fclose(in_file);
		exit(ETXTBSY);
	}

	u_byte buffer[BUFFER_SIZE];
	u_short read_u_bytes;
	while (read_u_bytes = fread(buffer, 1, BUFFER_SIZE, in_file))
		fwrite(text_buf_to_bin_buf(buffer, read_u_bytes), 1, (size_t)read_u_bytes / 2, out_file);

	fclose(in_file);
	fclose(out_file);
}

