#pragma once
#include "Date.h"
#include "EventHallsOwner.h"



typedef enum {
	wedding, britMila, barMitzva, genralEvent, NOfEvents
} eEventType;

static const char* EventTypeStr[NOfEvents]
= { "wedding", "britMila", "barMitzva", "genralEvent" };

typedef struct
{
	int cost;
	int guestCount;
	Date eventDate;
	EventHall  EventHall;
	eEventType eType;

}Event;



int InItEvent(Event* e, EventHallsOwner* pOwner);
void printEvent(const Event* e);
void freeEvent(Event* e);
eEventType getEventType();
int isEventFromNameEventHall(const Event* pEvent, const char* name);
const EventHall* setEventHallToEvent(const Event* pEvent);
const char* GetEventTypeStr(int type);
int checkCapacity(EventHall eh, const EventHallsOwner* pOwner, Event* e);
int	saveEventToBinFile(const Event* p, FILE* fp);
int loadEventFromBinFile(Event* p, FILE* fp);
int	saveEventToTxtFile(const Event* p, FILE* fp);
int loadEventFromTxtFile(Event* p, FILE* fp);
void	printEventPtr(void* e);
void	freeEventPtr(void* e);