/**
 ** DynamicArrays.c  - private implementations - student file
 **
 ** Implementation of a (constant growth) Dynamic Array data type             
 **   Modify struc Data in DynamicArrays.h for payload according application  
 **   To change growth policy modify PushToDArray as needed                   
 **                                                                           
 ** Written by: Greg Semeraro,Ph.D.                                           
 ** Modified: Dr. Juan C. Cockburn (jcck@ieee.org)                            
 ** Revised: 02/01/2014 JCCK     
 **          10/02/2015 R Repka 
 **          03/03/2017 R Repka
 **          07/21/2017 R.Repka - added class errors include file
 **          09/25/2017 R.Repka - Minor psuedo code correction
 **/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "DynamicArrays.h"

/***************************************************************************
 CreateDArray -- Allocates memory and initializes DArray state             
        void CreateDArray(DArray *DArrayHead, unsigned int InitialSize)
 Where:
    DArray *DArrayHead       - Pointer to a storage block which holds the
                               data structure entry 
    unsigned int InitialSize - The initial data block size, could be 0
    returns: void            - nothing is returned.
    errors:                  - This routine will print an error message to 
                               stderror and exit with an error code
 **************************************************************************/
void createDArray(DArray *DArrayHead, uint32_t InitialSize) {
	if(DArrayHead == NULL){
		printf("sampleDataHead doesn't exist.  Exiting...\n");
		return;
	}	
	DArrayHead->EntriesUsed = 0;
	DArrayHead->Capacity = InitialSize;
	if((DArrayHead->Payload = malloc(InitialSize*sizeof(int16_t))) == NULL){
		fprintf(stderr, 
				"Memory allocation for sample data failed!  Aborting...\n");
		return;
	}
} /* CreateDArray() */


/***************************************************************************
  PushToDArray -- Adds data at the end of the dynamic array and updates its 
                  state in the array header.  If full, reallocates memory 
                  space according to growth policy                          
        unsigned int PushToDArray(DArray *DArrayHead, Data *PayloadPtr)     
  Where:
    DArray *DArrayHead      - Pointer to a storage block which holds the
                              data structure entry 
    Data * PayloadPtr       - 
    returns: unsigned int   - The index of the last element inserted
    errors:                 - This routine will print an error message to 
                              stderror and exit with an error code 
 **************************************************************************/
int pushToDArray(DArray *DArrayHead, int16_t *PayloadPtr)
{
	if(DArrayHead->EntriesUsed == DArrayHead->Capacity){
		//Must be extended
		DArrayHead->Capacity += GROWTH_AMOUNT;
		DArrayHead->Payload = (int16_t *)realloc(DArrayHead->Payload, 
					(DArrayHead->Capacity)*sizeof(int16_t));
		if(DArrayHead->Payload == NULL){
			fprintf(stderr, 
				"Memory reallocation of dynamic array failed!  Aborting...\n");
			return -1;
		}
	}
	DArrayHead->Payload[DArrayHead->EntriesUsed] = *PayloadPtr;
	DArrayHead->EntriesUsed++;
	return DArrayHead->EntriesUsed;
} /* PushToDArray() */


/*************************************************************************
 DestroyDArray -- Returns the memory back to the heap and updates the   
                  state in the array header      
        void DestroyDArray(DArray *DArrayHead)
  Where:
    DArray *DArrayHead  - Pointer to a storage block which holds the
                          data structure entry 
    returns: void       - nothing is returned.
    errors:             - No errors are reported
*************************************************************************/
void destroyDArray(DArray *DArrayHead)
{
	DArrayHead->Capacity = 0;
	DArrayHead->EntriesUsed = 0;
	free(DArrayHead->Payload);
	DArrayHead = NULL;
} /* DestroyDArray() */
