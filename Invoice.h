#pragma once
#include "Event.h"

#define TAX 0.17
typedef struct
{
	Event event;
	char* customerName;

}Invoice;

void printInvoice(Invoice* i);
int saveInvoiceToBinFile(const Invoice* i, FILE* fp);
int loadInvoiceFromBinFile(Invoice* i, FILE* fp);
int saveInvoiceToTxtFile(const Invoice* i, FILE* fp);
int loadInvoiceFromTxtFile(Invoice* i, FILE* fp);
void InItInvoicName(Invoice* i);