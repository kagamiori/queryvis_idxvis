CC = gcc
#CFLAGS = -g -Wall -DDEBUG
CFLAGS =  -g -O0 -Wall -DSQLITE_ENABLE_STMT_SCANSTATUS

DEST = test

HFILES = sqlite3.h sqlite3ext.h

CFILES = sqlite3.c\
	 sqlite_test_batch_queries.c

OFILES = sqlite3.o \
	sqlite_test_batch_queries.o

.c.o :
	$(CC) $(CFLAGS) -c $<

$(DEST) : $(OFILES)
	$(CC) -pthread -Wl,--no-as-needed -ldl -o $(DEST)  $(OFILES) -ll -lsqlite3

sqlite3.o: sqlite3.h sqlite3ext.h sqlite3.c

sqlite_test_batch_queries.o: sqlite3.h sqlite3ext.h sqlite3.c sqlite_test_batch_queries.c



.PHONY: clean
clean :
	/bin/rm -f *.o $(DEST) *.BAK lex.yy.c y.tab.* y.output
