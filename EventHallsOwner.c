#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "EventHallsOwner.h"

void InItEventHallsOwner(EventHallsOwner* pOwner)
{
	L_init(&pOwner->EventHalls);
}
int InItEventHallsOwnerFromBinFile(EventHallsOwner* pOwner, const char* fileName)
{
	FILE* fp;

	fp = fopen(fileName, "rb");
	if (!fp)
	{
		printf("Error open owner file\n");
		return 0;
	}
	L_init(&pOwner->EventHalls);
	int count = 0;
	pOwner->name = readStringFromFile(fp, "Error reading owner name \n");
	if (!readIntFromFile(&count, fp, "Error reading Eventhalls count\n"))
	{
		CLOSE_RETURN_0(fp);
	}
	EventHall* eh;
	for (int i = 0; i < count; i++)
	{
		eh = (EventHall*)calloc(1, sizeof(EventHall));
		if (!eh)
			break;
		if (!readEventHallFromBinFile(eh, fp))
		{
			printf("Error loading Hall from file\n");
			CLOSE_RETURN_0(fp);
		}
		insertToCode(&pOwner->EventHalls, eh);
	}

	fclose(fp);
	return 1;
}
int inItOwner(EventHallsOwner* pOwner)
{
	if (L_init(&pOwner->EventHalls) == False)
		return 0;
	printf("Enter the event owner name\n");
	char temp[SIZE];
	myGets2(temp, SIZE);
	pOwner->name = getDynStr(temp);
	return 1;
}


int InItEventHallsOwnerFromTxtFile(EventHallsOwner* pOwner , const char* fileName) 
{
	FILE* fp;
	char temp[SIZE];
	fp = fopen(fileName, "r");
	if (!fp)
	{
		printf("Error open eventHallOwner manager file\n");
		return 0;
	}
	L_init(&pOwner->EventHalls);
	myGets1(temp, SIZE, fp);
	pOwner->name = getDynStr(temp);

	int count;
	fscanf(fp, "%d", &count);
	fgetc(fp);

	EventHall* eh;
	for (int i = 0; i < count; i++)
	{
		eh = (EventHall*)calloc(1, sizeof(EventHall));
		if (!eh)
			break;
		if (!readEventHallFromTxtFile(eh, fp))
		{
			printf("Error loading Hall from file\n");
			CLOSE_RETURN_0(fp);
		}
		insertToCode(&pOwner->EventHalls, eh);
	}

	fclose(fp);
	return 1;
}

void printEventHallsOwnerDetails(const EventHallsOwner* pOwner)
{
	L_print(&pOwner->EventHalls, printEventHall);
}
void printEventHallsOwner(const EventHallsOwner* pOwner)
{
	printf("owner name : %s\n", pOwner->name);
	printf("there are %d EventHalls\n", L_countList(&pOwner->EventHalls));
}

int AddEventHalls(EventHallsOwner* pOwner) 
{

	EventHall* eh = (EventHall*)calloc(1, sizeof(EventHall));
	if (!pOwner)
		return 0;

	if (!InItEventHall(eh, pOwner))
	{
		freeEventHall(eh);
		free(pOwner);
		return 0;
	}
	insertToCode(&pOwner->EventHalls, eh);
	return 1;
}

void insertToCode(LIST* pList, const EventHall* eh)
{
	if (!pList)
		return;
	NODE* pn = pList->head.next;
	NODE* temp = &pList->head;
	while (pn)
	{
		if (strcmp(eh->name, ((EventHall*)pn->key)->name) < 0)
		{
			L_insert(temp, eh);
			return;
		}
		temp = pn;
		pn = pn->next;
	}
	L_insert(temp, eh);

}
void freeEventHallsOwner(EventHallsOwner* pOwner) 
{
	L_free(&pOwner->EventHalls, freeEventHall);
}

int InItEventHall(EventHall* pEvent, EventHallsOwner* pOwner) 
{
		while (1)
		{
			pEvent->name = getEventHallName(pEvent->name);
		if (checkUniqueName(pEvent->name, pOwner))
			break;

		printf("This name already in use - enter a different name\n");
		}

	return InitEventHall(pEvent);
}

const EventHall* findEventHallByName(const EventHallsOwner* pOwner, char* name)
{
	NODE* ad = pOwner->EventHalls.head.next;
	while (ad)
	{
		if (!compareByName(ad->key, name))
			return ad->key;
		ad = ad->next;
	}
	return NULL;
}

int checkUniqueName( char* name, const EventHallsOwner* pOwner)
{
	NODE* ad = pOwner->EventHalls.head.next;
	while (ad)
	{
		if (!compareByName(ad->key, name))
			return 0;
		ad = ad->next;
	}
	return 1;
}

int compareByName(const void* n1, const void* n2) 
{
	EventHall* a1 = (EventHall*)n1;
	char* a2 = (char*)n2;
	return strcmp(a1->name, a2);
}

int	saveEventHallsOwnerToBinFile(const EventHallsOwner* pOwner, const char* fileName)
{
	FILE* fp;

	fp = fopen(fileName, "wb");
	if (!fp) {
		printf("Error open eventhall owner file to write\n");
		return 0;
	}
	
	if (!writeStringToFile(pOwner->name, fp, "Error writing string"))
	{
		fclose(fp);
		return 0;
	}

	int count = L_countList(&pOwner->EventHalls);
	if (!writeIntToFile(count, fp, "Error writing string"))
	{
		fclose(fp);
		return 0;
	}
	if (count > 0)
	{
		NODE* pN = pOwner->EventHalls.head.next;

		EventHall* eh;
		while (pN != NULL)
		{
			eh = (EventHall*)pN->key;
			if (!saveEventHallToBinFile(eh, fp))
			{
				printf("Error write eventhall\n");
				CLOSE_RETURN_0(fp);
			}
			pN = pN->next;
		}
	}
	fclose(fp);
	return 1;
}

int	saveEventHallsOwnerToTxtFile(const EventHallsOwner* pOwner, const char* fileName)
{
	FILE* fp;

	fp = fopen(fileName, "w");
	if (!fp) {
		printf("Error open eventhall owner file to write\n");
		return 0;
	}
	fprintf(fp, "%s\n", pOwner->name);
	int count = L_countList(&pOwner->EventHalls);
	fprintf(fp, "%d\n", count);
	if (count > 0)
	{
		NODE* pN = pOwner->EventHalls.head.next; 

		EventHall* eh;
		while (pN != NULL)
		{
			eh = (EventHall*)pN->key;
			if (!saveEventHallToTxtFile(eh, fp))
			{
				printf("Error write airport\n");
				CLOSE_RETURN_0(fp);
			}
			pN = pN->next;
		}
	}
	fclose(fp);
	return 1;
}

void printEventHallsByRegion(const EventHallsOwner* pOwner)
{
	int op = (int)getRegionType();
	NODE* e = pOwner->EventHalls.head.next;
	printf("these are all the eventhalls in the %s region\n", RegionTypeStr[op]);
	while (e)
	{
		EventHall* eh = (EventHall*)e->key;
		if ((int)eh->hallAddress.type == op)
			printf("%s\n",eh->name);
		e = e->next;
	}
}