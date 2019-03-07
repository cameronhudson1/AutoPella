/*
	File: Wav.h
	Name: Cameron Hudson
	Date: 3/7/2019
*/

// Macros for wav format

#define WAV_HEADER_CHUNK_ID "RIFF"
#define WAV_RIFF_TYPE "WAVE"
#define WAV_FORMAT_CHUNK_ID "fmt "
#define WAV_FORMAT_PCM 1
#define SAMPLE_SIZE 32
#define WAV_DATA_CHUNK_ID "data"


// WavFile Structure
typedef struct{
	// Header Chunk
	int8_t shGroupId[4];
	uint32_t dwFileLength;
	int8_t sRiffType[4];
	
	// Format Chunk
	int8_t sfGroupId[4];
	uint32_t dwChunkSize;
	uint16_t wFormatTag;
	uint16_t wChannel;
	uint32_t dwSamplesPerSec;
	uint32_t dwAvgBytesPerSec;
	uint16_t wBlockAlign;
	uint32_t dwBitsPerSample;
	
	// Data Chunk
	int8_t sdGroupId[4];
	uint32_t wChunkSize;
	int32_t *sampleData;
	
} WavFile;
