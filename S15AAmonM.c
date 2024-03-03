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

int
main()
{
	int nSelect, nReturn = 0; //Declare integer variables for user selection (nSelect) and return to main menu indicator (nReturn). Set nReturn to 0.
	
	struct RecordTag ExistRecords[100]; //Declare an array for the existing records with the structure RecordTag. 
	
	initializeRecord(ExistRecords, 100); //Function call initializeRecord to initialize the record.
	
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
				ManageData(&nReturn, ExistRecords); //function call ManageData()
				break;
			case 2: //If user chose to play the game:
				//PlayGame()
				printf("PLAY STILL IN PROGRESS\n");
				sleep(1);
				nReturn = 2;
				system("cls");
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