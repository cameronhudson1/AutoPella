CC 		= gcc
CFLAGS	= -Wall -std=c99 -pedantic -DERR_CHECK -g -ggdb -O0

MAIN 	= src/AutoPella.c
GEN 	= src/generateWave.c
UTILITY	= src/Endian.c src/DynamicArrays.c src/Wav.c

PRG 	= genWave

.SILENT:

# make
all:
	echo "Compile all..."
	$(CC) $(CFLAGS) $(UTILITY) $(GEN) $(MAIN) -o $(PRG) 

test:
	echo "testing tool..."
	./$(PRG)
