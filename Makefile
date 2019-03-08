GEN 		= generateWave.c
WC  		= Wav.c
UTILITY	= Endian.c DynamicArrays.c
PRG 		= genWave

CC 			= gcc
CFLAGS	= -Wall -std=c99 -pedantic -DERR_CHECK -g -ggdb -O0


.SILENT:

# make
all:
	echo "Compile all..."
	$(CC) $(CFLAGS) $(WC) $(UTILITY) -o $(PRG) 

test:
	echo "testing tool..."
	./$(PRG)
