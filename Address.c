#include <stdio.h>
#include "Address.h"


int InItAddress(Address* ad) 
{
	if (ad == NULL) {
		return 0; 
	}
	ad->type = getRegionType();

	char city[SIZE]; 
	printf("Enter City: ");
	myGets2(city, SIZE);
	ad->city = getDynStr(city);
	char street[SIZE]; 
	printf("Enter Street: ");
	myGets2(street, SIZE);
	ad->street = getDynStr(street);
	return 1;
}

void printAddress(const Address* ad)
{
	if (ad == NULL)
		return;
	printf("\nAddress:\nRegion - %s , city - %s , street - %s", RegionTypeStr[ad->type], ad->city, ad->street);
}

void freeAddress(Address* ad) 
{
	if (ad == NULL) {
		return;
	}

	free(ad->city);
	free(ad->street);
	free(ad);
}
eRegionType getRegionType() 
{

	int option;
	printf("\n\n");
	do {
		printf("Please enter one of the following types\n");
		for (int i = 0; i < NOfRegions; i++)
			printf("%d for %s\n", i, RegionTypeStr[i]);
		scanf("%d", &option);
	} while (option < 0 || option >= NOfRegions);
	getchar();
	return (eRegionType)option;
}

const char* GetRegionTypeStr(int type)
{
	if (type < 0 || type >= NOfRegions)
		return NULL;
	return RegionTypeStr[type];
}

int	saveAddressToBinFile(const Address* ad, FILE* fp)
{

	if (!writeStringToFile(ad->city, fp, "Error write city\n"))
		return 0;

	if (!writeStringToFile(ad->street, fp, "Error write street\n"))
		return 0;

	if (!writeIntToFile((int)ad->type, fp, "Error write type\n"))
		return 0;

	return 1;
}

int  readAddressFromBinFile(Address* ad, FILE* fp)
{
	ad->city = readStringFromFile(fp, "Error reading eventhall city\n");

	ad->street = readStringFromFile(fp, "Error reading eventhall street\n");

	if (!readIntFromFile(&(int)ad->type, fp, "Error reading eventhall type\n"))
		return 0;
}

int readAddressFromTxtFile(Address* ad, FILE* fp)
{
	char temp[SIZE];
	if (!ad)
		return 0;
	myGets1(temp, SIZE, fp);
	ad->city = getDynStr(temp);
	myGets1(temp, SIZE, fp);
	ad->street = getDynStr(temp);
	fscanf(fp, "%d", &(int)ad->type);
	return 1;
	
}
int	saveAddressToTxtFile(const Address* ad, FILE* fp)
{
	if (!ad)
		return 0;
	fprintf(fp, "%s\n", ad->city);
	fprintf(fp, "%s\n", ad->street);
	fprintf(fp, "%d\n", (int)ad->type);
	return 1;
}