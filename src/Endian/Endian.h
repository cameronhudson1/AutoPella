#include <stdio.h>
#include <stdint.h>

void writeLittleEndian32(uint32_t bigEndianInt, FILE *fp);
void writeLittleEndian16(uint16_t bigEndianInt, FILE *fp);
