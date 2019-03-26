/*
	File: Wav.C
	Name: Cameron Hudson
	Date: 3/7/2016
*/

#include "AutoPella.h"

WavFile* createEmtpyWavFile(){
	WavFile * wav = malloc(sizeof(WavFile));
	
	wav->dwFileLength = BASE_WAV_SIZE; // INCREMENT AS DATA IS APPENDED

	wav->dwChunkSize = FORMAT_CHUNK_SIZE;
	wav->wFormatTag = WAV_FORMAT_PCM;
	wav->wChannel = NUM_CHANNELS;
	wav->dwSamplesPerSec = SAMPLE_FREQ;
	wav->dwBitsPerSample = SAMPLE_SIZE;
	wav->wBlockAlign = (SAMPLE_SIZE / 8) * NUM_CHANNELS;
	wav->dwAvgBytesPerSec = wav->wBlockAlign * SAMPLE_FREQ;

	wav->wChunkSize = 0;
	wav->sampleData = malloc(sizeof(DArray));

	return wav; 
}

WavFile* createWavFile(DArray *dptr){
	WavFile * wav = malloc(sizeof(WavFile));
	
	wav->dwFileLength = 
		BASE_WAV_SIZE + (dptr->EntriesUsed * SAMPLE_SIZE); // We know the value to add

	wav->dwChunkSize = FORMAT_CHUNK_SIZE;
	wav->wFormatTag = WAV_FORMAT_PCM;
	wav->wChannel = NUM_CHANNELS;
	wav->dwSamplesPerSec = SAMPLE_FREQ;
	wav->dwBitsPerSample = SAMPLE_SIZE;
	wav->wBlockAlign = (SAMPLE_SIZE / 8) * NUM_CHANNELS;
	wav->dwAvgBytesPerSec = wav->wBlockAlign * SAMPLE_FREQ;

	wav->wChunkSize = dptr->EntriesUsed;
	wav->sampleData = dptr;

	return wav;
} 

void freeWavFile(WavFile* wav){
	destroyDArray(wav->sampleData);
	free(wav);
	wav = NULL;
}

int generateWave(DArray * da, uint32_t freq, uint32_t seconds){
	// Seconds must be smaller than 97000
	#ifdef ERR_CHECK

	if(seconds > 97000){
		fprintf(stderr, "Dude your audio is over a day long what are you doing\n");
		return 1;
	}

	#endif

	uint32_t samplesToMake = SAMPLE_FREQ * seconds;
	double angle = (2 * freq * M_PI) / SAMPLE_FREQ;

	for(uint32_t currSample = 0; currSample < samplesToMake; currSample++){
		uint32_t sample = (1u << SAMPLE_SIZE) * sin(angle * currSample);
		int res = pushToDArray(da, &sample);
		if(res == -1){
			// Error pushing to DArray
			fprintf(stderr, "Error adding to DArray\n");
			return 1;
		}
	}
	return 0;
}

int saveWavFile(WavFile* wav, char* filename){
	FILE *fp = fopen(filename, "wb");
	if(!fp){
		// Return nonzero on failure to create file 
		return 1;	
	}

	// HEADER CHUNK WRITE
	fwrite(WAV_HEADER_CHUNK_ID, 1, 4, fp); 					// Write shGroupId
	writeLittleEndian32(wav->dwFileLength, fp); 			// Write dwFileLength
	fwrite(WAV_RIFF_TYPE, 1, 4, fp);						// Write sRiffType
	
	// FORMAT CHUNK WRITE
	fwrite(WAV_FORMAT_CHUNK_ID, 1, 4, fp);					// Write sfGroupId

	writeLittleEndian32(wav->dwChunkSize, fp);				// Write dwChunkSize
	writeLittleEndian16(wav->wFormatTag, fp);				// Write wFormatTag
	writeLittleEndian16(wav->wChannel, fp);					// Write wChannel
	writeLittleEndian32(wav->dwSamplesPerSec, fp);			// Write dwSamplesPerSec
	writeLittleEndian32(wav->dwAvgBytesPerSec, fp);			// Write dwAvgBytesPerSec
	writeLittleEndian16(wav->wBlockAlign, fp);				// Write wBlockAlign
	writeLittleEndian32(wav->dwBitsPerSample, fp);			// Write dwBytesPerSample

	// DATA CHUNK WRITE
	fwrite(WAV_DATA_CHUNK_ID, 1, 4, fp);					// Write sdGroupId
	writeLittleEndian32(wav->wChunkSize, fp);				// Write wChunkSize

	for(int i = 0; i < (wav->sampleData->EntriesUsed); i++){
		writeLittleEndian32((wav->sampleData->Payload)[i], fp);
	}
	
	fclose(fp);
	return 0;
}

void testGenWav(){
	// TODO WRITE TEST FOR DARRAY
	DArray *test = malloc(sizeof(DArray));
	createDArray(test, 100);
	generateWave(test, A4, 5);

	WavFile *wav = createWavFile(test);

	for(int i = 0; i < test->Capacity; i++){
		uint32_t val = test->Payload[i];
		printf("%d ", val);
	}
	
	printf("\n");

	saveWavFile(wav, "testwav.wav");

	destroyDArray(test);
}

int main(){
	testGenWav();
	printf("Created and freed new WavFile struct!\n");
}
