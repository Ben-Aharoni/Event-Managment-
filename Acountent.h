#pragma once
#include "Invoice.h"
#include "General.h"


typedef struct
{
	Invoice** invoices;
	int NOfInvoices;

}Acountent;

void calcProfit(Acountent* a);
int addInvoice(Acountent* a, Invoice* i);
int compareByDate(const void* e1, const void* e2);
void printInvoiceByDate(Acountent* a);
const Invoice* findEventByDate(Acountent* a, Invoice* i);
int saveAcounntentToTxtFile(const Acountent* a, char* fileName);
int loadAcounntentFromTxtFile(Acountent* a, char* fileName);
int saveAcounntentToBinFile(const Acountent* a, char* fileName);
int loadAcounntentFromBinFile(Acountent* a, char* fileName);
void sortInvoiceByDate(Acountent* a);
int createInvoiceArr(Acountent* a);
int InItAcountent(Acountent* a);