#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <windows.h>
#include "MPFunctions.c"

int
main()
{
	int nSelect, nReturn = 0;
	
	struct RecordTag ExistRecords[100];
	
	initializeRecord(ExistRecords, 100);
	
	do
	{
		do 
		{
			displayTitle();
			printf("[1] Manage Data\n");
			printf("[2] Play\n");
			printf("[3] Exit\n");
			printf("------------------------------------------------------------------\n");
			printf("Enter: ");
			scanf("%1d", &nSelect);
			if(nSelect != 1 && nSelect != 2 && nSelect != 3)
			{
				printf("Invalid input! ");
				EnterToContinue(1);
			}
		} while(nSelect != 1 && nSelect != 2 && nSelect != 3);
		
		switch(nSelect)
		{
			case 1:
				system("cls");
				ManageData(&nReturn, ExistRecords);
				break;
			case 2:
				//PlayGame()
				printf("PLAY STILL IN PROGRESS");
				break;
			case 3:
				printf("Thanks for playing! :D");
				nReturn = 0;
				sleep(1);
				break;
		}
	} while(nReturn == 2);
	
	
}