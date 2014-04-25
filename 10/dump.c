

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
	
	//open db pointer
	sqlite3 *db = NULL;
	if(sqlite3_open(argv[1], &db) != SQLITE_OK)
	{
		 printf("Error : DB can't open\n");
		 return 1;
	}
	
	sqlite3_stmt *query = NULL;
	char temp[1000];
	strcpy(temp, "SELECT * FROM ");
	strcat(temp, argv[2]);
	
	int result = sqlite3_prepare_v2(db, temp, -1, &query, NULL);
	if(result != SQLITE_OK)
	{	
		printf("Error :query fail\n");
		sqlite3_finalize(query);
		sqlite3_close(db);
		return 1;
	}
	
	//set the file pointer
	FILE *csv = fopen(argv[3], "w");

	//put table to csv file
	while(sqlite3_step(query) == SQLITE_ROW)
	{
		int num_col = sqlite3_column_count(query);
		int i = 0;
		for(i = 0; i < num_col; i++)	
		{	
			//if the input word is word
			int col_type = sqlite3_column_type(query, i);
			if (col_type == SQLITE_TEXT)
			{
				printf("'%s'",  sqlite3_column_text(query, i));
				fprintf(csv, "'%s'",  sqlite3_column_text(query, i));
			}
			//if the input word is an integer
			else if (col_type == SQLITE_INTEGER)
			{	
				printf("%s",  sqlite3_column_text(query, i));
				fprintf(csv, "%s",  sqlite3_column_text(query, i));
			}
			//if the input word is nothing
			else 
			{
				printf("Error : Column fail\n");
				sqlite3_finalize(query);
				sqlite3_close(db);
				return 1;
			}
			//put ',' behind each input 
			if (num_col >i+1)
			{
				printf(",");
				fprintf(csv,",");
			}
		}
		//new line
		printf("\n");
		fprintf(csv,"\n");
	}
	//close file and db and query
	fclose(csv);
	sqlite3_finalize(query);
	sqlite3_close(db);
	return 0;
}
