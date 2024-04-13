#include <stdio.h>

// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order;
};

// Fill out this structure
struct HashType
{
	struct RecordType* data;
	int size;
};

// Compute the hash function
int hash(int x, int size)
{
	return x % size;
}

struct HashType* create_HashTable(int size) {
	struct HashType* hash_Table = (struct HashType*)malloc(sizeof(struct HashType));
	hash_Table->size = size;
	hash_Table->data = (struct RecordType*)malloc(sizeof(struct RecordType) * size);
	for (int i = 0; i < size; i++) {
		hash_Table->data[i].id = 0;
	}
	return hash_Table;
}

void insert_Record(struct HashType* hashTable, struct RecordType record) {
	int index = hash(record.id, hashTable->size);
	while (hashTable->data[index].id != 0) {
		index = (index + 1) % hashTable->size;
	}
	hashTable->data[index] = record;
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType* pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*)malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType* pHashArray, int hashSz)
{
	int i;

	for (i = 0; i < hashSz; ++i)
	{
		// if index is occupied with any records, print all
		if (pHashArray->data[i].id != -1) {
			printf("Record %d -> %d, %c, %d\n", i, pHashArray->data[i].id, pHashArray->data[i].name, pHashArray->data[i].order);
		}
	}

}

int main(void)
{
	struct RecordType* pRecords;
	int recordSz = 0;

	recordSz = parseData("input.txt", &pRecords);
	printRecords(pRecords, recordSz);
	// Your hash implementation
	struct HashType* hash_Table = createHashTable(recordSz);

	for (int i = 0; i < recordSz; ++i) {
		insertRecord(hash_Table, pRecords[i]);
	}

	displayRecordsInHash(hash_Table, hash_Table->size);
	
	free(pRecords);
	free(hash_Table->data);
	free(hash_Table);
	return 0;
}