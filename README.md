# idxvis

Direction:
To run the system, please run proj_630.html. Make sure that you have d3js_simple07.js, idx_7.tsv, idx_8.tsv, idx_715.tsv, idx_lshipdate.tsv, noindex.tsv, sqlite_all.sql, and d3.v3.js in the same directory. The other files in this repository, namely process_loop.cpp, sqlite_test_batch_queries.c, proj_630_blank.html, and Makefile, are used in the following way:

proj_630_blank.html: simply for debug.
sqlite_test_batch_queries.c: used to collect statistics from SQLite via S QLite APIs.
Makefile: used to compile sqlite_test_batch_queries.c. Make sure that SQLite source code are in the same directory and double check the path.
process_loop.cpp: used to process the output from sqlite_test_batch_queries.c.

=================================================================

Attention: 
Please notice that only indices on "l_orderkey", "o_orderkey", "l_shipdate" and "l_orderkey, o_orderdate" are available in this version. To show the effect of building indices on "l_orderkey, o_orderdate", first click on the rectangle of "lineitem", then click on "l_orderkey", then click on the rectangle of "orders", and finally click on "o_orderdate".


