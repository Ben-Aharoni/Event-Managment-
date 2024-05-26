#pragma once
#include "General.h"
#include "file.h"

typedef enum {
	center, north, south, NOfRegions
} eRegionType;

static const char* RegionTypeStr[NOfRegions]
= { "center", "north", "south" };

typedef struct
{
	eRegionType type;
	char* city;
	char* street;
}Address;


int InItAddress(Address* ad);
void printAddress(const Address* ad);
void freeAddress(Address* ad);
eRegionType getRegionType();
const char* GetRegionTypeStr(int type);
int readAddressFromBinFile(Address* ad, FILE* fp);
int	saveAddressToBinFile(const Address* ad, FILE* fp);
int readAddressFromTxtFile(Address* ad, FILE* fp);
int	saveAddressToTxtFile(const Address* ad, FILE* fp);