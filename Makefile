GEN = generateWave.c
WC  = Wav.c
PRG = genWave

CC 			= gcc
CFLAGS	= -Wall -std=c99 -pedantic 

.SILENT:

# make
all:
	echo "Compile all..."
	$(CC) $(CFLAGS) $(WC) -o $(PRG) 
