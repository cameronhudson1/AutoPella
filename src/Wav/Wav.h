/*
	File: Wav.h
	Name: Cameron Hudson
	Date: 3/7/2019
*/

// Macros for wav format

#define WAV_HEADER_CHUNK_ID "RIFF"
#define BASE_WAV_SIZE 44
#define WAV_RIFF_TYPE "WAVE"
#define WAV_FORMAT_CHUNK_ID "fmt "
#define FORMAT_CHUNK_SIZE 16
#define WAV_FORMAT_PCM 1
#define NUM_CHANNELS 1
#define SAMPLE_SIZE 2
#define WAV_DATA_CHUNK_ID "data"

#define SAMPLE_FREQ 44100


// WavFile Structure
typedef struct{
	// Header Chunk
	char shGroupId[4];
	uint32_t dwFileLength;
	char sRiffType[4];
	
	// Format Chunk
	char sfGroupId[4];
	uint32_t dwChunkSize;
	uint16_t wFormatTag;
	uint16_t wChannel;					// 1 for Mono
	uint32_t dwSamplesPerSec;			// SAMPLE_FREQ
	uint32_t dwAvgBytesPerSec;			// 
	uint16_t wBlockAlign;				//
	uint16_t dwBitsPerSample;			//
	
	// Data Chunk
	char sdGroupId[4];
	uint32_t wChunkSize;
	DArray *sampleData;
	
} WavFile;
