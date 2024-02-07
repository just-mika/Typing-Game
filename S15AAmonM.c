#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <windows.h>
#include "MPHeader.h"

int main()
{
	int nSelect;
	
	do
	{
		displayTitle();
		printf("[1] Manage Data\n");
		printf("[2] Play\n");
		printf("[3] Exit\n");
		printf("------------------------------------------------------------------\n");
		printf("Enter: ");
		scanf("%d", &nSelect);
		if(nSelect != 1 && nSelect != 2 && nSelect != 3)
		{
			printf("Invalid input!\n");
			sleep(1);
			system("cls");
		}
	} while(nSelect != 1 && nSelect != 2 && nSelect != 3);
	
	switch(nSelect)
	{
		case 1:
			printf("MANAGE DATA STILL IN PROGRESS");
			//ManageData()
			break;
		case 2:
			//PlayGame()
			printf("PLAY STILL IN PROGRESS");
			break;
		case 3:
			printf("Thanks for playing! :D");
			sleep(1);
			break;
	}
	return 0;
}