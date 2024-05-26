#pragma once
#include "General.h"
#include "file.h"

typedef struct
{
	int day;
	int month;
	int year;
}Date;

void getCorrectDate(Date* date);
int checkDate(int day, int month, int year);
void printDate(Date* d);
int compareDate(const void* d1, const void* d2);
int	saveDateToBinFile(const Date* pDate, FILE* fp);
int loadDateFromBinFile(Date* d, FILE* fp);
int	saveDateToTxtFile(const Date* pDate, FILE* fp);
int loadDateFromTxtFile(Date* d, FILE* fp);
