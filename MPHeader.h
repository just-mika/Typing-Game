typedef char String30 [31];
typedef char String10 [11];
typedef char String100 [101];

struct 
RecordTag
{
	int ID;
	String10 Level;
	int charCount;
	String100 Phrase;
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
DisplayRecord(int nHeader, 
			  struct RecordTag ExistRecord);

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
ManageData(int * nReturn, 
		   struct RecordTag *ExistRecords);