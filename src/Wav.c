/*
	File: Wav.C
	Name: Cameron Hudson
	Date: 3/7/2016
*/

#include <math.h>
#include "Wav.h"

WavFile* createWavFile(DArray *dptr){
	WavFile * wav = malloc(sizeof(WavFile));
	wav->dwFileLength = 
		BASE_WAV_SIZE + (dptr->EntriesUsed * SAMPLE_SIZE); // We know the value to add
	wav->dwChunkSize = FORMAT_CHUNK_SIZE;
	wav->wFormatTag = WAV_FORMAT_PCM;
	wav->wChannel = NUM_CHANNELS;
	wav->dwSamplesPerSec = SAMPLE_FREQ;
	wav->dwBitsPerSample = SAMPLE_SIZE * 8;
	wav->wBlockAlign = SAMPLE_SIZE * NUM_CHANNELS;
	wav->dwAvgBytesPerSec = wav->wBlockAlign * SAMPLE_FREQ * NUM_CHANNELS;

	wav->wChunkSize = (dptr->EntriesUsed) * SAMPLE_SIZE;
	wav->sampleData = dptr;

	return wav;
} 

void freeWavFile(WavFile* wav){
	free(wav);
	wav = NULL;
}

int saveWavFile(WavFile* wav, char* filename){
	FILE *fp = fopen(filename, "wb");
	if(!fp){
		// Return nonzero on failure to create file 
		return 1;	
	}

	// HEADER CHUNK WRITE
	fwrite(WAV_HEADER_CHUNK_ID, 1, 4, fp); 					// Write shGroupId
	fwrite(&wav->dwFileLength, 4, 1, fp); 			// Write dwFileLength
	fwrite(WAV_RIFF_TYPE, 1, 4, fp);						// Write sRiffType
	
	// FORMAT CHUNK WRITE
	fwrite(WAV_FORMAT_CHUNK_ID, 1, 4, fp);					// Write sfGroupId
	fwrite(&wav->dwChunkSize, 4, 1, fp);
	fwrite(&wav->wFormatTag, 2, 1, fp);				// Write wFormatTag
	fwrite(&wav->wChannel, 2, 1, fp);					// Write wChannel
	fwrite(&wav->dwSamplesPerSec, 4, 1, fp);			// Write dwSamplesPerSec
	fwrite(&wav->dwAvgBytesPerSec, 4, 1, fp);			// Write dwAvgBytesPerSec
	fwrite(&wav->wBlockAlign, 2, 1, fp);				// Write wBlockAlign
	fwrite(&wav->dwBitsPerSample, 2, 1, fp);			// Write dwBitsPerSample

	// DATA CHUNK WRITE
	fwrite(WAV_DATA_CHUNK_ID, 1, 4, fp);					// Write sdGroupId
	fwrite(&wav->wChunkSize, 4, 1, fp);				// Write wChunkSize

	for(int i = 0; i < (wav->sampleData->EntriesUsed); i++){
		fwrite(&((wav->sampleData->Payload)[i]), SAMPLE_SIZE, 1, fp);
	}
	
	fclose(fp);
	return 0;
}

void printWav(WavFile * wav){
	printf("shGroupId: %s\n", WAV_HEADER_CHUNK_ID);
	printf("dwFileLength: %u\n", wav->dwFileLength);
	printf("sRiffType: %s\n", WAV_RIFF_TYPE);
	printf("\n");

	printf("sfGroupId: %s\n", WAV_FORMAT_CHUNK_ID);
	printf("dwChunkSize: %u\n", wav->dwChunkSize);
	printf("wFormatTag: %hu\n", wav->wFormatTag);
	printf("wChannel: %hu\n", wav->wChannel);
	printf("dwSamplesPerSec: %u\n", wav->dwSamplesPerSec);
	printf("dwAvgBytesPerSec: %u\n", wav->dwAvgBytesPerSec);
	printf("wBlockAlign: %hu\n", wav->wBlockAlign);
	printf("dwBitsPerSample: %hu\n", wav->dwBitsPerSample);
	printf("\n");

	printf("sdGroupId: %s\n", WAV_DATA_CHUNK_ID);
	printf("wChunkSize: %u\n", wav->wChunkSize);
	printf("\n");

	// Print sampleData
	for(int i = 0; i < wav->sampleData->EntriesUsed; i++){
		uint16_t val = wav->sampleData->Payload[i];
		printf("%hd\n", val);
	}
	printf("\n");
}
