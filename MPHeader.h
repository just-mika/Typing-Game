typedef char String30 [31];
typedef char String10 [11];
typedef char String100 [101];

struct RecordTag
{
	int ID;
	String10 Level;
	int charCount;
	String100 Phrase;
};

void displayTitle();

void EnterToContinue(int clear);

void initializeRecord(struct RecordTag *existrecord, int size);

void ManageData(int * nReturn, struct RecordTag *existrecords);