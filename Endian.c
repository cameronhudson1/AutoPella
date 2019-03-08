/*
	File: Endian.c
	Name: Cameron Hudson
	Date: 3/7/2019
*/

#include <stdio.h>
#include <stdint.h>

void writeLittleEndian32(uint32_t bigEndianInt, FILE *fp){
	uint32_t b0, b1, b2, b3;

	b0 = (bigEndianInt & 0x000000ff) << 24u;
	b1 = (bigEndianInt & 0x0000ff00) << 8u;
	b2 = (bigEndianInt & 0x00ff0000) >> 8u;
	b3 = (bigEndianInt & 0xff000000) >> 24u;

	uint16_t newInt = b0 | b1 | b2 | b3;
	fwrite(&newInt, 4, 1, fp);
}

void writeLittleEndian16(uint16_t bigEndianInt, FILE *fp){
	uint16_t b0, b1;

	b0 = (bigEndianInt & 0x00ff) << 8u;
	b1 = (bigEndianInt & 0xff00) >> 8u;

	uint16_t newInt = b0 | b1;
	fwrite(&newInt, 2, 1, fp);
}
