#include <stdio.h>
#include "Date.h"


void getCorrectDate(Date* d)
{
	int flag = 0;
	if (d == NULL)
		return;
	do
	{
		char str[255];
		printf("Enter Event Date dd/mm/yyyy  minimum year 2025 \n");
		myGets2(str, SIZE);
		sscanf(str, "%d/%d/%d", &d->day, &d->month, &d->year);
		if (!checkDate(d->day, d->month, d->year))
		{
			printf("Error try again\n");
		}
		else
			flag = 1;
	} while (!flag);

}

int checkDate(int day, int month, int year)
{
	if (year < 2025)
		return 0;
	switch (month)
	{
	case 1: case 3: case 5: case 7: case 8: case 10: case 12:
		if (day > 31 || day < 0)
			return 0;
		break;

	case 2:
		if (day > 28 || day < 0)
			return 0;
		break;

	case 4: case 6: case 9: case 11:
		if (day > 30 || day < 0)
			return 0;
		break;

	default:
		return 0;
		break;
	}
	return 1;
}

void printDate(Date* d)
{
	if (d == NULL)
		return;
	printf("Date: %d/%d/%d", d->day, d->month, d->year);
}

int		compareDate(const void* d1, const void* d2)
{
	const Date* pDate1 = (const Date*)d1;
	const Date* pDate2 = (const Date*)d2;
	if (pDate1->year > pDate2->year)
		return 1;
	if (pDate1->year < pDate2->year)
		return -1;

	if (pDate1->month > pDate2->month)
		return 1;

	if (pDate1->month < pDate2->month)
		return -1;

	if (pDate1->day > pDate2->day)
		return 1;

	if (pDate1->day < pDate2->day)
		return -1;

	return 0;
}

int	saveDateToBinFile(const Date* pDate, FILE* fp)
{
	if (fwrite(pDate, sizeof(Date), 1, fp) != 1)
	{
		printf("Error write date\n");
		return 0;
	}
	return 1;
}

int loadDateFromBinFile(Date* d, FILE* fp)
{
	if (fread(d, sizeof(Date), 1, fp) != 1)
	{
		printf("Error write date\n");
		return 0;
	}
	return 1;
}

int	saveDateToTxtFile(const Date* pDate, FILE* fp)
{
	if (!pDate)
		return 0;
	fprintf(fp, "%d\n", pDate->day);
	fprintf(fp, "%d\n", pDate->month);
	fprintf(fp, "%d\n", pDate->year);

	return 1;
}
int loadDateFromTxtFile(Date* pDate, FILE* fp)
{
	if (!pDate)
		return 0;
	fscanf(fp, "%d", &pDate->day);
	fscanf(fp, "%d", &pDate->month);
	fscanf(fp, "%d", &pDate->year);
	return 1;
}