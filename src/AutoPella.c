#include "AutoPella.h"

void testGenWav(){
	// TODO WRITE TEST FOR DARRAY
	DArray *test = malloc(sizeof(DArray));
	createDArray(test, 100);
	generateWave(test, A4, 1, SAMPLE_FREQ, SAMPLE_SIZE);

	WavFile *wav = createWavFile(test);

	//printWav(wav);

	saveWavFile(wav, "testwav.wav");

	destroyDArray(test);
	freeWavFile(wav);
}

int main(){
	testGenWav();
}
