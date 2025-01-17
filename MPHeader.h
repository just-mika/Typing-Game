typedef char String10 [11];
typedef char String255 [256];
typedef char String100 [101];

struct 
RecordTag
{
	int ID;
	String10 Level;
	int charCount;
	String100 Phrase;
};

struct
ScoreTag
{
	String10 Name;
	int Score;
};

void 
displayTitle();

void 
EnterToContinue(int nClear);

void
initializeRecord(struct RecordTag *ExistRecords, 
				 int nSize);

int 
GetPassword(char * strPassword);

void
DisplayRecord(struct RecordTag ExistRecord);

void 
DisplayRecordTable(struct RecordTag *ExistRecords,
					int nPhraseCount);
					
int
CountPhrase(struct RecordTag *ExistRecords,
			int nSize);
			
int
FindRecord(struct RecordTag *ExistRecords,
			int nPhraseCount, 
			int nRecordSelect);
			
int
FindExistingPhrase(struct RecordTag *ExistRecords,
					int nPhraseCount, 
					String100 strPhrase);

void
AddRecord(struct RecordTag *ExistRecords, 
		  int nSize, 
		  int *nSelect);
void
EditRecord(struct RecordTag *ExistRecords, 
		   int nSize, 
		   int *nSelect);

void
DeleteRecord(struct RecordTag *ExistRecords, 
			 int nSize, 
			 int *nSelect);
			 
void 
ImportData(struct RecordTag *ExistRecords, 
			int nSize, 
			int *nSelect);
			 
void 
ExportData(struct RecordTag *ExistRecords, 
			int nSize, 
			int *nSelect);

int 
getRandomPhrase(int *nLevelIndex, 
				int nLevelCount);

int 
CountLevelPhrases(struct RecordTag *ExistRecords, 
					int nPhraseCount, 
					int nLevel, 
					int *nLevelIndex);

int 
LoadScoreFile(struct ScoreTag *PlayerScores, 
				int nSize);

void 
SelectionSort(struct ScoreTag *PlayerScores, 
					int nSize);

void
EndGame(struct ScoreTag *PlayerScores, 
		String10 strPlayerName, 
		int nPlayerScore, 
		int nPlayerCount,
		int nSize);
		
void 
DisplayScores (struct ScoreTag *PlayerScores, 
				int *nSelect, 
				int nSize);

void 
PlayGame(struct RecordTag *ExistRecords, 
		 struct ScoreTag *PlayerScores,
		 int nSize, 
		 int *nSelect);