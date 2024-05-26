#include <stdio.h>
#include "EventHall.h"


int InitEventHall(EventHall* eh) {
    if (eh == NULL) {
        return 0; 
    }
   
    printf("Enter max capacity:\n ");
    scanf("%d", &eh->maxCap);

    InItAddress(&eh->hallAddress);

    return 1; 
}

char* getEventHallName(char* name)
{
    char temp[SIZE];
    printf("Enter hall name:\n ");
    myGets2(temp, SIZE);
    name = getDynStr(temp);
    return name;

}

void printEventHall(const EventHall* eh) {
    if (eh == NULL)
    {
        printf("Invalid Event Hall\n");
        return;
    }
    printf("\n\nName: %s\nMax Capacity: %d\n", eh->name, eh->maxCap);
    printf("\nHall Address:");
    printAddress(&(eh->hallAddress));
}

void freeEventHall(EventHall* eh) {
    if (eh != NULL) 
    {
        free(eh->name);
        freeAddress(&(eh->hallAddress));
    }
}

int	loadEventHallFromFile(EventHall* eh, FILE* fp)
{
    char temp[SIZE];
    if (!eh)
        return 0;

   myGets1(temp, SIZE, fp);
   eh->name = getDynStr(temp);

   myGets1(temp,SIZE, fp);
   eh->maxCap = getDynStr(temp);

   myGets1(temp, SIZE, fp);
   eh->hallAddress.city = getDynStr(temp);

   myGets1(temp, SIZE, fp);
   eh->hallAddress.street = getDynStr(temp);
    
    return 1;
}

int	saveEventHallToBinFile(const EventHall* eh, FILE* fp)
{
    if (!writeIntToFile(eh->maxCap, fp, "Error write max cap\n"))
        return 0;

    if (!writeStringToFile(eh->name, fp, "Error write Event type\n"))
        return 0;

    if (!saveAddressToBinFile(&eh->hallAddress, fp, "Error write plane SN\n"))
        return 0;

    return 1;
}

int readEventHallFromBinFile(EventHall* eh, FILE* fp)
{
    if (!eh)
        return 0;
    if (!readIntFromFile(&eh->maxCap, fp, "Error read max capacity from file"))
        FREE_CLOSE_RETURN_0(eh, fp);
    eh->name = readStringFromFile(fp, "Error read eventhall name");
    if (!readAddressFromBinFile(&eh->hallAddress, fp))
        FREE_CLOSE_RETURN_0(eh, fp);
    return 1;
}

int saveEventHallToTxtFile(const EventHall* eh, FILE* fp)
{
    if (!eh)
        return 0;
    fprintf(fp, "%s\n", eh->name);
    fprintf(fp, "%d\n", eh->maxCap);
    if (!saveAddressToTxtFile(&eh->hallAddress, fp))
        return 0;
    return 1;
}

int	readEventHallFromTxtFile(EventHall* eh, FILE* fp)
{
    char temp[SIZE];
    if (!eh)
        return 0;

    myGets1(temp, SIZE, fp);
    eh->name = getDynStr(temp);
    fscanf(fp, "%d", &eh->maxCap);

    return readAddressFromTxtFile(&eh->hallAddress, fp);
}