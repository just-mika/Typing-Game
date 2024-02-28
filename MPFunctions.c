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
	_getch();
	
	if(clear)
		system("cls");
}

int 
GetPassword(char * password)
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
		
	if(strcmp(nInput, password) == 0)
		nCorrect = 1;
	else
		nCorrect = 0;
		
	return nCorrect;
}

void
DisplayRecord(struct RecordTag existrecords)
{
	printf("=--------------------------------------------------------------------------------------------------=\n");
	printf("       ID        |	%d\n", existrecords.ID);
	printf("=--------------------------------------------------------------------------------------------------=\n");
	printf("      LEVEL      |	%s\n", existrecords.Level);
	printf("=--------------------------------------------------------------------------------------------------=\n");
	printf(" CHARACTER COUNT |	%d\n", existrecords.charCount);
	printf("=--------------------------------------------------------------------------------------------------=\n");
	printf("     PHRASE      |	%s\n", existrecords.Phrase);
	printf("=--------------------------------------------------------------------------------------------------=\n");
}

void
initializeRecord(struct RecordTag *existrecord, int size)
{
    int i, j;
    
    for(i = 0; i < size; i++)
    {
        existrecord[i].ID = 0;
        existrecord[i].charCount = 0;
    }
}


void
AddRecord(struct RecordTag *existrecords, int size, int *nSelect)
{
	String100 IntPhrase;
	int i;
	int phrasecount = 0;
	printf("ADD A RECORD\n");
	printf("------------------------------------------------------------------\n");
	printf("Enter a phrase (up to 100 characters): ");
	scanf(" %100[^\n]*c", IntPhrase);
	
	for(i = 0; i < size && *nSelect != 0; i++)
	{
		if(existrecords[i].ID > 0)
		{
			phrasecount++;
		}
		
		if(strcmp(IntPhrase, existrecords[i].Phrase) == 0)
		{
			DisplayRecord(existrecords[i]);
			printf("Phrase already exists! ");
			EnterToContinue(1);
			
			*nSelect = 0;
		}
	}
	
	if(*nSelect != 0)
	{
		existrecords[phrasecount + 1].ID = existrecords[phrasecount].ID + 1;
		strcpy(existrecords[phrasecount + 1].Phrase, IntPhrase);
		
		existrecords[phrasecount + 1].charCount = strlen(existrecords[phrasecount + 1].Phrase);
	
		if(existrecords[phrasecount + 1].charCount <= 20)
			strcpy(existrecords[phrasecount + 1].Level, "easy");
		else if (existrecords[phrasecount + 1].charCount <= 50)
			strcpy(existrecords[phrasecount + 1].Level, "medium");
		else
			strcpy(existrecords[phrasecount + 1].Level, "hard");
		
		printf("Record added! ");
		EnterToContinue(1);
		
		*nSelect = 0;
	}
	
}

//void EditRecord

void 
ManageData(int * nReturn, struct RecordTag *existrecords)
{
	int MainMenu;
	int nSelect;
	char password[20] = "test";
	
	do
	{
		if(GetPassword(password))
		{
			printf("\nCorrect password! ");
			sleep(1);
			system("cls");
			
			do 
			{
				printf("MANAGE DATA\n");
				printf("------------------------------------------------------------------\n");
				printf("[1] Add a Record\n");
				printf("[2] Edit a Record\n");
				printf("[3] Delete a Record\n");
				printf("[4] Import Data\n");
				printf("[5] Return to Main Menu\n");
				printf("------------------------------------------------------------------\n");
				printf("Enter: ");
				scanf("%1d", &nSelect);
				
				if(nSelect != 1 && nSelect != 2 && nSelect != 3 && nSelect != 4 && nSelect != 5)
				{
					printf("Invalid input! ");
					EnterToContinue(1);
				}
				
				if(nSelect == 1 || nSelect == 2 || nSelect == 3 || nSelect == 4 || nSelect == 5)
				{
					switch(nSelect)
					{
						case 1:
							system("cls");
							AddRecord(existrecords, 100, &nSelect);
							/*printf("STILL IN PROGRESS!!!\n");
							EnterToContinue(1);
							MainMenu = 2;*/
							break;
						case 2:
							printf("STILL IN PROGRESS!!!\n");
							EnterToContinue(1);
							MainMenu = 2;
							break;
						case 3:
							printf("STILL IN PROGRESS!!!\n");
							EnterToContinue(1);
							MainMenu = 2;
							break;
						case 4:
							printf("STILL IN PROGRESS!!!\n");
							EnterToContinue(1);
							MainMenu = 2;
							break;
						case 5:
							MainMenu = 2;
							system("cls");
							break;
					}
				}
			} while(nSelect != 1 && nSelect != 2 && nSelect != 3 && nSelect != 4 && nSelect != 5);
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