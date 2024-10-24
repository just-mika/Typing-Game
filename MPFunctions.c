#include <stdio.h>
#include <string.h>
#include <time.h>
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

/* changePassword allows user to change the set password.
@param *strPassword - pointer to a string that contains the password input
@param *nSelect - pointer to the variable that indicates the user selection from Manage Data Menu. Used to go back to said menu.
Pre-condition: 
- strPassword only contains letters, numbers, or symbols
- nSelect is 6
*/
void
changePassword(char * strPassword, int *nSelect)
{
	int nConfirm, nBack = 1;
	String255 strInput;
	
	do
	{
		system("cls");
		printf("CHANGE PASSWORD\n");
		printf("-----------------\n\n");
		printf("Enter old password\n\n");
		if(GetPassword(strPassword)) 
		{
			printf("\nCorrect password! ");
			sleep(1); //Pause for 1 second
			do
			{
				system("cls"); //Clear screen
				printf("CHANGE PASSWORD\n");
				printf("-----------------\n\n");
				printf("Enter new password (Enter 0 to go back to menu): ");
				scanf(" %255[^\n]*c", strInput);
				    
			    if(strcmp(strInput, "0") != 0) 
				{
			    	do //Execute this statement at least once
					{
						system("cls"); //Clear screen
						printf("Are you sure you want to change password from %s to %s?\n\n", strPassword, strInput); //Display confirmation message
						printf("\n------------------------------------------------------------------\n");
						printf("Yes [1]\n");
						printf("No [2]\n");
						printf("------------------------------------------------------------------\n");
					
						printf("Enter: ");
						scanf("%1d", &nConfirm); //Ask user input for their selection
						
						//Execute this statement if nConfirm is neither 1 nor 2
						if(nConfirm != 1 && nConfirm != 2)
						{
							printf("Invalid Input!\n");
							sleep(1);
						}
					} while(nConfirm != 1 && nConfirm != 2); //Loop statement if nConfirm is neither 1 nor 2
					
					if(nConfirm == 1) {
						system("cls");
						strcpy(strPassword, strInput);
						printf("Password changed successfully!\n\n\n");
						EnterToContinue(1);
						nBack = 2;
					}
				}
				else
				{
					nBack = 2;
					system("cls"); //Clear screen
				}
			} while (nBack == 1);
		}
		else 
		{
			printf("\nWrong password!\n");
			sleep(1); //Pause for 1 second
			printf("------------------------------------------------------------------\n");
			printf("Enter password again [1]\n");
			printf("Back to Manage Data Menu [2]\n");
			printf("------------------------------------------------------------------\n");
			do //Execute this statement at least once
			{
				printf("Enter: ");
				scanf("%1d", &nBack); //Enter user's selection if they want to return to main menu or not
				
				if(nBack != 1 && nBack != 2) //Execute this statement if input is neither 1 nor 2
				{
					printf("Invalid Input!\n");
					sleep(1);
				}
			} while (nBack != 1 && nBack != 2); //Only loop this statement if user input is invalid.
			system("cls"); //clear screen
		}
	} while(nBack == 1);
	
	
	*nSelect = 0;
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
	String255 strInput;     // Declare strInput for the user's password input with max of 30 characters.
	
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
	        if (i < 255 && strInput[i] != 13) 
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

//DisplayHeader displays the header of the table.
void
DisplayHeader()
{
	printf("=----------------------------------------------------------------------------------------------------------------------------------------------------=\n");
	printf("  ID  |   LEVEL   |  CHAR COUNT  |  PHRASE\n");
	printf("=----------------------------------------------------------------------------------------------------------------------------------------------------=\n");
}

//DisplayRecord displays one existing record
void
DisplayRecord(struct RecordTag ExistRecord)
{
    printf(" %3d  |", ExistRecord.ID); //Display the ID number.
	printf("   %3s", ExistRecord.Level); //Display phrase level.
	if(strcmp(ExistRecord.Level, "medium") == 0) //Execute this statement only if level is medium. This is for consistent spacing.
		printf("  |");
	else
		printf("    |");
	printf(" %6d       |", ExistRecord.charCount); //Display phrase's character count.
	printf("  %s\n", ExistRecord.Phrase); //Display the phrase itself.
    printf("=----------------------------------------------------------------------------------------------------------------------------------------------------=\n");
}

//DisplayRecordTable displays multiple records depending on the phrase count.
void 
DisplayRecordTable(struct RecordTag *ExistRecords,
					int nPhraseCount)
{
	int i;
	
	/*For loop to display the existing records in a tabular format.
	Statement 1: Initialize i to 0
	Statement 2: Loop statement as long as i is less than nPhraseCount
	Statement 3: Post-increment i
	*/
	for(i = 0; i < nPhraseCount; i++)
	{
		//Function call DisplayRecord to display the current record. 
		DisplayRecord(ExistRecords[i]);
	}
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

/* CountPhrase counts the number of existing phrases in the records.
@param *ExistRecords - pointer to a structure array containing all the records.
@param nSize - indicates the size of the structure array.
@return nPhraseCount which indicates the total number of existing phrases in the records.
Pre-condition: 
- nSize is an integer greater than 0.
*/
int
CountPhrase(struct RecordTag *ExistRecords,
			int nSize)
{
	int i; //Declare index variable
	int nPhraseCount = 0; //Declare variable for phrase count and set to 0 to prevent error.
	
	//For loop statement to check how many phrases exist already.
	for(i = 0; i < nSize; i++)
	{
		if(ExistRecords[i].ID > 0) //Execute statement if there is a phrase in the current index of ExistRecords.
			nPhraseCount++; //Increment phrase count
	}
	
	return nPhraseCount; //return the resulting value.
}

/* FindRecord finds for the index of an existing record with given input from the user.
@param *ExistRecords - pointer to a structure array containing all the records.
@param nPhraseCount - the number of existing phrases in the records.
@param nRecordSelect - the ID number the user inputed.
@return nIndex which indicates the index of the desired record. (-1 if the record does not exist)
Pre-condition: 
- nPhraseCount and nRecordSelect are both positive integers
- At least 1 record exists in ExistRecords
- nRecordSelect is greater than 0
*/
int
FindRecord(struct RecordTag *ExistRecords,
			int nPhraseCount, 
			int nRecordSelect)
{
	int i, nIndex;
	
	nIndex = -1; //Set to -1 to indicate the record has not yet been found.

	/*For loop to search for the record 
	Statement 1: Initialize i to 0
	Statement 2: Loop statement as long as i is less than nSize
	Statement 3: Post-increment i
	*/
	for(i = 0; i < nPhraseCount && nIndex == -1; i++)
	{
		if(ExistRecords[i].ID == nRecordSelect){ //Set nIndex to current value of i the current index ID matches the user input
			nIndex = i;
			break;
		}
	}
	
	return nIndex; //Return resulting index.
}

/* FindExistingPhrase checks if the input phrase already exists in the records.
@param *ExistRecords - pointer to a structure array containing all the records.
@param nPhraseCount - the number of existing phrases in the records.
@param strPhrase - the phrase the user inputed.
@return nIndex which indicates the index of the identical phrase (-1 if there is no identical phrases)
Pre-condition: 
- nPhraseCount is a positive integer
- At least 1 record exists in ExistRecords
- strPhrase is a string that contains characters and symbols
*/
int
FindExistingPhrase(struct RecordTag *ExistRecords,
					int nPhraseCount, 
					String100 strPhrase)
{
	int i, nIndex = -1;
	/*For loop statement to check if the phrase entered already exists in the records.
	Statement 1: Initialize index to 0
	Statement 2: Continue loop if index is less than the array size AND if nIndex is not yet found
	Statement 3: Post-increment index
	*/
	for(i = 0; i < nPhraseCount && nIndex == -1; i++)
	{
		if(strcmp(strPhrase, ExistRecords[i].Phrase) == 0) //Execute statement if the inputed phrase already exists in the records.
		{
			nIndex = i; //If found, set nIndex to the current index.
			break;
		}
	}
	
	return nIndex; //Return the resulting value of nIndex.
}

/* AddRecord allows the admin to add a phrase to the records.
@param *ExistRecords - pointer to a structure array containing all the records.
@param nSize - indicates the size of the structure array.
@param *nSelect - pointer to the variable that indicates the user selection from Manage Data Menu. Used to go back to said menu.
Pre-condition: 
- nSize is an integer greater than 0.
- nSelect is 1
*/
void
AddRecord(struct RecordTag *ExistRecords, 
		  int nSize, 
		  int *nSelect)
{
	String100 strPhrase; //Declare user's phrase input. Data type is character array with size 101.
	int nIndex; //Declare index of the identical phrase(nIndex)
	int nPhraseCount = CountPhrase(ExistRecords, nSize); //Declare integer variable for the number of existing phrases in the records. Call function CountPhrase() to set its value.
	int nNextPhrase; //Declare integer variable for the index of the added phrase.
	
	printf("ADD A RECORD\n");
	printf("-----------------\n");
	
	//Execute this statement only if the number of phrases is less than the size. 
	if(nPhraseCount < nSize)
	{
		printf("Enter a phrase up to 100 characters (type /back to go back to menu): ");
		scanf(" %100[^\n]*c", strPhrase); //Input string. Only read up to 100 characters AND stop inputting after pressing enter.
	
		if(strcmp(strPhrase, "/back") != 0) //Execute statement if phrase input isnt "/back" (command to go back to Manage Data Main Menu)
		{
			nIndex = FindExistingPhrase(ExistRecords, nPhraseCount, strPhrase); //Function call FindExistingPhrase to check if input phrase exists in the records.
			
			if(nIndex != -1)
			{
				DisplayHeader(); //Display header
				DisplayRecord(ExistRecords[nIndex]); //Function call DisplayRecord to display the said existing phrase
				printf("Phrase already exists! "); 
				EnterToContinue(1); //Function call EnterToContinue for continue prompt.
				
				*nSelect = 0; //Set nSelect to 0 to go back to Manage Data Menu.
			}
			//Execute statement if the entered phrase does not exist yet in the records
			else
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
				
				DisplayHeader(); //Display header
				DisplayRecord(ExistRecords[nNextPhrase]); //Display the added record
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
	else
	{
		printf("Maximum amount of records already exists! ");
		EnterToContinue(1); //continue pprompt
		*nSelect = 0; //Set nSelect to 0 to go back to Manage Data Menu
	}
}

/* EditRecord allows the admin to edit existing records.
@param *ExistRecords - pointer to a structure array containing all the records.
@param nSize - indicates the size of the structure array.
@param *nSelect - pointer to the variable that indicates the user selection from Manage Data Menu. Used to go back to said menu.
Pre-condition: 
- nSize is an integer greater than 0.
- nSelect is 2
*/
void
EditRecord(struct RecordTag *ExistRecords, 
		   int nSize, 
		   int *nSelect)
{
	String100 strPhrase; //Declare user's phrase input. Data type is character array with size 101.
	int nRecordSelect; //Declare variable for the record selection (nRecordSelect)
	int nIndex, nBack = 1; //Declare the index of the selected record (nIndex) and the indicator to go back to edit more records (nBack). Set this to 1.
	int nPhraseCount = CountPhrase(ExistRecords, nSize); //Declare integer variable for the number of existing phrases in the records. Call function CountPhrase() to set its value.
	int nFound; //Declare variable for the no. of phrases in the records (nPhraseCount) and indicator if an identical phrase is found (nFound).

	do //Execute this statement at least once
	{
		printf("EDIT RECORD\n");
		printf("-----------------\n\n");
		
		if(nPhraseCount != 0) //Execute this statement if there ARE existing records
		{
			do //Execute this statement at least once
			{
				DisplayHeader(); //Display header
				DisplayRecordTable(ExistRecords, nPhraseCount); //Function call DisplayRecordTable to display multiple records
			
				printf("\nSelect ID number (Enter 0 to go back to menu): ");
				scanf("%d", &nRecordSelect); //Ask for admin input for the ID number of the desired record to edit.
				
				//Execute this statement only if selected ID number is NOT 0 (an input of 0 will cause to return to Manage Data Menu)
				if(nRecordSelect > 0)
				{
					nIndex = FindRecord(ExistRecords, nPhraseCount, nRecordSelect); //Function call FindRecord to look for the index of said record.
					
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
					printf("Enter a phrase up to 100 characters (type /back to go back): ");
					scanf(" %100[^\n]*c", strPhrase); //Input string. Only read up to 100 characters AND stop inputting after pressing enter.
					
					nFound = FindExistingPhrase(ExistRecords, nPhraseCount, strPhrase); //Function call FindExistingPhrase to check if input phrase exists in the records.
					
					if(nFound != -1)
						printf("\nPhrase already exists! It's in ID Number %d.\n", ExistRecords[nFound].ID); //display the phrase's ID number.
				} while(nFound != -1); //Loop if there is an identical phrase found.
				
				if(strcmp(strPhrase, "/back") != 0)
				{
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
					DisplayHeader();
					DisplayRecord(ExistRecords[nIndex]);
					
					sleep(1); //Pause for 1 second
					printf("\n------------------------------------------------------------------\n");
					printf("Continue Editing [1]\n");
					printf("Back to Manage Data Menu [2]\n");
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
				else
				{
					system("cls");
					nBack = 1; //set nBack to 1 to return to the records list
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

/* DeleteRecord allows the admin to delete a phrase to the records.
@param *ExistRecords - pointer to a structure array containing all the records.
@param nSize - indicates the size of the structure array.
@param *nSelect - pointer to the variable that indicates the user selection from Manage Data Menu. Used to go back to said menu.
Pre-condition: 
- nSize is an integer greater than 0.
- nSelect is 3
*/
void
DeleteRecord(struct RecordTag *ExistRecords, 
			 int nSize, 
			 int *nSelect)
{
	int i, nRecordSelect, nConfirm; //Declare index variable, variable for the record selection (nRecordSelect), and variable for the confirmation option (nConfirm).
	int nIndex, nBack = 1; //Declare the index of the selected record (nIndex) and indicator to go back to edit more records (nBack). Set this to 1.
	int nPhraseCount = CountPhrase(ExistRecords, nSize); //Declare integer variable for the number of existing phrases in the records. Call function CountPhrase() to set its value.
	
	//Execute this statement at least once.
	do
	{
		printf("DELETE RECORD\n");
		printf("-----------------\n\n");
		
		if(nPhraseCount != 0) //Execute this statement if there ARE existing records
		{
			do //Execute this statement at least once
			{
				DisplayHeader(); //Display header
				DisplayRecordTable(ExistRecords, nPhraseCount); //Function call DisplayRecordTable to display multiple records
			
				printf("\nSelect ID number (Enter 0 to go back to menu): ");
				scanf("%d", &nRecordSelect); //Ask for admin input for the ID number of the desired record to delete.
				
				if(nRecordSelect > 0) //Execute this statement only if selected ID number is NOT 0 (an input of 0 will cause to return to Manage Data Menu)
				{
					nIndex = FindRecord(ExistRecords, nPhraseCount, nRecordSelect); //Function call FindRecord to look for the index of said record.
					
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
					DisplayHeader(); //Display header
					DisplayRecord(ExistRecords[nIndex]); //Display the record that admin chose to delete
					printf("\n------------------------------------------------------------------\n");
					printf("Yes [1]\n");
					printf("No [2]\n");
					printf("------------------------------------------------------------------\n");
				
					printf("Enter: ");
					scanf("%1d", &nConfirm); //Ask user input for their selection
					
					//Execute this statement if nConfirm is neither 1 nor 2
					if(nConfirm != 1 && nConfirm != 2)
					{
						printf("Invalid Input!\n");
						sleep(1);
					}
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
					nPhraseCount = CountPhrase(ExistRecords, nSize); //Update the number of phrases
					//Clear screen
       				system("cls");
       				printf("Record deleted!\n\n\n");

					//Display records again in tabular format only if there are still existing phrases in the records.
					if(nPhraseCount > 0)
					{
						DisplayHeader();
						DisplayRecordTable(ExistRecords, nPhraseCount);
					}
					
					sleep(1);//Pause for 1 second
					printf("\n------------------------------------------------------------------\n");
					printf("Continue Deleting [1]\n");
					printf("Back to Manage Data Menu [2]\n");
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

/* ImportData allows the admin to import existing phrase data in a text file to use for the game.
@param *ExistRecords - pointer to a structure array containing all the records.
@param nSize - indicates the size of the structure array.
@param *nSelect - pointer to the variable that indicates the user selection from Manage Data Menu. Used to go back to said menu. 
Pre-condition: 
- nSize is an integer greater than 0.
- nSelect is 4
*/
void 
ImportData(struct RecordTag *ExistRecords, 
			int nSize, 
			int *nSelect)
{
	int i, nNew = 0, j, nPhraseCount; //declare variables for the index (i, j), the new data count (nNew), and the current number of phrases in the records (nPhraseCount)
	int nFound, nCounter = 0, nDontAdd[nSize]; //declare a variable for the index of the found duplicate phrase (nFound), the counter for duplicate phrases (nCounter), and the array of indices containing the duplicate phrases.
	struct RecordTag temp; //declare temporary record to place the read data into to check the phrase before placing it in the records.
	String255 strFileName; //declare the variable for the input file name 
	FILE *fpImport; //declare the pointer to the file
	
	nPhraseCount = CountPhrase(ExistRecords, nSize);
	
	printf("IMPORT DATA\n");
	printf("-----------------\n\n");
	
	//Execute this statement if there are already maximum amount of records.
	if(nPhraseCount >= nSize)
	{
		printf("Maximum amount of records already exists! ");
		EnterToContinue(1); //continue pprompt
	}
	else //otherwise:
	{
		printf("Enter file name to import (type /back to go to back to menu): ");
		scanf(" %255[^\n]*c", strFileName); //ask user for file name (no file extension needed)
		//clear screen and go back to Manage Data menu if user inputs "/back"
		if(strcmp(strFileName, "/back") == 0)
		{
			system("cls");
	 		*nSelect = 0;
	 	}
	 	else //otherwise:
	 	{
		 	strcat(strFileName, ".txt"); //append ".txt" in file name to add file extension
			
			fpImport = fopen(strFileName, "r"); //open file using the input file name and set mode to read
			//if file is found, execute:
			if(fpImport != NULL)
			{
				//Loop this while there is an existing record in the text file AND max phrase count hasnt reached.
			 	while (fscanf(fpImport, "%d\n", &temp.ID) == 1 && nPhraseCount < nSize)
			 	{	
			 		fscanf(fpImport, "%[^\n]*c\n", temp.Level); //get the level in the file and place it in the temp record
			 		fscanf(fpImport, "%d\n", &temp.charCount); //get the character count in the file and place it in the temp record
			 		fscanf(fpImport, "%[^\n]*c\n\n", temp.Phrase); //get the phrase in the file and place it in the temp record
			 		
			 		nFound = FindExistingPhrase(ExistRecords, nPhraseCount, temp.Phrase); //check if the current record read is already in the existing records.
					
					if(nFound != -1) //if phrase already exists:
					{
						nDontAdd[nCounter] = nFound; //Add its index to the array
						nCounter++; //increment the counter
					}
					else //otherwise:
					{
						ExistRecords[nPhraseCount] = temp; //add the read record in the Existing records in the index after the previous record
						ExistRecords[nPhraseCount].ID = nPhraseCount + 1; //set the ID of the read record to the next ID number after the previous record
						nPhraseCount++; //increment to indicate there is a new phrase added
						nNew++; //increment to indicate there is a new phrase
					}
				}
				//if there is at least one phrase added
				if(nNew > 0)
				{
					nPhraseCount = CountPhrase(ExistRecords, nSize); //call function CountPhrase() to recount the number of existing phrases
					DisplayHeader(); //display header
					//for loop to display all added phrases
					//start the loop by setting i to number of all phrases subtracter by the number of new phrases.
					for(i = nPhraseCount - nNew; i < nPhraseCount; i++)
					{
						DisplayRecord(ExistRecords[i]); //display the record of the added phrases
					}
					printf("\nData successfully imported! "); //display message
				}
				else //if there are no new data added (for instance, if all records in the text file are already existing), display message
					printf("Data unsuccessfully imported. ");
				
				if(nCounter > 0) // If there is at least 1 duplicate phrase, execute:
				{
					sleep(1);
					printf("The ff phrases in the file are already found in the records:\n");
					DisplayHeader();
					//for loop to display all of the records already existing in the current record.
					for(j = 0; j < nCounter; j++)
					{
						DisplayRecord(ExistRecords[nDontAdd[j]]);
					}
					printf("\n");
				}
				EnterToContinue(1);
				fclose(fpImport); //close file
			}
			else //if file is not found, display message and go back.
			{
				printf("File not found! ");
				EnterToContinue(1);
			}	
		}

	}
	
	*nSelect = 0; //Set nSelect to 0 to go back to Manage Data Menu
}

/* ExportData allows the admin to export the existing phrase data in the game into a file to save the data
@param *ExistRecords - pointer to a structure array containing all the records.
@param nSize - indicates the size of the structure array.
@param *nSelect - pointer to the variable that indicates the user selection from Manage Data Menu. Used to go back to said menu. 
Pre-condition: 
- nSize is an integer greater than 0.
- nSelect is 5
*/
void 
ExportData(struct RecordTag *ExistRecords, 
			int nSize, 
			int *nSelect)
 {
 	//declare variables for index (i), the confirmation option (nConfirm) and number of phrases (nPhraseCount). Call function CountPhrase() to count the number of existing phrases
 	int i, nConfirm, nPhraseCount = CountPhrase(ExistRecords, nSize);
 	struct RecordTag temp[nSize]; //declare structure variable to show the records in the existing file name.
 	String255 strFileName; //declare string variable for the file name input.
 	
 	FILE *fpExport; //declare file pointer for the export file
 	
 	printf("EXPORT DATA\n");
	printf("-----------------\n\n");
		
	if(nPhraseCount != 0) //Execute this statement if there ARE existing records
	{
		do
		{
			printf("Enter the filename for the export file (type /back to go to back to menu): ");
			scanf(" %255[^\n]*c", strFileName); //ask user for file name (no file extension needed)
			//clear screen and go back to Manage Data menu if user inputs "/back"
			if(strcmp(strFileName, "/back") == 0)
			{
				system("cls");
		 		nConfirm = 1;
		 	}
		 	else //otherwise:
		 	{
		 		strcat(strFileName, ".txt"); //append ".txt" in file name to add file extension
		 		fpExport = fopen(strFileName, "r"); //open file using the input file name and set mode to write
		 		//if file is already found:
		 		if(fpExport != NULL)
		 		{
		 			i = 0; //set i to 0 to start the counter
		 			initializeRecord(temp, nSize); //initialize the temporary records
		 			system("cls"); //Clear screen
		 			while (fscanf(fpExport, "%d\n", &temp[i].ID) == 1 && i < nSize)
			 		{	
				 		fscanf(fpExport, "%[^\n]*c\n", temp[i].Level); //get the level in the file and place it in the temp record
				 		fscanf(fpExport, "%d\n", &temp[i].charCount); //get the character count in the file and place it in the temp record
				 		fscanf(fpExport, "%[^\n]*c\n\n", temp[i].Phrase); //get the phrase in the file and place it in the temp record
				 		i++; //increment i to indicate a record has been added
				 	}
				 	
				 	if(i > 0) //if at least 1 record is found in the file
					{
						printf("Are you sure you want to overwrite this existing file?\n\n"); //Display confirmation message
						DisplayHeader(); //Display header
						DisplayRecordTable(temp, i); //Display the records in the existing file name
						printf("\n------------------------------------------------------------------\n");
						printf("Yes [1]\n");
						printf("No [2]\n");
						printf("------------------------------------------------------------------\n");
						do //Execute this statement at least once
						{
							printf("Enter: ");
							scanf("%1d", &nConfirm); //Ask user input for their selection
							
							//Execute this statement if nConfirm is neither 1 nor 2
							if(nConfirm != 1 && nConfirm != 2)
								printf("Invalid Input!\n");
						} while(nConfirm != 1 && nConfirm != 2); //Loop statement if nConfirm is neither 1 nor 2
					} 
					fclose(fpExport); //close file to change mode later
				}
				else //if file does not exist yet
				{
					nConfirm = 1; //set nConfirm to 1 to execute exporting 
		 			fclose(fpExport); //close file to change mode later
				}
				//execute if nConfirm is 1
		 		if(nConfirm == 1)
		 		{
		 			fpExport = fopen(strFileName, "w"); //open file again to change to write mode
		 			//for loop to write the existing phrases in a text file
			 		for(i = 0; i < nPhraseCount; i++) 
				 	{
				 		fprintf(fpExport, "%d\n", ExistRecords[i].ID);
				 		fprintf(fpExport, "%s\n", ExistRecords[i].Level);
				 		fprintf(fpExport, "%d\n", ExistRecords[i].charCount);
				 		fprintf(fpExport, "%s\n\n", ExistRecords[i].Phrase);
					}
					printf("Data successfully exported! "); //display message
					EnterToContinue(1); //continue prompt
					fclose(fpExport); //close file
				}
				else //if user does not want to overwrite the record: clear screen and display title again
				{
					system("cls");
					printf("EXPORT DATA\n");
					printf("-----------------\n\n");
				}
			}
		} while (nConfirm == 2); //loop this until user exports a record
	}
	else //If there are no records found, execute this statement
	{
		printf("No records found! ");
		EnterToContinue(1); //continue prompt
	}

	*nSelect = 0; //set nSelect to 0 to go back to the menu.
 }

/* getRandomPhrase generates a random number from 0 to the number of total phrases in that level and returns the index of the chosen phrase.
@param *nLevelIndex - the address of the array containing all of the indices of the phrases in a specific level.
@param nLevelCount - the number of total phrases in a specific level.
@return nLevelIndex[nIndex] which is the index of the chosen phrase
Pre-condition: 
- There are at least 3 (easy), 2 (medium), or 5 (hard) elements in nLevelIndex
- nLevelCount is at least 3 (easy), 2 (medium), or 5 (hard)
*/
int
getRandomPhrase(int *nLevelIndex, 
				int nLevelCount)
{
	int nIndex; //declare variable for an index
	
	//srand() function is used to set the starting point for the rand() function.
	//time(NULL) function is used as the seed so that the random number generated isn't the same every run.
	srand(time(NULL));
	
	// Set nIndex as a random number generated using the rand() function, get its modulo by nLevelCount
	// so that the returned number will only range from 0 to nLevelCount - 1
	nIndex = (rand() % nLevelCount); 
	
	return nLevelIndex[nIndex]; //choose a phrase within the array using nIndex and return the index of the chosen phrase.
}

/* CountLevelPhases places all phrases's indices from a specific level in a single array and returns the total number of phrases in that level.
returns the total number of phrases in a specific level.
@param *ExistRecords - pointer to a structure array containing all the records.
@param nPhraseCount - total number of phrases in the records
@param nLevel - Specifies which level is to be checked. (1 for easy, 2 for medium, 3 for hard)
@param *nLevelIndex - pointer to an array for the indices 
@return the total number of phrases in a given level.
Pre-condition: 
- There is at least 1 existing record in *ExistRecords
- nPhraseCount is at least 1
- nLevel can only be either 1, 2, or 3
*/
int
CountLevelPhrases(struct RecordTag *ExistRecords, 
					int nPhraseCount, 
					int nLevel, 
					int *nLevelIndex)
{
	int i; //declare index variable
	int nLevelPhrases = 0; //declare counter for the amount of phrases in a level. Set to 0
	char difficulty[7]= "";
	
	if(nLevel == 1) //Only execute if chosen level is 1 (easy)
	{
		strcat(difficulty, "easy");
	}
	else if(nLevel == 2) //Only execute if chosen level is 2 (medium)
	{
		strcat(difficulty, "medium");
	}
	else if(nLevel == 3) //Only execute if chosen level is 3 (hard)
	{
		strcat(difficulty, "hard");
	}
	//for loop to find the prhases in a specific level
	for(i = 0; i < nPhraseCount; i++)
	{
		if(strcmp(ExistRecords[i].Level, difficulty) == 0)
		{
			nLevelIndex[nLevelPhrases] = i; //place the index of the phrase in the array
			nLevelPhrases++; //increment to count
		}
	}
	return nLevelPhrases; //return the resulting count of the phrases in the level.
}

/* LoadScoreFile loads the score.txt file (Containing all previous players and their score) and returns the total number of players in the records.
@param *PlayerScores - structure variable that contains a string (player name) and integer (score).
@param nSize - the size of the array or the max amount of records allowed in the PlayerScores array
@returns nPlayer which is the total number of players in the records (-1 if the file fails to load)
Pre-condition:
- nSize is a positive integer
*/
int 
LoadScoreFile(struct ScoreTag *PlayerScores, 
				int nSize)
{
	int nPlayerCount = 0; //Declare variable for the number of existing player records
	FILE *fpScores; //Declare file pointer to load the file
	
	fpScores = fopen("score.txt", "r"); //open score.txt file in read mode
	if(fpScores == NULL) //return -1 if file not found.
		return -1;
	else
	{
		while(!feof(fpScores) && nPlayerCount < nSize) //loop while end of file has not reached yet.
	 	{	
	 		//only execute if player name is successfully read
	 		if(fscanf(fpScores, "%10[^\n]*c\n", PlayerScores[nPlayerCount].Name) == 1)
			{
		 		fscanf(fpScores, "%d\n", &PlayerScores[nPlayerCount].Score); //get player score
		 		nPlayerCount++; //increment player count
			}
	 	}
	 	fclose(fpScores); //close file
	 	return nPlayerCount; //return resulting number of player count
 	}	
}

/* compareScores compares scores of two players.
@param *a - pointer to the first player's score record
@param *b - pointer to the second player's score record
@returns a negative integer if first player's score is less than second players, zero if their scores are equal,
		 a positive integer otherwise.
Pre-conditions:
- a and b must be valid ScoreTag pointers
- a and b's scores must be a positive integer
*/
int compareScores(const void* a, const void* b) {
    struct ScoreTag* scoreA = (struct ScoreTag*)a;
    struct ScoreTag* scoreB = (struct ScoreTag*)b;
    
    // Sort in descending order
    return scoreB->Score - scoreA->Score; // Negative if scoreA < scoreB
}

/* EndGame displays the player's score after the game and updates the score.txt file accordingly.
@param *PlayerScores - structure variable that contains a string (player name) and integer (score).
@param strPlayerName - string containing the current players name
@param nPlayerScore - the player's total accumulated score
@param nPlayerCount - the total number of players in the records
@param nSize - the size of the array or the max amount of records allowed in the PlayerScores array
Pre-conditions:
- strPlayerName contains at most 10 characters
- nPlayerScore is a nonnegative integer
- nPlayerCount is a nonnegative integer
- nSize is a positive integer
- "score.txt" file exists
*/
void
EndGame(struct ScoreTag *PlayerScores, 
		String10 strPlayerName, 
		int nPlayerScore, 
		int nPlayerCount,
		int nSize)
{
	int i, nTop = 0, nLow = 0, nPlayerIndex = -1; //declare index variable (i), index of the current top score (nTop), index of the current lowest score (nLow), and the index of the player found in the records (nPlayerIndex)
	FILE *fpScores; //declare file pointer to access the scores file
	
	printf("\n-------------------------------------\n");
	printf("GAME OVER!\n\n");
	sleep(1);
	printf("RESULTS:\n");
	printf("Player Name: %s\n", strPlayerName); //display player's name
	printf("Final Score: %d\n\n", nPlayerScore); //display player's score
	sleep(1);
 	
 	//for loop to find if the player's name is already in the records.
	for(i = 0; i < nPlayerCount; i++)
	{
		if(strcmp(PlayerScores[i].Name, strPlayerName) == 0)
			nPlayerIndex = i; //set nPlayerIndex to the current value if i
	}
	
	if(nPlayerScore <= 2) //display message if player score is less than or equal to 2
		printf("Better luck next time! ");
	else if (nPlayerScore <= 10) //display message if player score is less than or equal to 10
		printf("Nice job! ");
	else if (nPlayerScore > 10) //display message if player score is more than 10
		printf("Congratulations! ");
		
	//for loop to find the player with high score
	for(i = 0; i < nPlayerCount; i++)
	{
		//set top score index to i if the current top score is less than the current index's score
		if(PlayerScores[nTop].Score < PlayerScores[i].Score)
			nTop = i;
		//only do this if there are max records in the scores record
		if(nPlayerCount == nSize)
		{
			//set low score index to i if current low score is greater than current index's score
			if(PlayerScores[nLow].Score > PlayerScores[i].Score)
				nLow = i;
		}
	}
	
	//if the current player's score is greater than the recorded high score:
	if(nPlayerScore > PlayerScores[nTop].Score)
	{
		sleep(1);
		//display message and the previous high score holder.
		printf("You beat %s's high score of %d! ", PlayerScores[nTop].Name, PlayerScores[nTop].Score);
	}

	//If the current player's name is found in the records:
	if(nPlayerIndex != -1)
	{
		//If player's current score is greater than their previous score:
		if(nPlayerScore > PlayerScores[nPlayerIndex].Score)
			PlayerScores[nPlayerIndex].Score = nPlayerScore; //update their previous score to current score in the records.
		
	}
	else //otherwise, add their name and score in the record
	{
		//add name to next record if there are still spaces in the records
		if(nPlayerCount < nSize)
		{
			strcpy(PlayerScores[nPlayerCount].Name, strPlayerName);
			PlayerScores[nPlayerCount].Score = nPlayerScore;
			nPlayerCount++; //increment to indicate that a new record has been added 
		}
		else if(nPlayerCount == nSize) //if there are already max records:
		{
			//if Player beats person with the lowest score, replace person with lower score's record with the current player's record
			if(nPlayerScore > PlayerScores[nLow].Score)
			{
				strcpy(PlayerScores[nLow].Name, strPlayerName);
				PlayerScores[nLow].Score = nPlayerScore;
			}
				
		}
	}
	
	fpScores = fopen("score.txt", "w"); //open score.txt file in write mode
	
	//for loop to update the contents of score.txt
	for(i = 0; i < nPlayerCount; i++)
	{
		fprintf(fpScores, "%s\n", PlayerScores[i].Name);
		fprintf(fpScores, "%d\n", PlayerScores[i].Score);
		fprintf(fpScores, "\n");
	}

	fclose(fpScores); //close file
	
	EnterToContinue(1); //continue prompt.
}

/* DisplayScores displays the player's score after the game and updates the score.txt file accordingly.
@param *PlayerScores - structure variable that contains a string (player name) and integer (score).
@param *nSelect - pointer to the variable that indicates the user selection from Play Menu. Used to go back to said menu.
@param nSize - the size of the array or the max amount of records allowed in the PlayerScores array
Pre-conditions:
- nSelect contains 2
*/
void 
DisplayScores (struct ScoreTag *PlayerScores, 
				int *nSelect, 
				int nSize)
{
	int i = 0; //declare index variable
	int nPlayerCount = LoadScoreFile(PlayerScores, nSize); //declare variable for the player count in the score records. Call function LoadScoreFile() to get the value
	
	printf("LEADERBOARD\n");
	printf("-------------------------------------\n\n");
	if(nPlayerCount == -1) //Execute if the score.txt file is not found.
	{
		printf("Score file not found! ");
		sleep(1);
		printf("Create \"score.txt\" file and try again. ");
		EnterToContinue(1);
	}
	else //Execute if score.txt file is found
	{
		if(nPlayerCount == 0) //Execute if there are no scores recorded yet.
		{
			printf("No Player records yet! ");
			EnterToContinue(1);
		}
		else //otherwise:
		{
			//quicksort to sort player leaderboard by scores
			qsort(PlayerScores, nPlayerCount, sizeof(struct ScoreTag), compareScores);
		 	
			printf("=-------------------------------------=\n");
			printf(" RANK |   NAME   |  TOTAL SCORE \n");
			printf("=-------------------------------------=\n");
			//for loop to display the player's names and scores 
			for(i = 0; i < nPlayerCount; i++)
			{
			    printf(" %3d  |", i + 1);
				printf("%10s|", PlayerScores[i].Name);
				printf(" %3d  \n", PlayerScores[i].Score);
				printf("=-------------------------------------=\n");
			}
			printf("\n");
			EnterToContinue(1); //continue prompt
		}
	}
	*nSelect = 0; //set nSelect to 0 to go back to the Play Menu
}
 
 /* PlayGame executes the game itself.
@param *ExistRecords - pointer to a structure array containing all the records.
@param *PlayerScores - structure variable that contains a string (player name) and integer (score).
@param nSize - indicates the size of the structure array.
@param *nSelect - pointer to the variable that indicates the user selection from Play Menu. Used to go back to said menu.
Pre-condition: 
- nSelect is 1
- nSize is a positive integer
*/
void 
PlayGame(struct RecordTag *ExistRecords, 
		 struct ScoreTag *PlayerScores,
		 int nSize, 
		 int *nSelect)
{
	String10 strPlayerName; //declare string variable for the player's name
	String100 strPlayerInput; //declare string variable for the player's input
	
	int i, j = 0; //declare index variables
	int nChosenPhrase, nIndex, nDone[nSize]; //declare the index of the chosen phrase (nChosenPhrase), the phrase generated randomly (nIndex) and an array for the finished phrases' indices (nDone[])
	int nPhraseCount, nPlayerScore = 0, nPlayerLives = 3; //declare the number of phrases in records (nPhraseCount), the player's score (nPlayerScore), and the player's remaining (nPlayerLives)
	int nEasyIndex[nSize], nMediumIndex[nSize], nHardIndex[nSize]; //declare an array for the indices of the phrases based on their level
	int nEasyCount,  nMediumCount, nHardCount; //declare variables for the number of phrases within the level
	int nPlayerCount = LoadScoreFile(PlayerScores, nSize); //declare variable for the number of player records in the score.txt file. call function LoadScoreFile() to get the value.
	
	printf("TYPING GAME\n");
	printf("-------------------------------------\n\n");
	
	nPhraseCount = CountPhrase(ExistRecords, nSize); //Call function CountPhrase() to count the number of phrases currently in records
	
	//Execute this only if there are existing records
	if(nPhraseCount != 0)
	{
		if(nPlayerCount != -1) //Execute if score.txt is found
		{
			//Count the phrases belonging in each difficulty using CountLevelPhrases()
			nEasyCount = CountLevelPhrases(ExistRecords,  nPhraseCount, 1, nEasyIndex);
			nMediumCount = CountLevelPhrases(ExistRecords,  nPhraseCount, 2, nMediumIndex);
			nHardCount = CountLevelPhrases(ExistRecords,  nPhraseCount, 3, nHardIndex);
			
			//Execute this if there are enough phrases in each level (3 for easy, 2 for medium, and 5 for hard)
			if(nEasyCount >= 3 && nMediumCount >= 2 && nHardCount >= 5)
			{
				printf("Enter your name (up to 10 characters): ");
				scanf(" %10[^\n]*c", strPlayerName); //get player's name input
				
				system("cls");
				printf("TYPING GAME");
				
				//do while loop to execute the easy level
				do
				{
					printf("\n-------------------------------------\n");
					printf("\nPlayer: %s\t Lives: %d\t Score: %d\n", strPlayerName, nPlayerLives, nPlayerScore);
					sleep(1);
					printf("DIFFICULTY: EASY\n\n");
					//do while loop to choose a phrase from the records
					do
					{
						nChosenPhrase = 0; //set the chosen phrase to 0 at every loop
						nIndex = getRandomPhrase(nEasyIndex, nEasyCount); //call function getRandomPhrase() to generate a random number
						//for loop to check if the chosen index is already chosen before
						for(i = 0; i < nEasyCount && nChosenPhrase != -1; i++)
						{
							if(nDone[i] == nIndex) //if the chosen index has already been choosen before
								nChosenPhrase = -1; //set nChosenPhrase to -1
						}
						if(nChosenPhrase != -1) //if the generated index has not been found in the array
							nChosenPhrase = nIndex; //set the chosen phrase to the generated index
					} while (nChosenPhrase == -1); //loop this until a chosen phrase has been found
					
					printf("Type this phrase: \n");
					printf("%s\n", ExistRecords[nChosenPhrase].Phrase); //display chosen phrase
					printf("\nEnter: ");
					scanf(" %100[^\n]*c", strPlayerInput); //ask user to input the phrase
					
					//add up points if the user input matches perfectly with the phrase
					if(strcmp(strPlayerInput, ExistRecords[nChosenPhrase].Phrase) == 0)
					{
						printf("Correct! You earn 1 point. ");
						EnterToContinue(0);
						nPlayerScore++;
					}
					else //decrease lives if user input does not match perfectly with the prhase
					{
						printf("Wrong! You lose 1 life. ");
						EnterToContinue(0);
						nPlayerLives--;
					}
					
					nDone[j] = nChosenPhrase; //add the chosen phrase to the nDone array after each turn
					j++; //increment j to indicate an index has been added to nDone
				} while(nPlayerLives > 0 && j < 3); //loop this statement until 3 easy phrases have been finished or player loses lives
				
				if(nPlayerLives == 0) //if player has no more lives, call function EndGame() to end the game
					EndGame(PlayerScores, strPlayerName, nPlayerScore, nPlayerCount, nSize);
				else //otherwise, continue with the game.
				{
					j = 0; //reset j to 0 to reset the turn counter
					//do-while loop to execute medium level
					do
					{
						printf("\n-------------------------------------\n");
						printf("\nPlayer: %s\t Lives: %d\t Score: %d\n", strPlayerName, nPlayerLives, nPlayerScore);
						sleep(1);
						printf("DIFFICULTY: MEDIUM\n\n");
						//do while loop to choose a phrase from the records
						do
						{
							nChosenPhrase = 0; //set the chosen phrase to 0 at every loop
							nIndex = getRandomPhrase(nMediumIndex, nMediumCount);  //call function getRandomPhrase() to generate a random number
							//for loop to check if the chosen index is already chosen before	
							for(i = 0; i < nMediumCount && nChosenPhrase != -1; i++)
							{
								if(nDone[i] == nIndex)//if the chosen index has already been choosen before
									nChosenPhrase = -1; //set nChosenPhrase to -1
							}
							if(nChosenPhrase != -1) //if the generated index has not been found in the array
								nChosenPhrase = nIndex; //set the chosen phrase to the generated index
						} while (nChosenPhrase == -1); //loop this until a chosen phrase has been found
						
						printf("Type this phrase: \n");
						printf("%s\n", ExistRecords[nChosenPhrase].Phrase); //display chosen phrase
						printf("\nEnter: ");
						scanf(" %100[^\n]*c", strPlayerInput); //ask user to input the phrase
					
						//add up points if the user input matches perfectly with the phrase
						if(strcmp(strPlayerInput, ExistRecords[nChosenPhrase].Phrase) == 0)
						{
							printf("Correct! You earn 2 points. ");
							EnterToContinue(0);
							nPlayerScore += 2;
						}
						else //decrease lives if user input does not match perfectly with the phrase
						{
							printf("Wrong! You lose 1 life. ");
							EnterToContinue(0);
							nPlayerLives--;
						}
						nDone[j] = nChosenPhrase; //add the chosen phrase to the nDone array after each turn
						j++; //increment j to indicate an index has been added to nDone
					} while(nPlayerLives > 0 && j < 2); //loop this statement until 2 medium phrases have been finished or player loses lives
				
					if(nPlayerLives == 0) //if player has no more lives, call function EndGame() to end the game
						EndGame(PlayerScores, strPlayerName, nPlayerScore, nPlayerCount, nSize);
					else //otherwise, continue with the game:
					{
						j = 0; //reset j to 0 to reset the turn counter
						//do-while loop to execute medium level
						do
						{
							printf("\n-------------------------------------\n");
							printf("\nPlayer: %s\t Lives: %d\t Score: %d\n", strPlayerName, nPlayerLives, nPlayerScore);
							sleep(1);
							printf("DIFFICULTY: HARD\n\n");
							//do while loop to choose a phrase from the records
							do
							{
								nChosenPhrase = 0; //set the chosen phrase to 0 at every loop
								nIndex = getRandomPhrase(nHardIndex, nHardCount); //call function getRandomPhrase() to generate a random number
								//for loop to check if the chosen index is already chosen before
								for(i = 0; i < nHardCount; i++)
								{
									if(nDone[i] == nIndex) //if the chosen index has already been choosen before
										nChosenPhrase = -1; //set nChosenPhrase to -1
								}
								if(nChosenPhrase != -1) //if the generated index has not been found in the array
									nChosenPhrase = nIndex; //set the chosen phrase to the generated index
							} while (nChosenPhrase == -1); //loop this until a chosen phrase has been found
							
							printf("Type this phrase: \n");
							printf("%s\n", ExistRecords[nChosenPhrase].Phrase); //display chosen phrase
							printf("\nEnter: ");
							scanf(" %100[^\n]*c", strPlayerInput); //ask user to input phrase
							
							//add up points if the user input matches perfectly with the phrase
							if(strcmp(strPlayerInput, ExistRecords[nChosenPhrase].Phrase) == 0)
							{
								printf("Correct! You earn 3 points. ");
								EnterToContinue(0);
								nPlayerScore += 3;
							}
							else //decrease lives if user input does not match perfectly with the phrase
							{
								printf("Wrong! You lose 1 life. ");
								EnterToContinue(0);
								nPlayerLives--;
							}
							nDone[j] = nChosenPhrase; //add the chosen phrase to the nDone array after each turn
							j++; //increment j to indicate an index has been added to nDone
						} while(nPlayerLives > 0 && j < nHardCount); //loop this statement until player loses all lives or all hard phrases have already been done
						
						EndGame(PlayerScores, strPlayerName, nPlayerScore, nPlayerCount, nSize); //no matter if the user has lost all lives or not, end the game.
					}
				}
			}
			else //otherwise:
			{
				if(nEasyCount < 3) //execute if there are not enough phrases for easy level
					printf("Not enough phrases for easy level! \n");
				if(nMediumCount < 2) //execute if there are not enough phrases for medium level
					printf("Not enough phrases for medium level! \n");
				if(nHardCount < 5) //execute if there are not enough phrases for hard level
					printf("Not enough phrases for hard level! \n");
				EnterToContinue(1);
			}
		}
		else //if score.txt not found:
		{
			printf("Score file not found! Create \"score.txt\" file and try again. ");
			EnterToContinue(1); //continue prompt
		}
	}
	else //If there are no existing records:
	{
		printf("No existing records! ");
		EnterToContinue(1); //continue prompt
	}
	
	*nSelect = 0; //set nSelect to 0 to return to Play Menu
}