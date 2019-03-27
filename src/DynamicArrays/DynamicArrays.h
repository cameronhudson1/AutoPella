/**************************************************************************
* Dynamic Arrays Module  - public interface
*
* data types: Data - struct with data to be stored
*             DArray - structure for Dynamic Array Header
*
* functions: CreateDArray, PushToDArray, DestroyDArray
*
* Author: Greg Semeraro, Juan C. Cockburn
* Revised: JCCK 2/3/2015
* 10/02/2015    R Repka 
* 03/13/2017    R. Repka    Added #define to support multiple labels
* 12/24/2017    R. Repka    simplified Darray structure
**************************************************************************/
#ifndef _DYNAMIC_ARRAYS_H_
#define _DYNAMIC_ARRAYS_H_

#include <stdint.h>

/* Growth Policy : Constant Size */
#define GROWTH_AMOUNT (100) 
#define MAX_STR_LEN   (256) 

/**************************************************************************
* DArray - Dynamic Array Header structure to keep track of its "state" 
*          The "state" of the Dynamic Array is: Capacity and EntriesUsed
**************************************************************************/
typedef struct {
   uint32_t Capacity;    /* Max Number of elements array can hold */
   uint32_t EntriesUsed; /* Number of array elements "used"       */
   int16_t *Payload;   /* Pointer to array that actually holds the data  */
  } DArray;

/***************************************************************************
 function prototypes to create, add and destroy data arrays
 **************************************************************************/
void createDArray( DArray *DArrayPtr, uint32_t InitialSize );
int pushToDArray( DArray *DArrayPtr, int16_t *PayloadPtr );
void destroyDArray(DArray *DArrayPtr);

#endif /* _DYNAMIC_ARRAYS_H_ */
