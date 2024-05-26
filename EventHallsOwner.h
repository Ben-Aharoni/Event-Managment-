#pragma once
#include "List.h"
#include "EventHall.h"
#include "file.h"

typedef struct
{
	char* name;
	LIST EventHalls;

}EventHallsOwner;

int inItOwner(EventHallsOwner* pOwner);
int InItEventHallsOwnerFromTxtFile(EventHallsOwner* pOwner, const char* fileName);
int InItEventHallsOwnerFromBinFile(EventHallsOwner* pOwner, const char* fileName);
void printEventHallsOwner(const EventHallsOwner* pOwner);
void printEventHallsOwnerDetails(const EventHallsOwner* pOwner);
int AddEventHalls(EventHallsOwner* pOwner);
void freeEventHallsOwner(EventHallsOwner* pOwner);
int InItEventHall(EventHall* pEvent, EventHallsOwner* pOwner);
const EventHall* findEventHallByName(const EventHallsOwner* pOwner, char* name);
int checkUniqueName(char* name, const EventHallsOwner* pOwner);
int compareByName(const void* n1, const void* n2);
int saveEventHallToTxtFile(EventHall* eh, FILE* fp);
void insertToCode(LIST* pList, const EventHall* eh);
int	saveEventHallsOwnerToTxtFile(const EventHallsOwner* pOwner, const char* fileName);
int	saveEventHallsOwnerToBinFile(const EventHallsOwner* pOwner, const char* fileName);
const EventHall* findEventHallByName(const EventHallsOwner* pOwner, char* name);
void printEventHallsByRegion(const EventHallsOwner* pOwner);
void InItEventHallsOwner(EventHallsOwner* pOwner);