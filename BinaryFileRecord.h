// Jiwon Topper
// jxt171830@utdallas.edu
// CS3377.002

#ifndef BinaryFileHeader_H
#define BinaryFileHeader_H

#include <stdint.h>

//BinaryFileRecord class definition

const int maxRecordStringLength = 25;

class BinaryFileRecord
{
	public:
		uint8_t strLength;
		char stringBuffer[maxRecordStringLength];
};

//Binary File header definition
class BinaryFileHeader
{
	public:
		uint32_t magicNumber;	//should be 0xFEEDFACE
		uint32_t versionNumber;
		uint64_t numRecords;
};

#endif
