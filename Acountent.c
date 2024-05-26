#include <stdio.h>
#include <stdlib.h> 
#include "Acountent.h"

int InItAcountent(Acountent* a)
{
    a->NOfInvoices = 0;
    a->invoices = NULL;
}

void calcProfit(Acountent* a) 
{
    int op = 0;
    int profit = 0;
    int flag = 0;
    printf("base on what field do you want to see the profit :\n1) year \n2) month \n3) day\n ");
    scanf("%d", &op);
    switch (op)
    {
         case 1:
         {
             int year = 0;
              while(!flag)
             {
                printf("Enter the year\n");
                scanf("%d", &year);
                if (year < 2025)
                    printf("wrong input");
                else
                    flag = 1;
             }
             for (int i = 0; i < a->NOfInvoices; i++)
             {
                 if (a->invoices[i]->event.eventDate.year <= year)
                     profit += a->invoices[i]->event.cost;
             }
                 break;
         }

         case 2:
         {
             int year = 0;
             int month = 0;
             while (!flag)
             {
                printf("Enter the year : ");
                scanf("%d", &year);
                if (year < 2025)
                {
                    printf("wrong input\n");
                    break;
                }
                else
                {
                    printf("Enter the month : ");
                    scanf("%d", &month);
                    if (month < 0 || month > 12)
                        printf("wrong input\n");
                    else
                        flag = 1;
                }
                 break;
             }
             if (!flag)
                 break;
             for (int i = 0; i < a->NOfInvoices; i++)
             {
                 if (a->invoices[i]->event.eventDate.year < year)
                     profit += a->invoices[i]->event.cost;
                 else
                 {
                     if (a->invoices[i]->event.eventDate.year == year)
                         if (a->invoices[i]->event.eventDate.month <= month)
                             profit += a->invoices[i]->event.cost;
                 }
             }
             break;
         }
         case 3:
         {
             Date d;
             getCorrectDate(&d);
             for (int i = 0; i < a->NOfInvoices; i++)
             {
                 if (a->invoices[i]->event.eventDate.year < d.year)
                     profit += a->invoices[i]->event.cost;
                 if (a->invoices[i]->event.eventDate.year == d.year)
                     if (a->invoices[i]->event.eventDate.month < d.month)
                         profit += a->invoices[i]->event.cost;
                 if (a->invoices[i]->event.eventDate.year == d.year)
                     if (a->invoices[i]->event.eventDate.month == d.month)
                         if (a->invoices[i]->event.eventDate.day <= d.day)
                            profit += a->invoices[i]->event.cost;
             }
             break;
         }
         default:
         {
             printf("invalid number");
             break;
         }
    }
    printf("the profit is %d NIS\n", profit);
}


int addInvoice(Acountent* a, Invoice* i)
{
    if (!i)
        return 0;
    a->invoices = (Invoice**)realloc(a->invoices, (a->NOfInvoices + 1) * sizeof(Invoice*));
    if (a->invoices == NULL)
    {
        return 0;
    }
    a->invoices[a->NOfInvoices++] = i;
    return 1;
}

int compareByDate(const void* e1, const void* e2)
{

    const Invoice* p1 = *(const Invoice**)e1;
    const Invoice* p2 = *(const Invoice**)e2;

    return compareDate(&p1->event.eventDate, &p2->event.eventDate);
}

void sortInvoiceByDate(Acountent* a)
{
    qsort(a->invoices,a->NOfInvoices , sizeof(Acountent*), compareByDate);
}

const Invoice* findEventByDate(Acountent* a, Invoice* i) 
{
    Invoice** I = (Invoice**)bsearch(&i, a->invoices, a->NOfInvoices, sizeof(Invoice*), compareByDate);
    if (!I)
        return NULL;
    return *I;
}

void printInvoiceByDate(Acountent* a)
{
    Invoice* i = (Invoice*)malloc(sizeof(Invoice));
    if (!i)
        return;
    getCorrectDate(&i->event.eventDate);
    sortInvoiceByDate(a);
    Invoice* temp = findEventByDate(a , i);
    if (!temp)
    {
        printf("Invocie not found\n\n");
        return;
    }
    printInvoice(temp);
}

int saveAcounntentToTxtFile(const Acountent* a, char* fileName)
{
    FILE* fp;
    fp = fopen(fileName, "w");
    if (!fp)
    {
        printf("Error open event manager file\n");
        return 0;
    }
    fprintf(fp, "%d\n", a->NOfInvoices);
    for (int i = 0; i < a->NOfInvoices; i++)
    {
        if (!saveInvoiceToTxtFile(a->invoices[i], fp))
            return 0;
    }
    fclose(fp);
    return 1;
}

int loadAcounntentFromTxtFile(Acountent* a, char* fileName)
{
    FILE* fp;
    fp = fopen(fileName, "r");
    if (!fp)
    {
        printf("Error open event manager file\n");
        return 0;
    }
    fscanf(fp, "%d", &a->NOfInvoices);
    if(!createInvoiceArr(a))
        FREE_CLOSE_RETURN_0(a->invoices, fp);
    for (int i = 0; i < a->NOfInvoices; i++)
    {
        if (!loadInvoiceFromTxtFile(a->invoices[i], fp))
            FREE_CLOSE_RETURN_0(a->invoices, fp);
    }
    fclose(fp);
    return 1;
}

int saveAcounntentToBinFile(const Acountent* a, char* fileName)
{
    FILE* fp;
    fp = fopen(fileName, "wb");
    if (!fp)
    {
        printf("Error open event manager file\n");
        return 0;
    }
    if (!writeIntToFile(a->NOfInvoices, fp, "ERROR to save the number of invoices"))
        return 0;
    for (int i = 0; i < a->NOfInvoices; i++)
    {
        if (!saveInvoiceToBinFile(a->invoices[i], fp))
            CLOSE_RETURN_0(fp);
    }
    fclose(fp);
    return 1;
}

int loadAcounntentFromBinFile(Acountent* a, char* fileName)
{
    FILE* fp;
    fp = fopen(fileName, "rb");
    if (!fp)
    {
        printf("Error open event manager file\n");
        return 0;
    }
    if (!readIntFromFile(&a->NOfInvoices, fp, "ERROR to read the number of invoices"))
        return 0;
    if(!createInvoiceArr(a))
       FREE_CLOSE_RETURN_0(a->invoices, fp);
    for (int i = 0; i < a->NOfInvoices; i++)
    {
        if (!loadInvoiceFromBinFile(&a->invoices[i], fp))
            FREE_CLOSE_RETURN_0(a->invoices, fp);
    }
    fclose(fp);
    return 1;
}

int createInvoiceArr(Acountent* a)
{
    if (a->NOfInvoices > 0)
    {
        a->invoices = (Invoice**)malloc(a->NOfInvoices * sizeof(Invoice*));
        if (!a->invoices)
        {
            printf("Alocation error\n");
            return 0;
        }
    }
    else
        a->invoices = NULL;

    for (int i = 0; i < a->NOfInvoices; i++)
    {
        a->invoices[i] = (Invoice*)calloc(1, sizeof(Invoice));
        if (!a->invoices[i])
        {
            printf("Alocation error\n");
            return 0;
        }
    }
    return 1;
}
