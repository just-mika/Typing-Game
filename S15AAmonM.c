#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>
#include <windows.h>
#include "MPHeader.h"

int 
main()
{
	int nSelect, nReturn = 0;
	
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
				printf("MANAGE DATA STILL IN PROGRESS ");
				EnterToContinue(1);
				ManageData(&nReturn);
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
	return 0;
}