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
	for(i = 0; i < nPhraseCount; i++)
	{
		if(ExistRecords[i].ID == nRecordSelect) //Set nIndex to current value of i the current index ID matches the user input
			nIndex = i;
	}
	
	return nIndex; //Return resulting index.
}

/* FindExistingPhrase checks if the input phrase already exists in the records.
@param *ExistRecords - pointer to a structure array containing all the records.
@param nPhraseCount - the number of existing phrases in the records.
@param strPhrase - the phrase the user inputed.
@return nIndex which indicates the index of the identical phrase (-1 if there is no identical phrasews)
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
	Statement 2: Continue loop if index is less than the array size AND if nSelect is not 0 (so that the loop would stop once existing phrase is found.)
	Statement 3: Post-increment index
	*/
	for(i = 0; i < nPhraseCount; i++)
	{
		if(strcmp(strPhrase, ExistRecords[i].Phrase) == 0) //Execute statement if the inputed phrase already exists in the records.
		{
			nIndex = i; //If found, set nIndex to the current index.
		}
	}
	
	return nIndex; //Return the resulting value of nIndex.
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
	int nIndex; //Declare index of the identical phrase(nIndex)
	int nPhraseCount = CountPhrase(ExistRecords, nSize); //Declare integer variable for the number of existing phrases in the records. Call function CountPhrase() to set its value.
	int nNextPhrase; //Declare integer variable for the index of the added phrase.
	
	printf("ADD A RECORD\n");
	printf("-----------------\n");
	
	//Execute this statement only if the number of phrases is less than the size. 
	if(nPhraseCount < nSize)
	{
		printf("Enter a phrase up to 100 characters (type /back to go to back to menu): ");
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
					printf("Enter a phrase (up to 100 characters): ");
					scanf(" %100[^\n]*c", strPhrase); //Input string. Only read up to 100 characters AND stop inputting after pressing enter.
					
					nFound = FindExistingPhrase(ExistRecords, nPhraseCount, strPhrase); //Function call FindExistingPhrase to check if input phrase exists in the records.
					
					if(nFound != -1)
						printf("\nPhrase already exists! It's in ID Number %d.\n", ExistRecords[nFound].ID); //display the phrase's ID number.
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
				DisplayHeader();
				DisplayRecordTable(ExistRecords, nPhraseCount);
				
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

void 
ImportData(struct RecordTag *ExistRecords, 
			int nSize, 
			int *nSelect)
{
	int i, nPhraseCount;
	String30 strFileName;
	
	FILE *fpImport;
	
	printf("IMPORT DATA\n");
	printf("-----------------\n\n");
	
	printf("Enter file name for export file: ");
	scanf(" %28[^\n]*c", strFileName);
	 	
	strcat(strFileName, ".txt");
	
	fpImport = fopen(strFileName, "r");
	
	if(fpImport != NULL)
	{
		i = 0;
	 	do
	 	{
	 		fscanf(fpImport, "%d\n", &ExistRecords[i].ID);
	 		fscanf(fpImport, "%[^\n]s\n", ExistRecords[i].Level);
	 		fscanf(fpImport, "%d\n", &ExistRecords[i].charCount);
	 		fscanf(fpImport, "%[^\n]s\n\n", ExistRecords[i].Phrase);
	 		
	 		i++;
		} while (feof(fpImport) == 0);
		
		nPhraseCount = CountPhrase(ExistRecords, nSize);
		
		DisplayHeader();
		DisplayRecordTable(ExistRecords, nPhraseCount);
		printf("\nData successfully imported! ");
		EnterToContinue(1);
		fclose(fpImport);
	}
	else
	{
		printf("File not found! ");
		EnterToContinue(1);
	}
	
	*nSelect = 0;
}

void 
ExportData(struct RecordTag *ExistRecords, 
			int nSize, 
			int *nSelect)
 {
 	int i, nPhraseCount = CountPhrase(ExistRecords, nSize);
 	String30 strFileName;
 	
 	FILE *fpExport;
 	
 	printf("EXPORT DATA\n");
	printf("-----------------\n\n");
		
	if(nPhraseCount != 0) //Execute this statement if there ARE existing records
	{
		printf("Enter file name: ");
	 	scanf(" %28[^\n]*c", strFileName);
	 	
	 	strcat(strFileName, ".txt");
	 	
	 	fpExport = fopen(strFileName, "a");
	 	
	 	for(i = 0; i < nPhraseCount; i++)
	 	{
	 		fprintf(fpExport, "%d\n", ExistRecords[i].ID);
	 		fprintf(fpExport, "%s\n", ExistRecords[i].Level);
	 		fprintf(fpExport, "%d\n", ExistRecords[i].charCount);
	 		fprintf(fpExport, "%s\n\n", ExistRecords[i].Phrase);
		}
		printf("Data successfully exported! ");
		EnterToContinue(1);
		fclose(fpExport);
	}
	else //If there are no records found, execute this statement
	{
		printf("No records found! ");
		EnterToContinue(1); //continue prompt
	}

	*nSelect = 0;
 }


int getRandomPhrase(int *nLevelIndex, int nLevelCount)
{
	int nIndex;
	/* srand() function is used to set the starting point for the rand() function.
	   time(NULL) function is used as the seed so that the random number generated isn't the same every run. */
	srand(time(NULL));
	/* return the generated random number using the rand() function, get its modulo by 4 and add 1 
	   so that the returned number will only range from 1 to 4. */
	
	nIndex = (rand() % nLevelCount); 
	
	return nLevelIndex[nIndex];
}


int CountLevelPhrases(struct RecordTag *ExistRecords, int nPhraseCount, int nLevel, int *nLevelIndex)
{
	int i;
	int nLevelPhrases = 0;
	
	for(i = 0; i < nPhraseCount; i++)
	{
		if(nLevel == 1)
		{
			if(strcmp(ExistRecords[i].Level, "easy") == 0)
			{
				nLevelIndex[nLevelPhrases] = i;
				nLevelPhrases++;
			}
		}
		else if(nLevel == 2)
		{
			if(strcmp(ExistRecords[i].Level, "medium") == 0)
			{
				nLevelIndex[nLevelPhrases] = i;
				nLevelPhrases++;
			}
		}
		else if(nLevel == 3)
		{
			if(strcmp(ExistRecords[i].Level, "hard") == 0)
			{
				nLevelIndex[nLevelPhrases] = i;
				nLevelPhrases++;
			}
		}
	}
	return nLevelPhrases;
}

//WIP
void 
PlayGame(struct RecordTag *ExistRecords, 
		 struct ScoreTag *PlayerScores,
			 int nSize, 
			 int *nSelect)
{
	String30 strPlayerName;
	String100 strPlayerInput;
	
	int nChosenPhrase, i;
	
	int nPhraseCount = CountPhrase(ExistRecords, nSize), nPlayerScore = 0, nPlayerLives = 3;
	
	int nEasyIndex[nSize], nMediumIndex[nSize], nHardIndex[nSize];
	
	int nEasyCount = CountLevelPhrases(ExistRecords,  nPhraseCount, 1, nEasyIndex);
	int nMediumCount = CountLevelPhrases(ExistRecords,  nPhraseCount, 2, nMediumIndex);
	int nHardCount = CountLevelPhrases(ExistRecords,  nPhraseCount, 3, nHardIndex);
	
	printf("TYPING GAME\n");
	printf("-------------------------------------\n\n");
	
	if(nPhraseCount != 0)
	{
		if(nEasyCount >= 3 && nMediumCount >= 2 && nHardCount >= 5)
		{
			i = 0;
			printf("Enter your name: ");
			scanf(" %30[^\n]*c", strPlayerName);
			
			system("cls");
			printf("TYPING GAME\n");
			do
			{
				printf("-------------------------------------\n");
				printf("\nPlayer: %s\t Lives: %d\t Score: %d\n", strPlayerName, nPlayerLives, nPlayerScore);
				sleep(1);
				printf("DIFFICULTY: EASY\n\n");
				nChosenPhrase = getRandomPhrase(nEasyIndex, nEasyCount);
				
				printf("Type this phrase: \n");
				printf("%s\n", ExistRecords[nChosenPhrase].Phrase);
				printf("\nEnter: ");
				scanf(" %100[^\n]*c", strPlayerInput);
				
				if(strcmp(strPlayerInput, ExistRecords[nChosenPhrase].Phrase) == 0)
				{
					printf("Correct! You earn 1 point.");
					EnterToContinue(0);
					nPlayerScore++;
				}
				else
				{
					printf("Wrong! You lose 1 life.");
					EnterToContinue(0);
					nPlayerLives--;
				}
				i++
			} while(nPlayerLives > 0;
		}
		else
		{
			if(nEasyCount < 3)
				printf("Not enough phrases for easy level! \n");
			if(nMediumCount < 2)
				printf("Not enough phrases for medium level! \n");
			if(nHardCount < 5)
				printf("Not enough phrases for hard level! \n");
			EnterToContinue(1);
		}
	}
	else
	{
		printf("No existing records! ");
		EnterToContinue(1);
	}
	
	*nSelect = 0;
}
