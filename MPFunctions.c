#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>
#include <windows.h>
#include "MPHeader.h"

void
displayTitle()
{
	printf("========================================================================\n");
	printf(" ____  ____  ____  ____  ____  ____  _________  ____  ____  ____  ____\n"); 
	printf("||T ||||Y ||||P ||||I ||||N ||||G ||||       ||||G ||||A ||||M ||||E ||\n");
	printf("||__||||__||||__||||__||||__||||__||||_______||||__||||__||||__||||__||\n");
	printf("|/__\\||/__\\||/__\\||/__\\||/__\\||/__\\||/_______\\||/__\\||/__\\||/__\\||/__\\|\n");
	printf("\n");
	printf("========================================================================\n");
}

void
EnterToContinue(int clear)
{
	sleep(1);
	printf("Press any key to continue");
	char enter = _getch();
	
	if(clear)
		system("cls");
}

int 
GetPassword(char * pPassword)
{
	int i = 0, nCorrect;
	char nInput[31];
	
	printf("Enter Password: ");
	while ((nInput[i] = _getch())!= 13) 
	{
	    if (nInput[i] == 8) 
		{
	        if (i > 0) 
			{
	            printf("\b \b");
	            i--;
	        }
	    } 
		else 
		{
	        if (i < 30) 
			{ 
	            i++;
	            printf("*");
	        }
	    }
    }
    nInput[i] = '\0';
		
	if(strcmp(nInput, pPassword) == 0)
		nCorrect = 1;
	else
		nCorrect = 0;
		
	return nCorrect;
}

void 
ManageData(int * nReturn)
{
	int MainMenu;
	char password[20] = "test";
	
	do
	{
		if(GetPassword(password))
		{
			printf("\nCorrect password! ");
			sleep(1);
			printf("\nSTILL IN PROGRESS!!");
			EnterToContinue(1);
			MainMenu = 2;
		}
		else
		{
			printf("\nWrong password!\n");
			sleep(1);
			do
			{
				printf("------------------------------------------------------------------\n");
				printf("Enter password again [1]\n");
				printf("Back to Main Menu [2]\n");
				printf("------------------------------------------------------------------\n");
				printf("Enter: ");
				scanf("%1d", &MainMenu);
				system("cls");
				
				if(MainMenu != 1 && MainMenu != 2)
				{
					printf("Invalid Input!\n");
					sleep(1);
				}
			} while (MainMenu != 1 && MainMenu != 2);
		}
	} while(MainMenu != 2);
	
	*nReturn = MainMenu;
}