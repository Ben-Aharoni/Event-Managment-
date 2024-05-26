#pragma once
#include "Event.h"
#include "Worker.h"
#include "Acountent.h"

#define MAX_CAP 511

typedef enum {
	cost, guestcount, date, eNofSortTypes
} eSortType;

static const char* SortTypeStr[eNofSortTypes]
= { "cost", "guest count", "date" };

typedef struct
{
	Event** eventArr;
	int NOfEvents;
	Worker* WorkersArr;
	int NOfWorkers;
	eSortType sortType;
}EventManager;

int InItManager(EventManager* pManager);
void printEventManager(const EventManager* pManager);
void printAllEventManager(const EventManager* pManager);
void freeManager(EventManager* pManager);
int addEvent(EventManager* pManager, EventHallsOwner* pOwner, Acountent* a);
int addWorker(EventManager* pManager);
int compareByCost(const void* e1, const void* e2);
int compareByGuestCount(const void* e1, const void* e2);
int CompareByDate(const void* e1, const void* e2);
void eventSort(EventManager* pManager);
void findEvent(EventManager* pManager);
void freeWorkerArr(Worker* arr, int size);
void freeEventArr(Event** arr, int size);
void printWorkerArr(const Worker* arr, int size);
void printEventArr(const Event** arr, int size);
eSortType chooseSort();
int	initEventManagerFromBinFile(EventManager* pManager, const char* fileName, const char* compressFile);
int	saveEventManagerToBinFile(const EventManager* pManager, const char* fileName, const char* compressFile);
int	createWorkersArr(EventManager* pManager);
int createEventArr(EventManager* pManager);
int loadEventArrFromFile(EventManager* pManager, FILE* fp);
int	initEventManagerFromTxtFile(EventManager* pManager, const char* fileName);
int	saveEventManagerFromTxtFile(EventManager* pManager, const char* fileName);