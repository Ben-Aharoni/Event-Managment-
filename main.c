#include <stdio.h>
#include "main.h"

int main() {
	int opt = 0;
	int flag = 0;
	int choose = 0;
	Acountent a;
	EventHallsOwner pOwner;
	EventManager pManager;

	InItEventHallsOwnerFromTxtFile(&pOwner, OWNER_Txt_FILE_NAME);
	flag = 1;
	InItManager(&pManager);
	InItAcountent(&a);
	initEventManagerFromTxtFile(&pManager, EVENTMANAGER_Txt_FILE_NAME);
	loadAcounntentFromTxtFile(&a, ACOUNTENT_Txt_FILE_NAME);



	do {
		printf("Please choose one of the following options\n");
		printf(" 1 - upload system from file (text\\binary)\n");
		printf(" 2 - display system\n");//
		printf(" 3 - display subcomponents\n");//
		printf(" 4 - add components\n");//
		printf(" 5 - sort\n");//
		printf(" 6 - find\n");//
		printf(" 7 - display profit\n");//
		printf(" 8 - print invoice\n");
		printf("-1 - to exit\n");
		scanf("%d", &opt);

		switch (opt)
		{
		case 1:
			uploadSystem(&pManager,&pOwner, &a);
			flag = 1;

			//saveAcounntentToBinFile(&a, ACOUNTENT_Txt_FILE_NAME);
			//saveAcounntentToBinFile(&a, ACOUNTENT_BinFILE_NAME);
			break;

		case 2:
			if (!flag)
			{
				printf("WARNING!!! , YOU DIDN'T UPLOAD THE SYSTEM\n IF YOU CHOSE TO INITIALIZE YOURSELF THE FILES WILL BE DELETED!\n");
				printf("Enter 1 to contiue\n");
				scanf("%d", &choose);
				if (choose == 1)
				{
					InItManager(&pManager);
					inItOwner(&pOwner);
					InItAcountent(&a);
					displaySystem(&pManager, &pOwner);
					flag = 1;
				}
				else
					break;
			}
			else
				displaySystem(&pManager, &pOwner);
			break;

		case 3:
			if (!flag)
			{
				printf("WARNING!!! , YOU DIDN'T UPLOAD THE SYSTEM\n IF YOU CHOSE TO INITIALIZE YOURSELF THE FILES WILL BE DELETED!\n");
				printf("Enter 1 to contiue\n");
				scanf("%d", &choose);
				if (choose == 1)
				{
					InItManager(&pManager);
					inItOwner(&pOwner);
					InItAcountent(&a);
					displaySystemSubcomponents(&pManager, &pOwner);
					flag = 1;
				}
				else
					break;
			}
			else
				displaySystemSubcomponents(&pManager, &pOwner);
			break;

		case 4:
			if (!flag)
			{
				printf("WARNING!!! , YOU DIDN'T UPLOAD THE SYSTEM\n IF YOU CHOSE TO INITIALIZE YOURSELF THE FILES WILL BE DELETED!\n");
				printf("Enter 1 to contiue\n");
				scanf("%d", &choose);
				if (choose == 1)
				{
					InItManager(&pManager);
					inItOwner(&pOwner);
					InItAcountent(&a);
					addcomponents(&pManager, &pOwner, &a);
					flag = 1;
				}
				else
					break;
			}
			else
				addcomponents(&pManager, &pOwner, &a);
			break;

		case 5:
			if (!flag)
			{
				InItManager(&pManager);
				inItOwner(&pOwner);
				InItAcountent(&a);
				flag = 1;
			}
			eventSort(&pManager);
			break;

		case 6:
			if (!flag)
			{
				printf("you didn't initialize the system\n");
				InItManager(&pManager);
				inItOwner(&pOwner);
				InItAcountent(&a);
				flag = 1;
			}
			findEvent(&pManager);
			break;

		case 7:
			if (!flag)
			{
				printf("you didn't initialize the system\n");
				InItManager(&pManager);
				inItOwner(&pOwner);
				InItAcountent(&a);
				flag = 1;
			}
			calcProfit(&a);
			break;

		case 8:
			if (!flag)
			{
				printf("you didn't initialize the system\n");
				InItManager(&pManager);
				inItOwner(&pOwner);
				InItAcountent(&a);
				flag = 1;
			}
			printInvoiceByDate(&a);
			break;
		}
	} while (opt != -1);
	printf("bye");
	return 1;

}
int inItEventManagerAndEventOWnerFromBinFile(EventManager* pManager, EventHallsOwner* pOwner, Acountent* a)
{
	int res = InItEventHallsOwnerFromBinFile(pOwner , OWNER_Bin_FILE_NAME);
	if (!res)
	{
		inItOwner(pOwner);
		for (int i = 0; i < 2; i++)
		{
			if (!AddEventHalls(pOwner))
			{
				printf("error init owner\n");
				return 0;
			}
		}
	}
	res = loadAcounntentFromBinFile(a, ACOUNTENT_BinFILE_NAME);
	if (!res)
	{
		InItAcountent(a);
	}
	res = initEventManagerFromBinFile(pManager, EVENTMANAGER_BinFILE_NAME, COMPRESSED_WORKER_FILE);
	if (!res)
	{
		InItManager(pManager);
		for (int i = 0; i < 2; i++)
		{
			if (!addEvent(pManager,pOwner, a))
			{
				printf("error init manager\n");
				return 0;
			}
			if (!addWorker(pManager))
			{
				printf("error init manager\n");
				return 0;
			}
		}
		return 0;
	}
	return 1;
}
int inItEventManagerAndEventOWnerFromTxtFile(EventManager* pManager, EventHallsOwner* pOwner, Acountent* a)
{
	int res = InItEventHallsOwnerFromTxtFile(pOwner,OWNER_Txt_FILE_NAME);
	if (!res)
	{
		inItOwner(pOwner);
		for (int i = 0; i < 2; i++)
		{
			if (!AddEventHalls(pOwner))
			{
				printf("error init owner\n");
				return 0;
			}
		}
	}
	res = loadAcounntentFromTxtFile(a, ACOUNTENT_Txt_FILE_NAME);
	if (!res)
	{
		InItAcountent(a);
	}
	//res = initEventManagerFromTxtFile(pManager, EVENTMANAGER_Txt_FILE_NAME);
	if (!res)
	{
		InItManager(pManager);
		for (int i = 0; i < 2; i++)
		{
			if (!addEvent(pManager, pOwner,a))
			{
				printf("error init manager\n");
				return 0;
			}
			if (!addWorker(pManager))
			{
				printf("error init manager\n");
				return 0;
			}
		}
		return 0;
	}
	return 1;
}
void uploadSystem(EventManager* pManager, EventHallsOwner* pOwner, Acountent* a)
{
	int choose;
	printf("1 - binary  2 - text\n");
	scanf("%d", &choose);
	switch (choose)
	{
	case 1:
		if (inItEventManagerAndEventOWnerFromBinFile(pManager, pOwner, a))
			printf("success to load the details\n ");
		break;

	case 2:
		if (inItEventManagerAndEventOWnerFromTxtFile(pManager, pOwner, a))
			printf("success to load the details\n ");
		break;
	default:
		printf("invalid choice\n");
	}
}
void displaySystem(EventManager* pManager, EventHallsOwner* pOwner)
{
	printf("EVENT OWNER\n");
	printEventHallsOwner(pOwner);
	printf("\n-----------------------\n\n");
	printf("EVENT MANAGER\n");
	printEventManager(pManager);
}
void displaySystemSubcomponents(EventManager* pManager, EventHallsOwner* pOwner)
{
	printf("EVENT OWNER\n");
	printEventHallsOwner(pOwner);
	printEventHallsOwnerDetails(pOwner);
	printf("\n-----------------------\n\n");
	printf("EVENT MANAGER\n");
	printAllEventManager(pManager);	
}
void addcomponents(EventManager* pManager, EventHallsOwner* pOwner, Acountent* a)
{
	int op = 0;
	do
	{
		printf("Please choose one of the following options\n");
		printf(" 1 - add event\n");
		printf(" 2 - add worker\n");
		printf(" 3 - add eventhall\n");
		scanf("%d", &op);
		switch (op)
		{
		case 1:
			addEvent(pManager, pOwner,a);
			break;

		case 2:
			if(!addWorker(pManager))
				printf("ERROR ADD WORKER");
			break;
		case 3:
			if(!AddEventHalls(pOwner))
				printf("ERROR ADD EVENTHALL");
			break;
		default:
			printf("invalid option");
			break;
		}
	} while (op != 0);
}