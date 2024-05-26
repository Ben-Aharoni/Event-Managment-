#pragma once
#include "file.h"


#define INITIALSLENGTH 2
typedef enum {
	cook, waiter, barmen , NOfWorkers
} eWorkerType;

static const char* WorkerTypeStr[NOfWorkers]
= { "cook", "waiter", " barmen" };

typedef struct
{
	long ID;
	char nameInitials[INITIALSLENGTH + 1];
	eWorkerType WType;
}Worker;


int InItWorker(Worker* w);
void printWorker(const Worker* w);
eWorkerType getWorkerType();
Worker getWorkerByID(Worker* arr, int size, int ID);
int isSerialIDUnique(Worker* arr, int size, int ID);
const char* GetWorkerTypeStr(int type);
void InitNameInitials(char* initials);
int isCorrectId();
int saveWorkerToCompressedFile(const Worker* w, FILE* filename);
int loadWorkerArrFromFile(Worker* w, FILE* fcb);
int loadWorkerFromTxtFile(Worker* w, FILE* fp);
int saveWorkerToTxtFile(const Worker* w, FILE* fp);