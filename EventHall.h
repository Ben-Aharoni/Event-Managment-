#pragma once
#include "Address.h"
#include "General.h"

typedef struct
{
	char* name;
	int maxCap;
	Address hallAddress;

}EventHall;

int InitEventHall(EventHall* eh);
void printEventHall(const EventHall* eh);
void freeEventHall(EventHall* eh);
char* getEventHallName(char* Name);
int	loadEventHallFromFile(EventHall* eh, FILE* fp);
int	saveEventHallToBinFile(const EventHall* eh, FILE* fp);
int readEventHallFromBinFile(EventHall* eh, FILE* fp);
int	saveEventHallToTxtFile(const EventHall* eh, FILE* fp);
int readEventHallFromTxtFile(EventHall* eh, FILE* fp);

