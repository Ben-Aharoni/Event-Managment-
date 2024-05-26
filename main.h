#pragma once
#include "EventHallsOwner.h"
#include "Acountent.h"
#include "EventManager.h"

#define OWNER_Txt_FILE_NAME "halls_owner.txt"
#define OWNER_Bin_FILE_NAME "halls_owner.bin"
#define EVENTMANAGER_Txt_FILE_NAME "manager.txt"
#define EVENTMANAGER_BinFILE_NAME "manager.bin"
#define ACOUNTENT_Txt_FILE_NAME "acountent.txt"
#define ACOUNTENT_BinFILE_NAME "acountent.bin"
#define COMPRESSED_WORKER_FILE "worker.bin"

int inItEventManagerAndEventOWnerFromBinFile(EventManager* pManager, EventHallsOwner* pOwner, Acountent* a);
int inItEventManagerAndEventOWnerFromTxtFile(EventManager* pManager, EventHallsOwner* pOwner, Acountent* a);
void uploadSystem(EventManager* pManager, EventHallsOwner* pOwner, Acountent* a);
void displaySystem(EventManager* pManager, EventHallsOwner* pOwner);
void displaySystemSubcomponents(EventManager* pManager, EventHallsOwner* pOwner);
void addcomponents(EventManager* pManager, EventHallsOwner* pOwner, Acountent* a);
