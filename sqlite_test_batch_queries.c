#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include </home/kagamiori/Courses/Visualization 630/test_batch_queries/sqlite3.h>
//---------------------------------------
//using namespace std;
//---------------------------------------
static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
	int i;
	for(i=0; i<argc; i++)
	{
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

//----------------------------------------

int main(int argc, const char **argv)
{
	sqlite3 *db;
	char *ErrMsg = 0;
	int rc;
	sqlite3_stmt *ppStmt;
	const char **tmp;
	sqlite3_int64 out_status;
	const char *out_status2;
	FILE *fp;
	char *query = malloc(sizeof(char) * 5000);
	int len = 0;
	int query_no;
	//char out_status[500];
	//string::size_type sz;
	
	if (argc < 4)
	{
		printf("Usage: %s DATABASE QueryFile --option --loop-num\n", argv[0]);
		return 0;
	}
	rc = sqlite3_open(argv[1], &db);
	if (rc != SQLITE_OK)
	{
		printf("SQL error open db: %s\n", ErrMsg);
		sqlite3_free(ErrMsg);
	}
	
	fp = fopen(argv[2], "r");
	if (fp == NULL)
	{
		printf("open query file error\n");
		return 0;
	}
	
	query_no = 0;
	if (strcmp("--execute", argv[3]) == 0)
	{
		while (getline(&query, &len, fp) != -1)
		{
			query_no++;
			rc = sqlite3_exec(db, query, callback, 0, &ErrMsg);
			if (rc != SQLITE_OK || query[0] == '\n')
			{
				if (query[0] == '\n')
				{
					query_no--;
				}
				else
				{
					printf("SQL error stmtstatus: %s\n", ErrMsg);
					sqlite3_free(ErrMsg);
				}
				//getline(&query, &len, fp);
				//getline(&query, &len, fp);
				continue;
			}
			printf("%d done\n", query_no);
			//getline(&query, &len, fp);
			//getline(&query, &len, fp);
			
		}
		goto exit;
	}
	/*rc = sqlite3_exec(db, argv[2], callback, 0, &ErrMsg);
	if (rc != SQLITE_OK)
	{
		printf("SQL error: %s\n", ErrMsg);
		sqlite3_free(ErrMsg);
	}*/

	

	int loop_no, step_no, i;
	//step_no = atoi(argv[4]);
	if (strcmp("--scanstatus", argv[3]) == 0)
	{
		while (getline(&query, &len, fp) != -1)
		{
			query_no++;
			rc = sqlite3_prepare(db, query, 5000, &ppStmt, tmp);
			if (rc != SQLITE_OK || query[0] == '\n')
			{
				if (query[0] == '\n')
				{
					query_no--;
				}
				else
				{
					printf("SQL error stmtstatus: %s\n", ErrMsg);
					sqlite3_free(ErrMsg);
				}
				//getline(&query, &len, fp);
				//getline(&query, &len, fp);	
				continue;
			}
			
			printf("%d:: \n", query_no);
			loop_no = atoi(argv[4]);
			rc = sqlite3_stmt_scanstatus(ppStmt, loop_no, SQLITE_SCANSTAT_NVISIT, &out_status);
			printf("loop %d: rc = %d, scanstatus = %d\n", loop_no, rc, out_status);
	
			rc = sqlite3_step(ppStmt);
			printf("step %d: rc = %d\n", i, rc);
			while (rc != 101)
			{
				rc = sqlite3_stmt_scanstatus(ppStmt, loop_no, SQLITE_SCANSTAT_NVISIT, &out_status);
				rc = sqlite3_stmt_scanstatus(ppStmt, loop_no, SQLITE_SCANSTAT_NAME, &out_status2);
				printf("loop %d: rc = %d, table/index = %s, scanstatus = %d\n", loop_no, rc, out_status2, out_status);
				rc = sqlite3_step(ppStmt);
				
				i++;
				printf("step %d: rc = %d\n", i, rc);
			}
			//getline(&query, &len, fp);
			//getline(&query, &len, fp);	
		}
	}
	else if (strcmp("--stmtstatus", argv[3]) == 0)
	{
		while (getline(&query, &len, fp) != -1)
		{
			query_no++;
			rc = sqlite3_prepare(db, query, 5000, &ppStmt, tmp);
			if (rc != SQLITE_OK || query[0] == '\n')
			{
				if (query[0] == '\n')
				{
					query_no--;
				}
				else
				{
					printf("SQL error stmtstatus: %s\n", ErrMsg);
					sqlite3_free(ErrMsg);
				}
					
				//getline(&query, &len, fp);
				//getline(&query, &len, fp);
				continue;
			}
			
			printf("%d: \n", query_no);
			rc = sqlite3_stmt_status(ppStmt, SQLITE_STMTSTATUS_FULLSCAN_STEP, 0);
			printf("stmtstatus: scanstep = %d\n", rc);
		
			rc = sqlite3_step(ppStmt);
			printf("step %d: rc = %d\n", i, rc);
			while (rc != 101)
			{
				rc = sqlite3_stmt_status(ppStmt, SQLITE_STMTSTATUS_FULLSCAN_STEP, 0);
				printf("stmtstatus: scanstep = %d\n", rc);
		
				rc = sqlite3_step(ppStmt);
				printf("step %d: rc = %d\n", i, rc);
			}
			//getline(&query, &len, fp);
			//getline(&query, &len, fp);	
		}
	}
	else
	{
		printf("option: --scanstatus or --stmtstatus or --execute\n");
	}
	
	
	

exit:	sqlite3_close(db);
	return 0;
}
