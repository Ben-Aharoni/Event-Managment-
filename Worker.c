#include <stdio.h>
#include <string.h>
#include "Worker.h"

int InItWorker(Worker* w)
{
	if (w == NULL) {
		return 0; 
	}
	w->ID = isCorrectId();
	InitNameInitials(w->nameInitials);
	w->WType = getWorkerType();
	return 1; 
}

void InitNameInitials(char* initials) 
{
	while (1)
	{
		printf("Enter Worker name initials: (lower case letters)\n ");
		scanf(" %s", initials);
		if (strlen(initials) == INITIALSLENGTH)
		{
			for (int i = 0; i < INITIALSLENGTH + 1; i++)
			{
				if (i == 2)
					break;
				if (initials[i] < 'a' || initials[i] > 'z')
					printf("the letters must be lower case\n");
			}		
		}
		printf("initials must be 2 characters\n");
	}
	initials[2] = '\0';
}

void printWorker(const Worker* w) {
	if (w == NULL) {
		printf("Invalid worker\n");
		return;
	}

	printf("Worker ID: %d\n", w->ID);
	printf("Worker Name Initials: %s\n", w->nameInitials);
	printf("Worker Type: %s\n\n", GetWorkerTypeStr(w->WType));
}

eWorkerType getWorkerType() {

	int option;
	printf("\n\n");
	do {
		printf("Please enter one of the following types\n");
		for (int i = 0; i < NOfWorkers; i++)
			printf("%d for %s\n", i, WorkerTypeStr[i]);
		scanf("%d", &option);
	} while (option < 0 || option >= NOfWorkers);
	getchar();
	return (eWorkerType)option;
}

const char* GetWorkerTypeStr(int type)
{
	if (type < 0 || type >= NOfWorkers)
		return NULL;
	return WorkerTypeStr[type];
}

Worker getWorkerByID(Worker* arr, int size , int ID) 
{
	for (int i = 0; i < size; i++)
		if (arr[i].ID == ID)
			return arr[i];
}

int isSerialIDUnique(Worker* arr, int size, int ID)
{
	for (int i = 0; i < size; i++)
	{
		if (arr[i].ID == ID)
			return 0;
	}
	return 1;
	
}

int isCorrectId() 
{
	long id = 0;
	while (1)
	{
		printf("Enter Worker ID:\n ");
		scanf("%d", &id);
		if (id < 1000000000 && id > 99999999)
			break;
		printf("ID must be 9 characters\n");
	}
	return id;
}

int saveWorkerToCompressedFile(const Worker* w, FILE* filename)
{
	BYTE data[8] = { 0 };
	data[0] = w->ID & 0xFF;            // 0-7
	data[1] = (w->ID >> 8) & 0xFF;     // 8-15
	data[2] = (w->ID >> 16) & 0xFF;    // 16-23
	data[3] = (w->ID >> 24) & 0xFF;    // 24-31
	data[4] = (w->ID >> 32) & 0xFF;    // 32-39
	data[5] = ((w->ID >> 40) & 0x3F) | ((w->WType & 0x03) << 6); // 40 - 47
	data[6] = (w->nameInitials[0] - 'a') & 0x1F; // Lower 5 bits of first character
	data[6] |= ((w->nameInitials[1] - 'a') & 0x03) << 5; // Upper 2 bits of second character
	data[7] = ((w->nameInitials[1] - 'a') >> 2) & 0xFF;
	if (fwrite(&data, sizeof(BYTE), 8, filename) != 8)
		return 0;
	return 1;
}

int loadWorkerArrFromFile(Worker* w, FILE* fcb)
{
	BYTE data[8] = { 0 };
	if (fread(&data, sizeof(BYTE), 8, fcb) != 8)
		return 0;
	w->ID = (data[0]) | (data[1] << 8) | (data[2] << 16) | (data[3] << 24) | (data[4] << 32) | ((data[5] & 0x3F) << 40);
	w->WType = (data[5] >> 6) & 0x03;
	w->nameInitials[0] = (data[6] & 0x1F) + 'a';
	w->nameInitials[1] = ((data[6] >> 5) & 0x03) + ((data[7] & 0xFF) << 2) + 'a';
	w->nameInitials[2] = '\0';
	return 1;
}

int loadWorkerFromTxtFile(Worker* w, FILE* fp)
{
	if (!w)
		return 0;
	fscanf(fp, "%d", &w->ID);
	fscanf(fp, "%s", w->nameInitials);
	fscanf(fp, "%d", &(int)w->WType);
	return 1;
}
int saveWorkerToTxtFile(const Worker* w, FILE* fp)
{
	if (!w)
		return 0;
	fprintf(fp, "%d\n", w->ID);
	fprintf(fp, "%s\n", w->nameInitials);
	fprintf(fp, "%d\n", (int)w->WType);
	return 1;
}