#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <unistd.h>
#include <windows.h>
#include "MPHeader.h"

// displayTitle displays the title of the game.
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

/* EnterToContinue tells the user to press any key to continue. This is to prevent displaying everything at once.
@param nClear - indicates if the program will clear the screen after pressing a key or not. 
Pre-condition: nClear is an integer either 1 or 0 (1 to clear the screen, 0 to not clear the screen.)
*/
void
EnterToContinue(int nClear)
{
	sleep(1); //Pause for 1 second before displaying the message.
	printf("Press any key to continue");
	_getch(); //Use _getch() for the user to enter a character. Doesnt necessarily have to be contained in a variable.
	
	if(nClear) //Execute CMD command "cls" if nClear is 1.
		system("cls");
}

/* GetPassword asks for a password input and returns an integer which indicates if the user entered the correct password.
@param *strPassword - pointer to a string that contains the password input
@return nCorrect which indicates if the password is correct (1 if correct, 0 if incorrect)
Pre-condition: strPassword only contains letters, numbers, or symbols
*/
int 
GetPassword(char * strPassword)
{
	int i = 0, nCorrect; // Declare index variable (i) and set to 0 so it begins at the first index; nCorrect to indicate if the password is correct or not
	char strInput[31];     // Declare strInput for the user's password input with max of 30 characters.
	
	printf("Enter Password: ");
	
	do //Execute this statement at least once.
	{
		//Use _getch() function from <conio.h> to assign a character in current index of strInput.
		strInput[i] = _getch();
		//Execute statement if the inputed value is 8 (ASCII value for Backspace)
	    if (strInput[i] == 8)
		{
			//Execute statement only if the current index is greater than 0. This is to prevent erasing characters before the input.
	        if (i > 0) 
			{
				//Backspace escape sequence is used twice to actually erase the previous character. Only one "\b" will only move the cursor to the left.
	            printf("\b \b");
	            i--; //decrement index to go back to the previous index.
	        }
	    }
	    //Execute statement if the inputed value is NOT 8
		else 
		{
			//Execute statement only if the current index is less than 30 AND the current input is NOT 13 (ASCII value for Enter). 
			//The first condition is to prevent the string to have length beyond its size. 
			//The second is to prevent incrementing index and printing an asterisk if Enter key was pressed.
	        if (i < 30 && strInput[i] != 13) 
			{ 
	            i++; //increment index to proceed to the next index
	            printf("*"); //display asterisk "*" to indicate that a character has been inputed.
	        }
	    }
	    
    } while(strInput[i] != 13);  //Loop the statement until Enter key is pressed.
    
    strInput[i] = '\0'; //set NULL byte to the index after the last character input to terminate the string.
	
	//Execute the statement if the input and the password are identical
	if(strcmp(strInput, strPassword) == 0)
		nCorrect = 1; //Set nCorrect to 1 to indicate that the password input is correct
	//Execute the statement if the input and the password are NOT identical
	else
		nCorrect = 0; //Set nCorrect to 0 to indicate that the password input is wrong.
	
	//Return the value of nCorrect.
	return nCorrect;
}

/* DisplayRecord displays the given record's information in a tabular format.
@param nHeader - indicates if the program will display the header or not.
@param ExistRecords - a structure containing an existing record.
Pre-conditions: 
- nHeader is an integer that either contains 1 or 0.
- ExistRecord's ID number is NOT 0 (Meaning there is a phrase in this record).
*/
void
DisplayRecord(int nHeader, 
			  struct RecordTag ExistRecord)
{
	if(nHeader) //Execute this statement only if nHeader is not 0.
	{
		printf("=------------------------------------------------------------------------------------------=\n");
		printf("  ID  |   LEVEL   |  CHAR COUNT  |  PHRASE\n");
		printf("=------------------------------------------------------------------------------------------=\n");
	}
    printf(" %3d  |", ExistRecord.ID); //Display the ID number.
	printf("   %3s", ExistRecord.Level); //Display phrase level.
	if(strcmp(ExistRecord.Level, "medium") == 0) //Execute this statement only if level is medium. This is for consistent spacing.
		printf("  |");
	else
		printf("    |");
	printf(" %6d       |", ExistRecord.charCount); //Display phrase's character count.
	printf("  %s\n", ExistRecord.Phrase); //Display the phrase itself.
    printf("=------------------------------------------------------------------------------------------=\n");
}

/* initializeRecord initializes the records to make sure there is something in the records (even if there are no phrases yet) to prevent errors.
@param *ExistRecords - pointer to a structure array containing all the records.
@param nSize - indicates the size of the structure array.
Pre-condition: 
- nSize is an integer greater than 0.
*/
void
initializeRecord(struct RecordTag *ExistRecords, 
				 int nSize)
{
    int i; //Declare index variable.
    
    /*For loop statement to initialize.
    Statement 1: Set index to 0
    Statment 2: Loop statement until index is greater than or equal to the array size.
    Statement 3: Post-increment index
    */
    for(i = 0; i < nSize; i++)
    {
        ExistRecords[i].ID = 0; //Set every ID number to 0.
        strcpy(ExistRecords[i].Level, "None"); //Set every level to "None"
        ExistRecords[i].charCount = 0; //Set every character count to 0
        strcpy(ExistRecords[i].Phrase, "None"); //Set every Phrase to "None"
    }
}


/* AddRecord allows the admin to add a phrase to the records.
@param *ExistRecords - pointer to a structure array containing all the records.
@param nSize - indicates the size of the structure array.
@param nSelect - pointer to the variable that indicates the user selection from Manage Data Menu. Used to go back to said menu.
Pre-condition: 
- nSize is an integer greater than 0.
*/
void
AddRecord(struct RecordTag *ExistRecords, 
		  int nSize, 
		  int *nSelect)
{
	String100 strPhrase; //Declare user's phrase input. Data type is character array with size 101.
	int i; //Declare index variable
	int nPhraseCount = 0; //Declare integer variable for the number of existing phrases in the records. Set value to 0.
	int nNextPhrase; //Declare integer variable for the index of the added phrase.
	
	printf("ADD A RECORD\n");
	printf("-----------------\n");
	printf("Enter a phrase up to 100 characters (type /back to go to back to menu): ");
	scanf(" %100[^\n]*c", strPhrase); //Input string. Only read up to 100 characters AND stop inputting after pressing enter.
	
	if(strcmp(strPhrase, "/back") != 0) //Execute statement if phrase input isnt "/back" (command to go back to Manage Data Main Menu)
	{
		/*For loop statement to check if the phrase entered already exists in the records.
		Statement 1: Initialize index to 0
		Statement 2: Continue loop if index is less than the array size AND if nSelect is not 0 (so that the loop would stop once existing phrase is found.)
		Statement 3: Post-increment index
		*/
		for(i = 0; i < nSize && *nSelect != 0; i++)
		{
			if(ExistRecords[i].ID > 0) //Execute statement if there is a phrase in the current index of ExistRecords.
				nPhraseCount++; //Increment phrase count
			
			if(strcmp(strPhrase, ExistRecords[i].Phrase) == 0) //Execute statement if the inputed phrase already exists in the records.
			{
				DisplayRecord(1, ExistRecords[i]); //Function call DisplayRecord to display the said existing phrase (including header)
				printf("Phrase already exists! "); 
				EnterToContinue(1); //Function call EnterToContinue for continue prompt.
				
				*nSelect = 0; //Set nSelect to 0 to go back to Manage Data Menu.
			}
		}
		
		//Execute statement if nSelect is not yet 0 (meaning the entered phrase does not exist yet in the records.)
		if(*nSelect != 0)
		{
			//Set index of the next phrase to the current value of the phrase count.
			nNextPhrase = nPhraseCount;
			//Decrement phrase count only if there are phrases in the records to represent the index of the last phrase in the records.
			if(nPhraseCount > 0)
				nPhraseCount--;
			//Set the ID of the added record to the next number after the last phrase's ID.
			ExistRecords[nNextPhrase].ID = ExistRecords[nPhraseCount].ID + 1;
			//Add the phrase itself to the records.
			strcpy(ExistRecords[nNextPhrase].Phrase, strPhrase);
			//Set the character count of the phrase by using strlen function in <string.h>
			ExistRecords[nNextPhrase].charCount = strlen(ExistRecords[nNextPhrase].Phrase);
			
			//Set level to "easy" if character count is less than or equal to 20
			if(ExistRecords[nNextPhrase].charCount <= 20)
				strcpy(ExistRecords[nNextPhrase].Level, "easy");
			//Set level to "medium" if character count is greater than 20 and less than or equal to 50
			else if (ExistRecords[nNextPhrase].charCount <= 50)
				strcpy(ExistRecords[nNextPhrase].Level, "medium");
			//Set level to "hard" if character count is greater than 50
			else
				strcpy(ExistRecords[nNextPhrase].Level, "hard");
				
			DisplayRecord(1, ExistRecords[nNextPhrase]); //Display the added record
			printf("Record added! ");
			EnterToContinue(1); //continue prompt
			
			*nSelect = 0; //Set nSelect to 0 to go back to Manage Data Menu
		}
	}
	else //Otherwise, set nSelect to 0 and clear screen.
	{
		*nSelect = 0;
		system("cls");
	}
}

/* EditRecord allows the admin to edit existing records.
@param *ExistRecords - pointer to a structure array containing all the records.
@param nSize - indicates the size of the structure array.
@param nSelect - pointer to the variable that indicates the user selection from Manage Data Menu. Used to go back to said menu.
Pre-condition: 
- nSize is an integer greater than 0.
*/
void
EditRecord(struct RecordTag *ExistRecords, 
		   int nSize, 
		   int *nSelect)
{
	String100 strPhrase; //Declare user's phrase input. Data type is character array with size 101.
	int i, nRecordSelect; //Declare index variable and variable for the record selection (nRecordSelect)
	int nIndex, nBack = 1; //Declare the index of the selected record (nIndex) and the indicator to go back to edit more records (nBack). Set this to 1.
	int nPhraseCount = 0, nFound; //Declare variable for the no. of phrases in the records (nPhraseCount) and indicator if an identical phrase is found (nFound).

	do //Execute this statement at least once
	{
		printf("EDIT RECORD\n");
		printf("-----------------\n\n");
		
		if(ExistRecords[0].ID != 0) //Execute this statement if there ARE existing records
		{
			do //Execute this statement at least once
			{
				/*For loop to display the existing records in a tabular format.
				Statement 1: Initialize i to 0
				Statement 2: Loop statement as long as i is less than nSize
				Statement 3: Post-increment i
				*/
				for(i = 0; i < nSize; i++)
				{
					//Execute this statement if current index does have a phrase in it.
					if(ExistRecords[i].ID != 0)
					{	
						//Function call DisplayRecord to display the current record.
						//Display the header ONLY at the first index.
						if(i == 0)  
							DisplayRecord(1, ExistRecords[i]);
						else
							DisplayRecord(0, ExistRecords[i]);
						nPhraseCount++; //Increment phrase count to count the number of phrases
					}
				}
			
				printf("\nSelect ID number (Enter 0 to go back to menu): ");
				scanf("%d", &nRecordSelect); //Ask for admin input for the ID number of the desired record to edit.
				
				//Execute this statement only if selected ID number is NOT 0 (an input of 0 will cause to return to Manage Data Menu)
				if(nRecordSelect > 0)
				{
					nIndex = -1; //Always reset nIndex to -1 before finding for the index.

					/*For loop to search for the record 
					Statement 1: Initialize i to 0
					Statement 2: Loop statement as long as i is less than nSize
					Statement 3: Post-increment i
					*/
					for(i = 0; i < nSize; i++)
					{
						if(ExistRecords[i].ID == nRecordSelect) //Set nIndex to current value of i the current index ID matches the user input
							nIndex = i;
					}
					//Execute this statement if the ID number is not found.
					if(nIndex == -1)
					{
						printf("Record not found! ");
						EnterToContinue(1); //Continue prompt
						printf("EDIT RECORD\n");
						printf("-----------------\n\n"); //Re-print this to display again after clear screen
					}
				}
			} while(nIndex == -1 && nRecordSelect != 0); //Loop the statement if index is not found AND user did not input 0.
				
			//Execute this statement if user did not input 0.
			if(nRecordSelect != 0)
			{
				do
				{
					printf("Enter a phrase (up to 100 characters): ");
					scanf(" %100[^\n]*c", strPhrase); //Input string. Only read up to 100 characters AND stop inputting after pressing enter.
					
					nFound = -1; //Reset nFound to -1 every time this loops.
					//For loop to check if theres an identical phrase in the records. Stop before i reaches the number of phrases.
					for(i = 0; i < nPhraseCount; i++)
					{
						//If the input is identical to at least one of the phrases in the records, execute the statement
						if(strcmp(strPhrase, ExistRecords[i].Phrase) == 0)
						{
							nFound = i; //set to the index of the identical phrase
							printf("\nPhrase already exists! It's in ID Number %d.\n", ExistRecords[i].ID); //display the phrase's ID number.
						}
					}
				} while(nFound != -1); //Loop if there is an identical phrase found.
				
				//Change the phrase in the index to the inputed phrase.
				strcpy(ExistRecords[nIndex].Phrase, strPhrase);
				//Change character count based on this inputed string
				ExistRecords[nIndex].charCount = strlen(ExistRecords[nIndex].Phrase);
				//Change level based on the inputed string
				if(ExistRecords[nIndex].charCount <= 20)
					strcpy(ExistRecords[nIndex].Level, "easy");
				else if (ExistRecords[nIndex].charCount <= 50)
					strcpy(ExistRecords[nIndex].Level, "medium");
				else
					strcpy(ExistRecords[nIndex].Level, "hard");
				
				//Clear screen
				system("cls");
				printf("Record edited!\n\n\n");
				
				//Display records again in tabular format
				for(i = 0; i < nSize; i++)
				{
					if(ExistRecords[i].ID != 0)
					{	
						if(i == 0) //Only display header at first loop
							DisplayRecord(1, ExistRecords[i]);
						else
							DisplayRecord(0, ExistRecords[i]);
					}
				}
				
				sleep(1); //Pause for 1 second
				printf("\n------------------------------------------------------------------\n");
				printf("Continue Editing [1]\n");
				printf("Back to Main Menu [2]\n");
				printf("------------------------------------------------------------------\n");
				do //Execute this at least once
				{
					printf("Enter: ");
					scanf("%1d", &nBack); //Ask user input if user want to contiue editing 
					//If nBack is neither of the choices, display message
					if (nBack != 1 && nBack != 2) 
						printf("Invalid input!\n");
				} while (nBack != 1 && nBack != 2); //loop this only if nBack is invalid
				system("cls"); //clear screen
			}
			else //If user input 0, clear screen and set nBack to 2 to prevent the loop from executing again (and to go back to manage data menu)
			{
				system("cls");
				nBack = 2;
			}
		}
		else //If there are no records found, execute this statement
		{
			printf("No records found! ");
			EnterToContinue(1); //continue prompt
			nBack = 2; //Set nBack to 2 to prevent the loop
		}
	} while(nBack == 1); //Loop as long as nBack is equal to 1.
	
	*nSelect = 0; //Set nSelect to 0 to go back to Manage Data Menu.
}

/* DeleteRecord allows the admin to delete a phrase to the records.
@param *ExistRecords - pointer to a structure array containing all the records.
@param nSize - indicates the size of the structure array.
@param nSelect - pointer to the variable that indicates the user selection from Manage Data Menu. Used to go back to said menu.
Pre-condition: 
- nSize is an integer greater than 0.
*/
void
DeleteRecord(struct RecordTag *ExistRecords, 
			 int nSize, 
			 int *nSelect)
{
	int i, nRecordSelect, nConfirm; //Declare index variable, variable for the record selection (nRecordSelect), and variable for the confirmation option.
	int nIndex, nBack = 1; //Declare the index of the selected record (nIndex) and indicator to go back to edit more records (nBack). Set this to 1.
	int nPhraseCount = 0;  //Declare integer variable for the number of existing phrases in the records. Set value to 0. 
	
	//Execute this statement at least once.
	do
	{
		printf("DELETE RECORD\n");
		printf("-----------------\n\n");
		
		if(ExistRecords[0].ID != 0) //Execute this statement if there ARE existing records
		{
			do //Execute this statement at least once
			{
				/*For loop to display the existing records in a tabular format.
				Statement 1: Initialize i to 0
				Statement 2: Loop statement as long as i is less than nSize
				Statement 3: Post-increment i*/
				for(i = 0; i < nSize; i++)
				{
					if(ExistRecords[i].ID != 0) //Execute this statement if current index does have a phrase in it.
					{	
						//Function call DisplayRecord to display the current record.
						//Display the header ONLY at the first index.
						if(i == 0)
							DisplayRecord(1, ExistRecords[i]);
						else
							DisplayRecord(0, ExistRecords[i]);
						nPhraseCount++; //Increment phrase count to count the number of existing phrases
					}
				}
			
				printf("\nSelect ID number (Enter 0 to go back to menu): ");
				scanf("%d", &nRecordSelect); //Ask for admin input for the ID number of the desired record to delete.
				
				if(nRecordSelect > 0) //Execute this statement only if selected ID number is NOT 0 (an input of 0 will cause to return to Manage Data Menu)
				{
					nIndex = -1; //Always reset nIndex to -1 before finding for the index.
					
					/*For loop to search for the record 
					Statement 1: Initialize i to 0
					Statement 2: Loop statement as long as i is less than nSize
					Statement 3: Post-increment i
					*/
					for(i = 0; i < nSize; i++)
					{
						if(ExistRecords[i].ID == nRecordSelect) //Set nIndex to current value of i the current index ID matches the user input
							nIndex = i;
					}
					//Execute this statement if the ID number is not found.
					if(nIndex == -1)
					{
						printf("Record not found! ");
						EnterToContinue(1); //Continue prompt
						printf("DELETE RECORD\n");
						printf("-----------------\n\n"); //Re-print this to display again after clear screen
					}
				}
			} while(nIndex == -1 && nRecordSelect != 0); //Loop the statement if index is not found AND user did not input 0.
			
			//Execute this statement if user did not input 0.
			if(nRecordSelect != 0)
			{
				do //Execute this statement at least once
				{
					system("cls"); //Clear screen
					printf("Are you sure you want to delete this record?\n\n"); //Display confirmation message
					DisplayRecord(1, ExistRecords[nIndex]); //Display the record that admin chose to delete
					printf("\n------------------------------------------------------------------\n");
					printf("Yes [1]\n");
					printf("No [2]\n");
					printf("------------------------------------------------------------------\n");
				
					printf("Enter: ");
					scanf("%1d", &nConfirm); //Ask user input for their selection
					
					//Execute this statement if nConfirm is neither 1 nor 2
					if(nConfirm != 1 && nConfirm != 2)
						printf("Invalid Input!\n");
				} while(nConfirm != 1 && nConfirm != 2); //Loop statement if nConfirm is neither 1 nor 2
					
				//Execute this statement if user chose to delete
				if(nConfirm == 1)
				{
       				/* For loop statement to adjust the existing records after deletion of the chosen record
					Statement 1: Initialize i to the index of the deleted record (so loop only affects the phrases listed AFTER deleted record)
					Statement 2: Loop statement as long as i is less than the number of existing phrases
					Statement 3: Post-increment i*/
       				for(i = nIndex; i < nPhraseCount; i++)
       				{
       					ExistRecords[i] = ExistRecords[i + 1]; //Shift the next record to the current index
       					if(ExistRecords[i].ID > 0) //Decrement ID number only if it is greater than 0.
       						ExistRecords[i].ID--;
					}
					
					//Clear screen
       				system("cls");
       				printf("Record deleted!\n\n\n");
					
					//Display records again in tabular format
					for(i = 0; i < nSize; i++)
					{
						if(ExistRecords[i].ID != 0)
						{	
							if(i == 0) //Only display header at first loop
								DisplayRecord(1, ExistRecords[i]);
							else
								DisplayRecord(0, ExistRecords[i]);
						}
					}
					
					sleep(1);//Pause for 1 second
					printf("\n------------------------------------------------------------------\n");
					printf("Continue Deleting [1]\n");
					printf("Back to Main Menu [2]\n");
					printf("------------------------------------------------------------------\n");
					 
					do //Execute this at least once
					{
						printf("Enter: ");
						scanf("%1d", &nBack); //Ask user input if user want to contiue deleting
						//If nBack is neither of the choices, display message
						if (nBack != 1 && nBack != 2) 
							printf("Invalid input!\n");
					} while (nBack != 1 && nBack != 2); //loop this only if nBack is invalid
					
					system("cls"); //clear screen
				}
				else //If user input 0, clear screen and set nBack to 1 to come back to the record selection
				{
					system("cls"); 
					nBack = 1;
				}
			}
			else //If user input 0, clear screen and set nBack to 2 to prevent the loop from executing again (and to go back to manage data menu)
			{
				system("cls");
				nBack = 2;
			}
		}
		else //If there are no records found, execute this statement
		{
			printf("No records found! ");
			EnterToContinue(1); //continue prompt
			nBack = 2; //Set nBack to 2 to prevent the loop
		}
	} while(nBack == 1); //Loop as long as nBack is equal to 1.
	
	*nSelect = 0; //Set nSelect to 0 to go back to Manage Data Menu.
}

/* ManageData executes the Manage Data Menu.
@param nReturn - indicates if the user wants to return to the Main Menu
@param *ExistRecords - pointer to a structure array containing all the records.

Pre-condition: 
- nReturn is an integer greater than 0.
*/
void 
ManageData(int * nReturn, 
		   struct RecordTag *ExistRecords)
{
	int nMainMenu; //Declare variable for indicator if user want to go back to main menu
	int nSelect; //Declare variable for user selection indicator
	char strPassword[20] = "test"; //Declare variable for the password. Set password to the following string.
	
	//Execute this statement at least once
	do
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
				printf("[5] Return to Main Menu\n");
				printf("------------------------------------------------------------------\n");
				printf("Enter: ");
				scanf("%1d", &nSelect); //Ask for user selection
				
				switch(nSelect) //Switch case for the different selections
				{
					case 1: //If user chooses to add record:
						system("cls"); //clear screen
						AddRecord(ExistRecords, 100, &nSelect); //Function call AddRecord()
						break;
					case 2: //If user chooses to edit record:
						system("cls"); //clear screen
						EditRecord(ExistRecords, 100, &nSelect); //Function call EditRecord()
						break;
					case 3: //If user chooses to delete record:
						system("cls"); //clear screen
						DeleteRecord(ExistRecords, 100, &nSelect); //Function call DeleteRecord()
						break;
					case 4: //If user chooses to import data:
						printf("STILL IN PROGRESS!!!\n");
						EnterToContinue(1);
						nMainMenu = 2;
						break;
					case 5: //If user chooses to return to main menu
						nMainMenu = 2; //Set nMainMenu to 2 to prevent loop AND return to main menu
						system("cls"); //clear screen
						break;
					default: //If user chooses neither of the choices
						printf("Invalid input! "); 
						EnterToContinue(1); //continue prompt
						break;
				}
			} while(nSelect != 1 && nSelect != 2 && nSelect != 3 && nSelect != 4 && nSelect != 5); //Loop statement only if the input is invalid.
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
				scanf("%1d", &nMainMenu); //Enter user's selection if they want to return to main menu or not
				system("cls"); //clear screen
				
				if(nMainMenu != 1 && nMainMenu != 2) //Execute this statement if input is neither 1 nor 2
				{
					printf("Invalid Input!\n");
					sleep(1);
				}
			} while (nMainMenu != 1 && nMainMenu != 2); //Only loop this statement if user input is invalid.
		}
	} while(nMainMenu != 2); //Loop this statement if user chooses to enter the password again.
	
	*nReturn = nMainMenu; //Set the value of nMainMenu to nReturn to go back to the Main Menu.
}