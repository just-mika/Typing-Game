/*********************************************************************************************************
This is to certify that this project is my own work, based on my personal efforts in studying and applying the concepts
learned. I have constructed the functions and their respective algorithms and corresponding code by myself. The
program was run, tested, and debugged by my own efforts. I further certify that I have not copied in part or whole or
otherwise plagiarized the work of other students and/or persons.
Mikaela Nicole B. Amon, DLSU ID# 12340790
*********************************************************************************************************/


#include <stdio.h>
#include <unistd.h>
#include <windows.h>
#include "MPFunctions.c"
//#include "MPHeader.h"
#define MAX_SIZE 100

int
main()
{
	int nSelect, nReturn = 0; //Declare integer variables for user selection (nSelect) and return to main menu indicator (nReturn). Set nReturn to 0.
	
	struct RecordTag ExistRecords[MAX_SIZE]; //Declare an array for the existing records with the structure RecordTag. 
	
	struct ScoreTag PlayerScores[MAX_SIZE];
	
	initializeRecord(ExistRecords, MAX_SIZE); //Function call initializeRecord to initialize the record.
	
	char strPassword[20] = "IHopeIPass"; //Declare variable for the password. Set password to the following string.
	
	system("cls"); //Clear screen before displaying the game.
	
	//Execute this statement at least once.
	do
	{
		//Execute this statement at least once.
		do 
		{
			displayTitle(); //Function call to display the title.
			printf("[1] Manage Data\n");
			printf("[2] Play\n");
			printf("[3] Exit\n");
			printf("------------------------------------------------------------------\n");
			printf("Enter: ");
			scanf("%1d", &nSelect); //Ask for user integer input. Only read one digit integer.
			
			//Execute this statement if the user selected neither of the choices
			if(nSelect != 1 && nSelect != 2 && nSelect != 3)
			{
				printf("Invalid input! ");
				EnterToContinue(1); //continue prompt
			}
		} while(nSelect != 1 && nSelect != 2 && nSelect != 3); //only loop this statement if user input is invalid.
		
		//Switch case for selection
		switch(nSelect)
		{
			case 1: //If user chose to manage data:
				system("cls"); //clear screen
				do //Execute ManageData option
				{
					//Execute this statement only if function call GetPassword() returns 1.
					if(GetPassword(strPassword))
					{
						printf("\nCorrect password! ");
						sleep(1); //Pause for 1 second
						system("cls"); //Clear screen
						
						//Execute this statement at least once
						do
						{
							printf("MANAGE DATA\n");
							printf("------------------------------------------------------------------\n");
							printf("[1] Add a Record\n");
							printf("[2] Edit a Record\n");
							printf("[3] Delete a Record\n");
							printf("[4] Import Data\n");
							printf("[5] Export Data\n");
							printf("[6] Return to Main Menu\n");
							printf("------------------------------------------------------------------\n");
							printf("Enter: ");
							scanf("%1d", &nSelect); //Ask for user selection
							
							switch(nSelect) //Switch case for the different selections
							{
								case 1: //If user chooses to add record:
									system("cls"); //clear screen
									AddRecord(ExistRecords, MAX_SIZE, &nSelect); //Function call AddRecord()
									break;
								case 2: //If user chooses to edit record:
									system("cls"); //clear screen
									EditRecord(ExistRecords, MAX_SIZE, &nSelect); //Function call EditRecord()
									break;
								case 3: //If user chooses to delete record:
									system("cls"); //clear screen
									DeleteRecord(ExistRecords, MAX_SIZE, &nSelect); //Function call DeleteRecord()
									break;
								case 4: //If user chooses to import data:
									system("cls"); //clear screen
									ImportData(ExistRecords, MAX_SIZE, &nSelect); //Function call ImportData()
									break;
								case 5: //If user chooses to import data:
									system("cls"); //clear screen
									ExportData(ExistRecords, MAX_SIZE, &nSelect); //Function call ExportData()
									break;
								case 6: //If user chooses to return to main menu
									nReturn = 2; //Set nMainMenu to 2 to prevent loop AND return to main menu
									system("cls"); //clear screen
									break;
								default: //If user chooses neither of the choices
									printf("Invalid input! "); 
									EnterToContinue(1); //continue prompt
									break;
							}
						} while(nSelect != 1 && nSelect != 2 && nSelect != 3 && nSelect != 4 && nSelect != 5 && nSelect != 6); //Loop statement only if the input is invalid.
					}
					else //Execute this is the password input is wrong.
					{
						printf("\nWrong password!\n");
						sleep(1); //Pause for 1 second
						do //Execute this statement at least once
						{
							printf("------------------------------------------------------------------\n");
							printf("Enter password again [1]\n");
							printf("Back to Main Menu [2]\n");
							printf("------------------------------------------------------------------\n");
							printf("Enter: ");
							scanf("%1d", &nReturn); //Enter user's selection if they want to return to main menu or not
							system("cls"); //clear screen
							
							if(nSelect != 1 && nSelect != 2) //Execute this statement if input is neither 1 nor 2
							{
								printf("Invalid Input!\n");
								sleep(1);
							}
						} while (nReturn != 1 && nReturn != 2); //Only loop this statement if user input is invalid.
					}
				} while (nReturn != 2); //Loop this statement if user chooses to enter the password again.
				break;
			case 2: //If user chose to play the game:
				system("cls"); //clear screen
				do
				{
					do 
					{
						printf("PLAY GAME\n");
						printf("------------------------------------------------------------------\n");
						printf("[1] Play\n");
						printf("[2] View Scores\n");
						printf("[3] Return to Main Menu\n");
						printf("------------------------------------------------------------------\n");
						printf("Enter: ");
						scanf("%1d", &nSelect); //Ask for user selection
						
						switch(nSelect) //Switch case for the different selections
						{
							case 1: //If user chooses to play game:
								system("cls"); //clear screen
								PlayGame(ExistRecords, PlayerScores, MAX_SIZE, &nSelect); //Function call PlayGame()
								break;
							case 2: //If user chooses to view scores:
								system("cls"); //clear screen
								DisplayScores(PlayerScores, &nSelect, MAX_SIZE); //Function call DisplayScores()
								break;
							case 3: //If user chooses to go back to main menu:
								system("cls"); //clear screen
								nReturn = 2;
								break;
							default: //If user chooses neither of the choices
								printf("Invalid input! "); 
								EnterToContinue(1); //continue prompt
								break;
						}
					} while(nSelect != 1 && nSelect != 2 && nSelect != 3); //Loop statement only if the input is invalid.
				} while(nReturn != 2); //loop this statement until user wishes to go back to Main menu
				break;
			case 3: //If user chose to exit program:
				printf("Thanks for playing! :D");
				nReturn = 0; //Set nReturn to 0 to prevent the loop from executing again
				sleep(1); //Pause for 1 second
				break;
		}
	} while(nReturn == 2); //Loop this statement only if nReturn is 2.
	
	return 0;
}