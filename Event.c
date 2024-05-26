#include <stdio.h>
#include "Event.h"


int InItEvent(Event* e,EventHallsOwner* pOwner )
{
	if (!L_countList(&pOwner->EventHalls.head))
	{
		printf("no eventhall yet\n");
		return 0;
	}
	
	char temp[SIZE];
	if (e == NULL) {
		return 0;
	}
	e->eType = getEventType();
	

	printf("enter cost:\n ");
	scanf("%d", &e->cost);
	
	 getCorrectDate(&e->eventDate);
	 do
	 {
		 printEventHallsByRegion(pOwner);
		 printf("Enter the name of the Eventhall\n");
		 myGets2(temp, SIZE);
		 EventHall* eh = findEventHallByName(pOwner, temp);
		 if (!eh)
			 printf("wrong name\n");
		 else
		 {
			 e->EventHall = *eh;
			 e->guestCount = checkCapacity(e->EventHall, pOwner, e);
			 break;
		 }
	 } while (1);	
	 return 1;
}
void	printEventPtr(void* e)
{
	const Event* temp = *(Event**)e;
	printEvent(temp);
}


void printEvent(const Event* e) 
{
	if (!e) {
		return;
	}
	printf("Eventhall: %s\n", e->EventHall.name);
	printf("cost : %d\nguest count : %d\nevent type : %s\n" , e->cost , e->guestCount , EventTypeStr[e->eType]);
	printDate(&e->eventDate);
	printf("\n\n");
}
void	freeEventPtr(void* e)
{
	const Event* temp = *(Event**)e;
	freeEvent(temp);
}

void freeEvent(Event* e) 
{
	if (e = NULL) {
		return;
	}
	freeEventHall(&e->EventHall);
	free(e);
}

eEventType getEventType()
{

	int option;
	printf("\n\n");
	do {
		printf("Please enter one of the following types\n");
		for (int i = 0; i < NOfEvents; i++)
			printf("%d for %s\n", i, EventTypeStr[i]);
		scanf("%d", &option);
	} while (option < 0 || option >= NOfEvents);
	return (eEventType)option;
}

const char* GetEventTypeStr(int type)
{
	if (type < 0 || type >= NOfEvents)
		return NULL;
	return EventTypeStr[type];
}

int isEventFromNameEventHall(const Event* pEvent, const char* name)
{

}

const EventHall* setEventHallToEvent(const Event* pEvent) 
{

}

int checkCapacity(EventHall eh , const EventHallsOwner* pOwner,Event* e) 
{
	int count = 0;
	int flag = 0;
	do
	{
		printf("enter guest count: ");
		scanf("%d", &count);
		if (count < eh.maxCap)
		{
			flag = 1;
		}
		else
		{
			printf("the guest count is bigger then the max capacity of this hall\n");
			char choose;
				char temp[SIZE];
				printf("press:\n 1 to change event hall\n any other key to change the guest count\n ");
				scanf("%c", &choose);
				if (choose == '1')
				{
					printf("Enter the name of the Eventhall\n");
					myGets2(temp, SIZE);
					EventHall* eh = findEventHallByName(pOwner, temp);
					if (!eh)
					{
						printf("event hall not found\n");
						choose = 0;
					}
					else
						e->EventHall = *eh;
				}
		}

	} while (!flag);

	return count;
}
int	saveEventToBinFile(const Event* e, FILE* fp)
{

	if (!writeIntToFile(e->cost, fp, "Error write Event cost\n"))
		return 0;

	if (!writeIntToFile(e->guestCount, fp, "Error write Event guest count\n"))
		return 0;

	if (!saveEventHallToBinFile(&e->EventHall, fp))
		return 0;

	if (!saveDateToBinFile(&e->eventDate, fp))
		return 0;

	return 1;
}

int loadEventFromBinFile(Event* e, FILE* fp)
{
	if (!readIntFromFile(&e->cost, fp, "Error reading event cost\n"))
		return 0;

	if (!readIntFromFile(&e->guestCount, fp, "Error reading event guest count\n"))
		return 0;
	if (!readEventHallFromBinFile(&e->EventHall, fp))
		return 0;

	if (!loadDateFromBinFile(&e->eventDate, fp))
		return 0;

	return 1;
}

int	saveEventToTxtFile(const Event* p, FILE* fp)
{
	if (!p)
		return 0;
	fprintf(fp, "%d\n", p->cost);
	fprintf(fp, "%d\n", p->guestCount);
	fprintf(fp, "%d\n", (int)p->eType);
	if (!saveDateToTxtFile(&p->eventDate,fp))
		return 0;
	if (!saveEventHallToTxtFile(&p->EventHall, fp))
		return 0;
	return 1;
}
int loadEventFromTxtFile(Event* p, FILE* fp)
{

	if (!p)
		return 0;
	fscanf(fp, "%d", &p->cost);
	fscanf(fp, "%d", &p->guestCount);
	fscanf(fp, "%d", &(int)p->eType);
	if (!loadDateFromTxtFile(&p->eventDate, fp))
		return 0;
	if (!readEventHallFromTxtFile(&p->EventHall, fp))
		return 0;
	return 1;
}