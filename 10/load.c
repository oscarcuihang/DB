

#include <stdio.h>
#include <sqlite3.h>
#include <string.h>

int main(int argc, char** argv)
{
	if(argc != 4)
    {
		fprintf(stderr, "USAGE: %s <database file> <table name> <CSV file>\n", argv[0]);
		return 1;
    }
	//printf("Implement me!\n");

	FILE *input = fopen(argv[3], "r");
	//find the file is there or not
	if (input == NULL)
	{
		printf("Error : File can't open\n");
	}
	sqlite3 * db = NULL;
	
	//find the DB
	if(sqlite3_open(argv[1], &db) != SQLITE_OK)
	{
		printf("Error : DB can't open\n");
	}
	sqlite3_stmt *query = NULL;
	//delete the old table in db
	char d[100] = "DELETE FROM ";
	strcat(d, argv[2]);
	int result = sqlite3_prepare_v2(db, d, -1, &query, NULL);
	printf("%s\n",d);
	//prepare the query
	if(result != SQLITE_OK)
	{
		printf("1Error : query fail\n");
	}
	//execute the query
	if(sqlite3_step(query) != SQLITE_DONE)
	{
			printf("2Error : query execute fail\n");
	}
	
	char temp[1000];
	while (fgets(temp, 1000, input) != NULL)
	{
		char q[1000] = "INSERT INTO ";
		strcat(q, argv[2]);
		strcat(q, " VALUES(");
		strcat(q, temp);
		strcat(q, ")");
		result = sqlite3_prepare_v2(db, q, -1, &query, NULL);
		printf("%s\n",q);
		if(result != SQLITE_OK)
		{
			printf("3Error : prepare fail\n");
		}
		if(sqlite3_step(query) != SQLITE_DONE)
		{
			printf("4Error : query execute fail\n");
		}
	}
	//close file and db and query
	fclose(input);
	sqlite3_finalize(query);
	sqlite3_close(db);
	return 0;
}
