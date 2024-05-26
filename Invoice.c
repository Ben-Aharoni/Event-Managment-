#include <stdio.h>
#include "Invoice.h"



void printInvoice(Invoice* i)
{
    printf("\n| Invoice for: %s            Date: %d//%d//%d \n", i->customerName,i->event.eventDate.day, i->event.eventDate.month , i->event.eventDate.year);
    printf("| ---------------------------------------------- \n");
    printf("| From: AMIT & BEN EVENTS                        \n");
    printf("| %-16s %-19s %-10s\n", "event place", "guest Quantity", "Price");
    printf("| ---------------------------------------------- \n");
    printf("| %-20s %-14d %.2d[NIS]                          \n", i->event.EventHall.name, i->event.guestCount, i->event.cost);
    printf("| ---------------------------------------------- \n");
    printf("| TAX: %f%%\n", TAX);
    printf("| ---------------------------------------------- \n");
    printf("| Total: %.2f[NIS]\n", i->event.cost * (1 + TAX));
}

int loadInvoiceFromTxtFile(Invoice* i , FILE* fp)
{
    if (!i)
        return 0;
    char temp[SIZE];
    myGets1(temp, SIZE, fp);
    i->customerName = getDynStr(temp);
    if (!loadEventFromTxtFile(&i->event, fp))
        return 0;
    return 1;
}

int saveInvoiceToTxtFile(const Invoice* i, FILE* fp)
{
    if (!i)
        return 0;
    fprintf(fp, "%s\n",i->customerName);
    if (!saveEventToTxtFile(&i->event, fp))
        return 0;
    return 1;
}

int loadInvoiceFromBinFile(Invoice* i, FILE* fp)
{
    i->customerName = readStringFromFile(fp, "Error load cusomer name");
    if(!loadEventFromBinFile(&i->event, fp))
        return 0;
   return 1;
}
int saveInvoiceToBinFile(const Invoice* i, FILE* fp)
{
    if (!writeStringToFile(i->customerName, fp, "Error to save invoice customer name"))
        return 0;
    if(!saveEventToBinFile(&i->event, fp))
        return 0;
    return 1;
}
void InItInvoicName(Invoice* i)
{
    char temp[SIZE];
    printf("Enter your name for the invoice: \n");
    myGets2(temp, SIZE);
    i->customerName = getDynStr(temp);
}