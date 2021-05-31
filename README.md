# SQLite in C++
+ Dowload [SQLite Expert Professional](https://soft98.ir/software/programming/15259-SQLite-Expert.html) and [Sqlite](https://www.sqlite.org/download.html) 
+ [Dowload C Source Code and Header File](https://www.sqlite.org/download.html)
+ Download the video of the first session of the online class
+ Download the video of the second session of the online class
# Important Points
## Data type
SQLite provides five primitive data types which are referred to as storage classes.

| Storage Class | Description|
|---------------|------------|
|NULL|The value is a NULL value.|
|INTEGER|The value is a signed integer, stored in 1, 2, 3, 4, 6, or 8 bytes depending on the magnitude of the value.|
|REAL|The value is a floating point value, stored as an 8-byte IEEE floating point number.|
|TEXT|The value is a text string, stored using the database encoding (UTF-8, UTF-16BE or UTF-16LE)|
|BLOB|The value is a blob of data, stored exactly as it was input.|

SQLite determines the data type of a value based on its data type according to the following rules:
+ If a literal has no enclosing quotes and decimal point or exponent, SQLite assigns the INTEGER storage class.
+ If a literal is enclosed by single or double quotes, SQLite assigns the TEXT storage class.
+ If a literal does not have quote nor decimal point nor exponent, SQLite assigns REAL storage class.
+ If a literal is NULL without quotes, it assigned NULL storage class.
+ If a literal has the X’ABCD’ or x‘abcd’, SQLite assigned BLOB storage class.

SQLite does not support built-in date and time storage classes. However, you can use the TEXT, INT, or REAL to store date and time values. For the detailed information on how to handle date and time values.

Using the TEXT storage class for storing SQLite date and time

If you use the TEXT storage class to store date and time value, you need to use the ISO8601 string format as follows

`YYYY-MM-DD HH:MM:SS.SSS`


## Primary Key (PK)

A primary key is a column or group of columns used to identify the uniqueness of rows in a table. Each table has one and only one primary key. It is possible that primary key has only one column or primary key consists of two or more columns

When you create a table without specifying the WITHOUT ROWID option, SQLite adds an implicit column called rowid that stores 64-bit signed integer. The rowid column is a key that uniquely identifies the rows in the table. Tables that have rowid columns are called rowid tables.

If a table has the primary key that consists of one column, and that column is defined as INTEGER then this primary key column becomes an alias for the rowid column.

Notice that if you assign another integer type such as BIGINT and UNSIGNED INT to the primary key column, this column will not be an alias for the rowid column.

Because the rowid table organizes its data as a B-tree, querying and sorting data of a rowid table are very fast. It is faster than using a primary key which is not an alias of the rowid.

## Foreign Key (FK)

A foreign key is a key used to link two tables together. This is sometimes also called as a referencing key.

A Foreign Key is a column or a combination of columns whose values match a Primary Key in a different table.

The relationship between 2 tables matches the Primary Key in one of the tables with a Foreign Key in the second table.

If a table has a primary key defined on any field(s), then you cannot have two records having the same value of that field(s).

## INSERT 
SQLite INSERT INTO Statement is used to add new rows of data into a table in the database.
```sql
INSERT INTO TABLE_NAME [(column1, column2, column3,...columnN)]  
VALUES (value1, value2, value3,...valueN);
```
For Example : 
```cpp
	sql = "INSERT INTO Student (ID,FName,LName,Photo) VALUES(? , ? , 'Tavkoli', ? ); ";
```

## SELECT 
SQLite SELECT statement is used to fetch the data from a SQLite database table which returns data in the form of a result table. These result tables are also called result sets.
```sql 
SELECT column1, column2, columnN FROM table_name;
```
Here, column1, column2 ... are the fields of a table, whose values you want to fetch. If you want to fetch all the fields available in the field, then you can use the following syntax −
```sql
SELECT * FROM table_name;
```
If you want to fetch only selected fields of Studen table, then use the following query −
```sql
SELECT ID, FName FROM COMPANY;
```

## Operators
Assume variable a holds 10 and variable b holds 20, then SQLite comparison operators will be used as follows
|Operator	|Description	|Example|
|--------|-------------|--------|
|==|Checks if the values of two operands are equal or not, if yes then the condition becomes true.	|(a == b) is not true.|
|!=|Checks if the values of two operands are equal or not, if the values are not equal, then the condition becomes true.|(a != b) is true.|
|>|Checks if the values of the left operand is greater than the value of the right operand, if yes then the condition becomes true.	|(a > b) is not true.|
|>=|Checks if the value of the left operand is greater than or equal to the value of the right operand, if yes then the condition becomes true.|(a >= b) is not true.|
|<|Checks if the values of the left operand is less than the value of the right operand, if yes then the condition becomes true.	|(a < b) is true.|
|<=|Checks if the value of the left operand is less than or equal to the value of the right operand, if yes then the condition becomes true.	|(a <= b) is true.|
|AND|The AND operator allows the existence of multiple conditions in an SQL statement's WHERE clause.||
|BETWEEN|The BETWEEN operator is used to search for values that are within a set of values, given the minimum value and the maximum value.||
|EXISTS|The EXISTS operator is used to search for the presence of a row in a specified table that meets certain criteria.||
|IN|The IN operator is used to compare a value to a list of literal values that have been specified.||
|NOT|The NOT operator reverses the meaning of the logical operator with which it is used. Eg. NOT EXISTS, NOT BETWEEN, NOT IN, etc. This is negate operator.||
|OR|The OR operator is used to combine multiple conditions in an SQL statement's WHERE clause.||
|IS NULL|The NULL operator is used to compare a value with a NULL value.||

## WHERE 
SQLite WHERE clause is used to specify a condition while fetching the data from one table or multiple tables.

If the given condition is satisfied, means true, then it returns the specific value from the table. You will have to use WHERE clause to filter the records and fetching only necessary records.
```sql
SELECT column1, column2, columnN 
FROM table_name
WHERE [condition]
```
## The AND Operator
```
SELECT column1, column2, columnN 
FROM table_name
WHERE [condition1] AND [condition2]...AND [conditionN];
```
## The OR Operator
```sql
SELECT column1, column2, columnN 
FROM table_name
WHERE [condition1] OR [condition2]...OR [conditionN]
```

## Expressions

An expression is a combination of one or more values, operators, and SQL functions that evaluate to a value.

SQL expressions are like formulas and they are written in query language. You can also use to query the database for a specific set of data.

Syntax
Consider the basic syntax of the SELECT statement as follows
```sql
SELECT column1, column2, columnN 
FROM table_name 
WHERE [CONDITION | EXPRESSION];
```
## Boolean Expressions
```sql
SELECT column1, column2, columnN 
FROM table_name 
WHERE SINGLE VALUE MATCHTING EXPRESSION;
```
Consider COMPANY table with the following records −
```
ID          NAME        AGE         ADDRESS     SALARY
----------  ----------  ----------  ----------  ----------
1           Paul        32          California  20000.0
2           Allen       25          Texas       15000.0
3           Teddy       23          Norway      20000.0
4           Mark        25          Rich-Mond   65000.0
5           David       27          Texas       85000.0
6           Kim         22          South-Hall  45000.0
7           James       24          Houston     10000.0
```
Following is a simple examples showing the usage of SQLite Boolean Expressions −

```sql
SELECT * FROM COMPANY WHERE SALARY = 10000;
```
```
ID          NAME        AGE         ADDRESS     SALARY
----------  ----------  ----------  ----------  ----------
4           James        24          Houston   10000.0
```

## Numeric Expression
These expressions are used to perform any mathematical operation in any query. Following is the syntax −
```sql
SELECT numerical_expression as OPERATION_NAME
[FROM table_name WHERE CONDITION] ;
```
Here, numerical_expression is used for mathematical expression or any formula. Following is a simple example showing the usage of SQLite Numeric Expressions.
```sql
SELECT (15 + 6) AS ADDITION
ADDITION = 21
```
There are several built-in functions such as avg(), sum(), count(), etc., to perform what is known as aggregate data calculations against a table or a specific table column.
```sql
SELECT COUNT(*) AS "RECORDS" FROM COMPANY; 
RECORDS = 7
```
## Date Expressions
Date Expressions returns the current system date and time values. These expressions are used in various data manipulations.
```
SELECT CURRENT_TIMESTAMP;
```
`CURRENT_TIMESTAMP = 2013-03-17 10:43:35`

## UPDATE 
SQLite UPDATE Query is used to modify the existing records in a table. You can use WHERE clause with UPDATE query to update selected rows, otherwise all the rows would be updated.

Syntax
Following is the basic syntax of UPDATE query with WHERE clause.
```sql
UPDATE table_name
SET column1 = value1, column2 = value2...., columnN = valueN
WHERE [condition];
```
### Example
Consider COMPANY table with the following records −
```
ID          NAME        AGE         ADDRESS     SALARY
----------  ----------  ----------  ----------  ----------
1           Paul        32          California  20000.0
2           Allen       25          Texas       15000.0
3           Teddy       23          Norway      20000.0
4           Mark        25          Rich-Mond   65000.0
5           David       27          Texas       85000.0
6           Kim         22          South-Hall  45000.0
7           James       24          Houston     10000.0
```
Following is an example, which will update ADDRESS for a customer whose ID is 6.

```sql
UPDATE COMPANY SET ADDRESS = 'Texas' WHERE ID = 6;
```
Now, COMPANY table will have the following records.
```
ID          NAME        AGE         ADDRESS     SALARY
----------  ----------  ----------  ----------  ----------
1           Paul        32          California  20000.0
2           Allen       25          Texas       15000.0
3           Teddy       23          Norway      20000.0
4           Mark        25          Rich-Mond   65000.0
5           David       27          Texas       85000.0
6           Kim         22          Texas       45000.0
7           James       24          Houston     10000.0
```
If you want to modify all ADDRESS and SALARY column values in COMPANY table, you do not need to use WHERE clause and UPDATE query will be as follows −

```sql
UPDATE COMPANY SET ADDRESS = 'Texas', SALARY = 20000.00;
```
Now, COMPANY table will have the following records −
```
ID          NAME        AGE         ADDRESS     SALARY
----------  ----------  ----------  ----------  ----------
1           Paul        32          Texas       20000.0
2           Allen       25          Texas       20000.0
3           Teddy       23          Texas       20000.0
4           Mark        25          Texas       20000.0
5           David       27          Texas       20000.0
6           Kim         22          Texas       20000.0
7           James       24          Texas       20000.0
```
You can combine N number of conditions using AND or OR operators.
## DELETE 
SQLite DELETE Query is used to delete the existing records from a table. You can use WHERE clause with DELETE query to delete the selected rows, otherwise all the records would be deleted.

Following is the basic syntax of DELETE query with WHERE clause.
```sql
DELETE FROM table_name
WHERE [condition];
```
You can combine N number of conditions using AND or OR operators.

### Example
Consider COMPANY table with the following records.
```
ID          NAME        AGE         ADDRESS     SALARY
----------  ----------  ----------  ----------  ----------
1           Paul        32          California  20000.0
2           Allen       25          Texas       15000.0
3           Teddy       23          Norway      20000.0
4           Mark        25          Rich-Mond   65000.0
5           David       27          Texas       85000.0
6           Kim         22          South-Hall  45000.0
7           James       24          Houston     10000.0
```
Following is an example, which will DELETE a customer whose ID is 7.

```sql
DELETE FROM COMPANY WHERE ID = 7;
```
Now COMPANY table will have the following records.
```
ID          NAME        AGE         ADDRESS     SALARY
----------  ----------  ----------  ----------  ----------
1           Paul        32          California  20000.0
2           Allen       25          Texas       15000.0
3           Teddy       23          Norway      20000.0
4           Mark        25          Rich-Mond   65000.0
5           David       27          Texas       85000.0
6           Kim         22          South-Hall  45000.0
```
If you want to DELETE all the records from COMPANY table, you do not need to use WHERE clause with DELETE query, which will be as follows −

```
sql DELETE FROM COMPANY;
```
Now, COMPANY table does not have any record as all the records have been deleted by DELETE statement.
## LIMIT
SQLite LIMIT clause is used to limit the data amount returned by the SELECT statement.
```sql
SELECT column1, column2, columnN 
FROM table_name
LIMIT [no of rows]
```
Following is the syntax of LIMIT clause when it is used along with OFFSET clause.
```sql
SELECT column1, column2, columnN 
FROM table_name
LIMIT [no of rows] OFFSET [row num]
```
SQLite engine will return rows starting from the next row to the given OFFSET as shown below in the last example.

### Example
Consider COMPANY table with the following records −
```
ID          NAME        AGE         ADDRESS     SALARY
----------  ----------  ----------  ----------  ----------
1           Paul        32          California  20000.0
2           Allen       25          Texas       15000.0
3           Teddy       23          Norway      20000.0
4           Mark        25          Rich-Mond   65000.0
5           David       27          Texas       85000.0
6           Kim         22          South-Hall  45000.0
7           James       24          Houston     10000.0
```
Following is an example, which limits the row in the table according to the number of rows you want to fetch from table.

```sql
SELECT * FROM COMPANY LIMIT 6;
```
This will produce the following result.
```
ID          NAME        AGE         ADDRESS     SALARY
----------  ----------  ----------  ----------  ----------
1           Paul        32          California  20000.0
2           Allen       25          Texas       15000.0
3           Teddy       23          Norway      20000.0
4           Mark        25          Rich-Mond   65000.0
5           David       27          Texas       85000.0
6           Kim         22          South-Hall  45000.0
```
However in certain situations, you may need to pick up a set of records from a particular offset. Here is an example, which picks up 3 records starting from the 3rd position.

```sql
SELECT * FROM COMPANY LIMIT 3 OFFSET 2;
```
This will produce the following result.
```
ID          NAME        AGE         ADDRESS     SALARY
----------  ----------  ----------  ----------  ----------
3           Teddy       23          Norway      20000.0
4           Mark        25          Rich-Mond   65000.0
5           David       27          Texas       85000.0
```
## ORDER BY
SQLite ORDER BY clause is used to sort the data in an ascending or descending order, based on one or more columns.

```sql
SELECT column-list 
FROM table_name 
[WHERE condition] 
[ORDER BY column1, column2, .. columnN] [ASC | DESC];
```
You can use more than one column in the ORDER BY clause. Make sure whatever column you are using to sort, that column should be available in the column-list.
### Example
Consider COMPANY table with the following records.
```
ID          NAME        AGE         ADDRESS     SALARY
----------  ----------  ----------  ----------  ----------
1           Paul        32          California  20000.0
2           Allen       25          Texas       15000.0
3           Teddy       23          Norway      20000.0
4           Mark        25          Rich-Mond   65000.0
5           David       27          Texas       85000.0
6           Kim         22          South-Hall  45000.0
7           James       24          Houston     10000.0
```
Following is an example, which will sort the result in descending order by SALARY.

```sql
SELECT * FROM COMPANY ORDER BY SALARY ASC;
```
This will produce the following result.
```
ID          NAME        AGE         ADDRESS     SALARY
----------  ----------  ----------  ----------  ----------
7           James       24          Houston     10000.0
2           Allen       25          Texas       15000.0
1           Paul        32          California  20000.0
3           Teddy       23          Norway      20000.0
6           Kim         22          South-Hall  45000.0
4           Mark        25          Rich-Mond   65000.0
5           David       27          Texas       85000.0
```
Following is an example, which will sort the result in descending order by NAME and SALARY.

```sql
SELECT * FROM COMPANY ORDER BY NAME, SALARY ASC;
```
This will produce the following result.
```
ID          NAME        AGE         ADDRESS     SALARY
----------  ----------  ----------  ----------  ----------
2           Allen       25          Texas       15000.0
5           David       27          Texas       85000.0
7           James       24          Houston     10000.0
6           Kim         22          South-Hall  45000.0
4           Mark        25          Rich-Mond   65000.0
1           Paul        32          California  20000.0
3           Teddy       23          Norway      20000.0
```
Following is an example, which will sort the result in descending order by NAME.

```sql
SELECT * FROM COMPANY ORDER BY NAME DESC;
```
This will produce the following result.
```
ID          NAME        AGE         ADDRESS     SALARY
----------  ----------  ----------  ----------  ----------
3           Teddy       23          Norway      20000.0
1           Paul        32          California  20000.0
4           Mark        25          Rich-Mond   65000.0
6           Kim         22          South-Hall  45000.0
7           James       24          Houston     10000.0
5           David       27          Texas       85000.0
2           Allen       25          Texas       15000.0
```

##  GROUP BY
SQLite GROUP BY clause is used in collaboration with the SELECT statement to arrange identical data into groups.

GROUP BY clause follows the WHERE clause in a SELECT statement and precedes the ORDER BY clause.

Following is the basic syntax of GROUP BY clause. GROUP BY clause must follow the conditions in the WHERE clause and must precede ORDER BY clause if one is used.
```sql
SELECT column-list
FROM table_name
WHERE [ conditions ]
GROUP BY column1, column2....columnN
ORDER BY column1, column2....columnN
```
You can use more than one column in the GROUP BY clause. Make sure whatever column you are using to group, that column should be available in the column-list.

### Example
Consider COMPANY table with the following records.

ID          NAME        AGE         ADDRESS     SALARY
----------  ----------  ----------  ----------  ----------
1           Paul        32          California  20000.0
2           Allen       25          Texas       15000.0
3           Teddy       23          Norway      20000.0
4           Mark        25          Rich-Mond   65000.0
5           David       27          Texas       85000.0
6           Kim         22          South-Hall  45000.0
7           James       24          Houston     10000.0
If you want to know the total amount of salary on each customer, then GROUP BY query will be as follows −

```sql
SELECT NAME, SUM(SALARY) FROM COMPANY GROUP BY NAME;
```
This will produce the following result −
```
NAME        SUM(SALARY)
----------  -----------
Allen       15000.0
David       85000.0
James       10000.0
Kim         45000.0
Mark        65000.0
Paul        20000.0
Teddy       20000.0
```
Now, let us create three more records in COMPANY table using the following INSERT statements.
```sql
INSERT INTO COMPANY VALUES (8, 'Paul', 24, 'Houston', 20000.00 );
INSERT INTO COMPANY VALUES (9, 'James', 44, 'Norway', 5000.00 );
INSERT INTO COMPANY VALUES (10, 'James', 45, 'Texas', 5000.00 );
```
Now, our table has the following records with duplicate names.
```
ID          NAME        AGE         ADDRESS     SALARY
----------  ----------  ----------  ----------  ----------
1           Paul        32          California  20000.0
2           Allen       25          Texas       15000.0
3           Teddy       23          Norway      20000.0
4           Mark        25          Rich-Mond   65000.0
5           David       27          Texas       85000.0
6           Kim         22          South-Hall  45000.0
7           James       24          Houston     10000.0
8           Paul        24          Houston     20000.0
9           James       44          Norway      5000.0
10          James       45          Texas       5000.0
```
Again, let us use the same statement to group-by all the records using NAME column as follows −

```sql
SELECT NAME, SUM(SALARY) FROM COMPANY GROUP BY NAME ORDER BY NAME;
```
This will produce the following result.
```
NAME        SUM(SALARY)
----------  -----------
Allen       15000
David       85000
James       20000
Kim         45000
Mark        65000
Paul        40000
Teddy       20000
```
Let us use ORDER BY clause along with GROUP BY clause as follows −

```sql
SELECT NAME, SUM(SALARY) FROM COMPANY GROUP BY NAME ORDER BY NAME DESC;
```
This will produce the following result.
```
NAME        SUM(SALARY)
----------  -----------
Teddy       20000
Paul        40000
Mark        65000
Kim         45000
James       20000
David       85000
Allen       15000
```
## HAVING
HAVING clause enables you to specify conditions that filter which group results appear in the final results.

The WHERE clause places conditions on the selected columns, whereas the HAVING clause places conditions on groups created by GROUP BY clause.

```sql
SELECT
FROM
WHERE
GROUP BY
HAVING
ORDER BY
```
HAVING clause must follow GROUP BY clause in a query and must also precede ORDER BY clause if used. Following is the syntax of the SELECT statement, including HAVING clause.

```sql
SELECT column1, column2
FROM table1, table2
WHERE [ conditions ]
GROUP BY column1, column2
HAVING [ conditions ]
ORDER BY column1, column2
```
### Example
Consider COMPANY table with the following records.
```
ID          NAME        AGE         ADDRESS     SALARY
----------  ----------  ----------  ----------  ----------
1           Paul        32          California  20000.0
2           Allen       25          Texas       15000.0
3           Teddy       23          Norway      20000.0
4           Mark        25          Rich-Mond   65000.0
5           David       27          Texas       85000.0
6           Kim         22          South-Hall  45000.0
7           James       24          Houston     10000.0
8           Paul        24          Houston     20000.0
9           James       44          Norway      5000.0
10          James       45          Texas       5000.0
```
Following is the example, which will display the record for which the name count is less than 2.

```sql
SELECT * FROM COMPANY GROUP BY name HAVING count(name) < 2;
```
This will produce the following result.
```
ID          NAME        AGE         ADDRESS     SALARY
----------  ----------  ----------  ----------  ----------
2           Allen       25          Texas       15000
5           David       27          Texas       85000
6           Kim         22          South-Hall  45000
4           Mark        25          Rich-Mond   65000
3           Teddy       23          Norway      20000
```
Following is the example, which will display the record for which the name count is greater than 2.
```sql
SELECT * FROM COMPANY GROUP BY name HAVING count(name) > 2;
```
This will produce the following result.
```
ID          NAME        AGE         ADDRESS     SALARY
----------  ----------  ----------  ----------  ----------
10          James       45          Texas       5000
```
## DISTINCT
SQLite DISTINCT keyword is used in conjunction with SELECT statement to eliminate all the duplicate records and fetching only the unique records.

There may be a situation when you have multiple duplicate records in a table. While fetching such records, it makes more sense to fetch only unique records instead of fetching duplicate records.


```sql
SELECT DISTINCT column1, column2,.....columnN 
FROM table_name
WHERE [condition]
```
### Example
Consider COMPANY table with the following records.
```
ID          NAME        AGE         ADDRESS     SALARY
----------  ----------  ----------  ----------  ----------
1           Paul        32          California  20000.0
2           Allen       25          Texas       15000.0
3           Teddy       23          Norway      20000.0
4           Mark        25          Rich-Mond   65000.0
5           David       27          Texas       85000.0
6           Kim         22          South-Hall  45000.0
7           James       24          Houston     10000.0
8           Paul        24          Houston     20000.0
9           James       44          Norway      5000.0
10          James       45          Texas       5000.0
```
First, let us see how the following SELECT query returns duplicate salary records.

```sql
SELECT name FROM COMPANY;
```
This will produce the following result.
```
NAME
----------
Paul
Allen
Teddy
Mark
David
Kim
James
Paul
James
James
```
Now, let us use DISTINCT keyword with the above SELECT query and see the result.

```sql
SELECT DISTINCT name FROM COMPANY;
```
This will produce the following result, where there is no duplicate entry.
```
NAME
----------
Paul
Allen
Teddy
Mark
David
Kim
James
```
## Database Connection Handle
```cpp
typedef struct sqlite3 sqlite3;
```
Each open SQLite database is represented by a pointer to an instance of the opaque structure named "sqlite3"

## Opening A New Database Connection
```cpp
int sqlite3_open(
  const char *filename,   /* Database filename (UTF-8) */
  sqlite3 **ppDb          /* OUT: SQLite db handle */
);
```
These routines open an SQLite database file as specified by the filename argument. 
## Prepared Statement Object
```cpp
typedef struct sqlite3_stmt sqlite3_stmt;
```
An instance of this object represents a single SQL statement that has been compiled into binary form and is ready to be evaluated.

Think of each SQL statement as a separate computer program. The original SQL text is source code. A prepared statement object is the compiled object code. All SQL must be converted into a prepared statement before it can be run.

The life-cycle of a prepared statement object usually goes like this:

1. Create the prepared statement object using sqlite3_prepare_v2().
2. Bind values to parameters using the sqlite3_bind_*() interfaces.
3. Run the SQL by calling sqlite3_step() one or more times.
4. Reset the prepared statement using sqlite3_reset() then go back to step 2. Do this zero or more times.
5. Destroy the object using sqlite3_finalize().
## Compiling An SQL Statement
```cpp
int sqlite3_prepare_v2(
  sqlite3 *db,            /* Database handle */
  const char *zSql,       /* SQL statement, UTF-8 encoded */
  int nByte,              /* Maximum length of zSql in bytes. */
  sqlite3_stmt **ppStmt,  /* OUT: Statement handle */
  const char **pzTail     /* OUT: Pointer to unused portion of zSql */
);
```
1. The first argument, "db", is a database connection obtained from a prior successful call to sqlite3_open(), sqlite3_open_v2() or sqlite3_open16(). The database connection must not have been closed.

2. The second argument, "zSql", is the statement to be compiled, encoded as either UTF-8 or UTF-16. The sqlite3_prepare(), sqlite3_prepare_v2(), and sqlite3_prepare_v3() interfaces use UTF-8, and sqlite3_prepare16(), sqlite3_prepare16_v2(), and sqlite3_prepare16_v3() use UTF-16.

3. If the nByte argument is negative, then zSql is read up to the first zero terminator. If nByte is positive, then it is the number of bytes read from zSql. If nByte is zero, then no prepared statement is generated. If the caller knows that the supplied string is nul-terminated, then there is a small performance advantage to passing an nByte parameter that is the number of bytes in the input string including the nul-terminator.

4. If pzTail is not NULL then *pzTail is made to point to the first byte past the end of the first SQL statement in zSql. These routines only compile the first statement in zSql, so *pzTail is left pointing to what remains uncompiled.
## Binding Values To Prepared Statements
```cpp
int sqlite3_bind_blob(sqlite3_stmt*, int, const void*, int n, void(*)(void*));

int sqlite3_bind_double(sqlite3_stmt*, int, double);
int sqlite3_bind_int(sqlite3_stmt*, int, int);
int sqlite3_bind_null(sqlite3_stmt*, int);
int sqlite3_bind_text(sqlite3_stmt*,int,const char*,int,void(*)(void*));
int sqlite3_bind_value(sqlite3_stmt*, int, const sqlite3_value*);
int sqlite3_bind_zeroblob(sqlite3_stmt*, int, int n);
```
In the SQL statement text input to sqlite3_prepare_v2() and its variants, literals may be replaced by a parameter that matches one of following templates:
```sql
?
?NNN
:VVV
@VVV
$VVV
```
In the templates above, NNN represents an integer literal, and VVV represents an alphanumeric identifier. The values of these parameters (also called "host parameter names" or "SQL parameters") can be set using the sqlite3_bind_*() routines defined here.
## Evaluate An SQL Statement
```cpp
int sqlite3_step(sqlite3_stmt*);
```
After a prepared statement has been prepared using any of sqlite3_prepare_v2(), this function must be called one or more times to evaluate the statement.
## Destroy A Prepared Statement Object
```cpp
int sqlite3_finalize(sqlite3_stmt *pStmt);
```
The sqlite3_finalize() function is called to delete a prepared statement. If the most recent evaluation of the statement encountered no errors or if the statement is never been evaluated, then sqlite3_finalize() returns SQLITE_OK. If the most recent evaluation of statement S failed, then sqlite3_finalize(S) returns the appropriate error code or extended error code.
## Error Codes And Messages
[See in SQLITE web](https://sqlite.org/rescode.html#extrc)
```cpp
const char *sqlite3_errmsg(sqlite3*);
```
## One-Step Query Execution Interface
```cpp
int sqlite3_exec(
  sqlite3*,                                  /* An open database */
  const char *sql,                           /* SQL to be evaluated */
  int (*callback)(void*,int,char**,char**),  /* Callback function */
  void *,                                    /* 1st argument to callback */
  char **errmsg                              /* Error msg written here */
);
```
The sqlite3_exec() interface runs zero or more UTF-8 encoded, semicolon-separate SQL statements passed into its 2nd argument, in the context of the database connection passed in as its 1st argument. If the callback function of the 3rd argument to sqlite3_exec() is not NULL, then it is invoked for each result row coming out of the evaluated SQL statements. The 4th argument to sqlite3_exec() is relayed through to the 1st argument of each callback invocation. If the callback pointer to sqlite3_exec() is NULL, then no callback is ever invoked and result rows are ignored.

If an error occurs while evaluating the SQL statements passed into sqlite3_exec(), then execution of the current statement stops and subsequent statements are skipped. If the 5th parameter to sqlite3_exec() is not NULL then any error message is written into memory obtained from sqlite3_malloc() and passed back through the 5th parameter. To avoid memory leaks, the application should invoke sqlite3_free() on error message strings returned through the 5th parameter of sqlite3_exec() after the error message string is no longer needed. If the 5th parameter to sqlite3_exec() is not NULL and no errors occur, then sqlite3_exec() sets the pointer in its 5th parameter to NULL before returning.

If an sqlite3_exec() callback returns non-zero, the sqlite3_exec() routine returns SQLITE_ABORT without invoking the callback again and without running any subsequent SQL statements.

The 2nd argument to the sqlite3_exec() callback function is the number of columns in the result. The 3rd argument to the sqlite3_exec() callback is an array of pointers to strings obtained as if from sqlite3_column_text(), one for each column. If an element of a result row is NULL then the corresponding string pointer for the sqlite3_exec() callback is a NULL pointer. The 4th argument to the sqlite3_exec() callback is an array of pointers to strings where each entry represents the name of corresponding result column as obtained from sqlite3_column_name().

If the 2nd parameter to sqlite3_exec() is a NULL pointer, a pointer to an empty string, or a pointer that contains only whitespace and/or SQL comments, then no SQL statements are evaluated and the database is not changed.


### CallBack Function
```cpp
static int my_special_callback(void *unUsed, int count, char **data, char **columns)
{
    for (int idx = 0; idx < count; idx++) {
        printf("The data in column \"%s\" is: %s\n", columns[idx], data[idx]);
    }
    return 0;
}
```









