#include <stdio.h>
#include <stdlib.h>
#include "EventManager.h"




int InItManager(EventManager* pManager) 
{
    pManager->eventArr = NULL;
    pManager->WorkersArr = NULL;
    pManager->NOfEvents = 0;
    pManager->NOfWorkers = 0;
}

void printEventManager(const EventManager* pManager) 
{
	printf("there are %d Events\n", pManager->NOfEvents);
	printf("\nthere are %d Workers\n\n", pManager->NOfWorkers);
}
void printAllEventManager(const EventManager* pManager)
{
	printf("there are %d Events :\n\n", pManager->NOfEvents);
	printEventArr(pManager->eventArr, pManager->NOfEvents);
	printf("\nthere are %d Workers :\n\n", pManager->NOfWorkers);
	printWorkerArr(pManager->WorkersArr, pManager->NOfWorkers);
}
void freeManager(EventManager* pManager) 
{
	L_free(&pManager->eventArr, freeEventArr);
	L_free(&pManager->WorkersArr, freeWorkerArr);
}

int addEvent(EventManager* pManager, EventHallsOwner* pOwner, Acountent* a) 
{
    if (pManager->NOfEvents == MAX_CAP)
    {
        printf("cant add more events max capacity reached\n ");
    } 
    Invoice* i = (Invoice*)malloc(sizeof(Invoice)); 
	if (!i)
		return 0;
	InItInvoicName(i);
    pManager->eventArr = (Event**)realloc(pManager->eventArr, (pManager->NOfEvents + 1) * sizeof(Event*));
    if (pManager->eventArr == NULL)
    {
        return 0;
    }
    Event* e = (Event*)malloc(sizeof(Event));
    if (e == NULL)
    {
        return 0;
    }
    InItEvent(e, pOwner);
    i->event = *e;
    addInvoice(a, i);
    pManager->eventArr[pManager->NOfEvents++] = e;
    return 1;
}


int addWorker(EventManager* pManager) 
{
    if (pManager->NOfWorkers == MAX_CAP) 
    {
        printf("cant add more workers max capacity reached\n ");
    }
    pManager->WorkersArr = (Worker*)realloc(pManager->WorkersArr, (pManager->NOfWorkers + 1) * sizeof(Worker));
    if (!pManager->WorkersArr)
        return 0;
    InItWorker(&pManager->WorkersArr[pManager->NOfWorkers]);
    pManager->NOfWorkers++;
    return 1;
}

int compareByCost(const void* e1, const void* e2) 
{
    const Event* p1 = *(const Event**)e1;
    const Event* p2 = *(const Event**)e2;

    return p1->cost - p2->cost;
}

int compareByGuestCount(const void* e1, const void* e2) 
{
    const Event* p1 = *(const Event**)e1;
    const Event* p2 = *(const Event**)e2;

    return p1->guestCount - p2->guestCount;
}

int CompareByDate(const void* e1, const void* e2) 
{

    const Event* p1 = *(const Event**)e1;
    const Event* p2 = *(const Event**)e2;

    return compareDate(&p1->eventDate, &p2->eventDate);
}

void eventSort(EventManager* pManager) 
{

    pManager->sortType = chooseSort();
    switch ((int)pManager->sortType)
    {
    case 1:
        qsort(pManager->eventArr, pManager->NOfEvents, sizeof(Event*), compareByCost);
        break;

    case 2:
        qsort(pManager->eventArr, pManager->NOfEvents, sizeof(Event*), compareByGuestCount);
        break;

    case 3:
        qsort(pManager->eventArr, pManager->NOfEvents, sizeof(Event*), compareByDate);
        break;

    default:
        break;
    }
}

void findEvent(EventManager* pManager) 
{

	Event* e = (Event*)malloc(sizeof(Event));
	if (!e)
		return;
    int (*CompFunc)(const void*, const void*);
	int op = pManager->sortType;
	switch (op)
	{
	case 1:
		printf("enter the event cost : \n");
		scanf("%f" , &e->cost);
        CompFunc = compareByCost;
        break;
	case 2:
		printf("enter the event guest count : \n");
		scanf("%d", &e->guestCount);
        CompFunc = compareByGuestCount;
        break;
	case 3:
		getCorrectDate(&e->eventDate);
        CompFunc = compareByDate;
        break;
	default:
		printf("\n\nThe search cannot be performed, array not sorted\n");
        return;
	}
		Event** E = (Event**)bsearch(&e, pManager->eventArr, pManager->NOfEvents, sizeof(Event*), CompFunc);
		if (!E)
		{
			printf("\nEvent was not found\n\n");
		}
		else
		{
			printf("Event found,\n ");
			printEvent(*E);
		}
	    free(e);
}

void freeWorkerArr(Worker* arr, int size) 
{
	generalArrayFunction(arr, size, sizeof(Worker), free);
}

void freeEventArr(Event** arr, int size) 
{
	generalArrayFunction(arr, size, sizeof(Event*), freeEventPtr);
}

void printWorkerArr(const Worker* arr, int size) 
{
	generalArrayFunction(arr, size, sizeof(Worker), printWorker);
}

void printEventArr(const Event** arr, int size) 
{

	generalArrayFunction(arr, size, sizeof(Event*), printEventPtr);
}


eSortType chooseSort()
{
    int option;
    printf("\n\n");
    printf("Base on what field do you want to sort?\n");
    do {
        for (int i = 0; i < eNofSortTypes; i++)
            printf("Enter %d for %s\n", (i + 1), SortTypeStr[i]);
        scanf("%d", &option);
        printf("\n\n");
    } while (option <= 0 || option > eNofSortTypes);
    return (eSortType)option;
}
int	saveEventManagerFromTxtFile(EventManager* pManager, const char* fileName)
{
	FILE* fp;
	fp = fopen(fileName, "w");
	if (!fp)
	{
		printf("Error open event manager file\n");
		return 0;
	}
	fprintf(fp, "%d\n", pManager->NOfEvents);
	for (int i = 0; i < pManager->NOfEvents; i++)
	{
		if (!saveEventToTxtFile(pManager->eventArr[i], fp))
			return 0;
	}
	fprintf(fp, "%d\n", pManager->NOfWorkers);
	for (int i = 0; i < pManager->NOfWorkers; i++)
	{
		if (!saveWorkerToTxtFile(&pManager->WorkersArr[i], fp))
			return 0;
	}
	fclose(fp);
	return 1;
}

int	initEventManagerFromTxtFile(EventManager* pManager, const char* fileName)
{
	FILE* fp;
	fp = fopen(fileName, "r");
	if (!fp)
	{
		printf("Error open event manager file\n");
		return 0;
	}
	pManager->eventArr = NULL;
	fscanf(fp, "%d", &pManager->NOfEvents);
	if (!createEventArr(pManager))
		return 0;
	for (int i = 0; i < pManager->NOfEvents; i++)
	{
		if (!loadEventFromTxtFile(pManager->eventArr[i], fp))
			return 0;
	}
	fscanf(fp, "%d", &pManager->NOfWorkers);
	if (!createWorkersArr(pManager))
		return 0;
	for (int i = 0; i < pManager->NOfWorkers; i++)
	{
		if (!loadWorkerFromTxtFile(&pManager->WorkersArr[i], fp))
			return 0;
	}
	fclose(fp);
	return 1;
}

int	initEventManagerFromBinFile(EventManager* pManager, const char* fileName, const char* compressFile)
{
	FILE* fp;
	fp = fopen(fileName, "rb");
	if (!fp)
	{
		printf("Error open event manager file\n");
		return 0;
	}
	if (!readIntFromFile(&pManager->NOfWorkers, fp, "Error reading Events count\n"))
	{
		CLOSE_RETURN_0(fp);
	}

	if (!createWorkersArr(pManager))
	{
		printf("Alocation error\n");
		CLOSE_RETURN_0(fp);
	}

	FILE* fcb;
	fcb = fopen(compressFile, "rb");
	if (!fcb) {
		printf("Error open Worker file to read\n");
		return 0;
	}

	for (int i = 0; i < pManager->NOfWorkers; i++)
	{
		if (!loadWorkerArrFromFile(&pManager->WorkersArr[i], fcb))
		{
			printf("unable to load from file");
			return 0;
		}
	}
	fclose(fcb);
	if (!readIntFromFile(&pManager->NOfEvents, fp, "Error reading Events count \n"))
	{
		FREE_CLOSE_RETURN_0(pManager->WorkersArr, fp);
	}

	if (!createEventArr(pManager))
	{
		printf("Alocation error\n");
		FREE_CLOSE_RETURN_0(pManager->WorkersArr, fp);
	}

	if (!loadEventArrFromFile(pManager, fp))
	{
		free(pManager->eventArr);
		FREE_CLOSE_RETURN_0(pManager->WorkersArr, fp);
	}
	fclose(fp);
	return 1;
}

int	saveEventManagerToBinFile(const EventManager* pManager, const char* fileName, const char* compressFile)
{
	FILE* fp;
	fp = fopen(fileName, "wb");
	if (!fp) {
		printf("Error open Event file to write\n");
		return 0;
	}
	if (!writeIntToFile(pManager->NOfWorkers, fp, "Error write Worker count\n"))
	{
		CLOSE_RETURN_0(fp);
	}

	FILE* fcb;
	fcb = fopen(compressFile, "wb");
	if (!fcb) {
		printf("Error open Worker file to write\n");
		return 0;
	}
	for (int i = 0; i < pManager->NOfWorkers; i++)
	{
		if (!saveWorkerToCompressedFile(&pManager->WorkersArr[i], fcb))
		{
			printf("unable to save to file");
			return 0;
		}
	}
	fclose(fcb);

	if (!writeIntToFile(pManager->NOfEvents, fp, "Error write Event count\n"))
	{
		CLOSE_RETURN_0(fp);
	}

	for (int i = 0; i < pManager->NOfEvents; i++)
	{
		if (!saveEventToBinFile(pManager->eventArr[i], fp))
		{
			CLOSE_RETURN_0(fp);
		}
	}
	fclose(fp);
	return 1;
}


int	createWorkersArr(EventManager* pManager)
{
	pManager->WorkersArr = (Worker*)malloc(pManager->NOfWorkers * sizeof(Worker));
	if (!pManager->WorkersArr)
	{
		printf("Alocation error\n");
		return 0;
	}
	return 1;
}

int createEventArr(EventManager* pManager)
{
	if (pManager->NOfEvents > 0)
	{
		pManager->eventArr = (Event**)malloc(pManager->NOfEvents * sizeof(Event*));
		if (!pManager->eventArr)
		{
			printf("Alocation error\n");
			return 0;
		}
	}
	else
		pManager->eventArr = NULL;

	for (int i = 0; i < pManager->NOfEvents; i++)
	{
		pManager->eventArr[i] = (Event*)calloc(1, sizeof(Event));
		if (!pManager->eventArr[i])
		{
			printf("Alocation error\n");
			return 0;
		}
	}
	return 1;
}

int loadEventArrFromFile(EventManager* pManager, FILE* fp)
{

	for (int i = 0; i < pManager->NOfEvents; i++)
	{
		if (!loadEventFromBinFile(pManager->eventArr[i], fp))
		{
			return 0;
		}
	}
	return 1;
}

