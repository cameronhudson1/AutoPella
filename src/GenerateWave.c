#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#include "GenerateWave.h"

int generateWave(DArray * da, uint32_t freq, uint32_t seconds, uint32_t sampleFreq, uint32_t sampleSize){
	// Seconds must be smaller than 97000
	#ifdef ERR_CHECK

	if(seconds > 97000){
		fprintf(stderr, "Dude your audio is over a day long what are you doing\n");
		return 1;
	}

	#endif

	uint32_t samplesToMake = sampleFreq * seconds;
	double angle = (2 * freq * M_PI) / sampleFreq;

	for(int16_t currSample = 0; currSample < samplesToMake; currSample++){
		int16_t sample = pow(2, (sampleSize * 4)) * sin(angle * currSample);
		int res = pushToDArray(da, &sample);
		if(res == -1){
			// Error pushing to DArray
			fprintf(stderr, "Error adding to DArray\n");
			return 1;
		}
	}
	return 0;
}
