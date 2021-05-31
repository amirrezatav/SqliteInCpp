#include <iostream>
#include <fstream>
#include "sqlite3.h"
#include <Cstring>
using namespace std;

static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
	for (size_t i = 0; i < argc; i++)
	{
		cout << azColName[i] << " : "; // col Name
		if (i == 3)
		{
			string path = argv[0];
			path += ".pdf"; // Change it
			ofstream ofs(path, ios::binary);
			char* buf = argv[3];
			int size = 1289468; // Static File Size You shoud know file Size (Save it in Database) // Change it
			ofs.write(buf, size);
			ofs.close();
			clog << "File Ctreated." << endl;
		}
		if (argv[i] != NULL)
		{
			cout << argv[0] << endl;
		}
		else
		{
			cout << "NULL" << endl;
		}
		// cout << argv[i] ? argv[i] : "NULL";
	}
	return 0;
}
int main()
{
	sqlite3* db;
	int res;
	string sql;
	
	res = sqlite3_open("FirstDataBase.db", &db);
	if (res)
	{
		cerr << sqlite3_errmsg(db) << endl;
		return 0;
	}
	else
	{
		clog << "Opened DataBase Successfully" << endl;
	}

	sqlite3_stmt* stmt = NULL;
												   // index  1   2              3
	sql = "INSERT INTO Student (ID,FName,LName,Photo) VALUES(? , ? , 'Tavkoli', ? ); ";
	res = sqlite3_prepare_v2(db, sql.c_str() , -1, &stmt, NULL);
	if (res != SQLITE_OK)
	{
		cerr << "Prepare Failed: " << sqlite3_errmsg(db) << endl;
		return 0;
	}

	ifstream ifs("C:\\Users\\amirr\\Desktop\\ALL\\connect.pdf" , ios::binary);
	int size = ifs.seekg(0, ios::end).tellg();
	ifs.seekg(0);
	char* buffer = new char[size];
	memset(buffer, 0, size);
	ifs.read(buffer, size);
	ifs.close();

	res = sqlite3_bind_blob(stmt, 3 , buffer, size, SQLITE_STATIC);
	if (res != SQLITE_OK)
		cerr << "Bind Failed : " << sqlite3_errmsg(db) << endl;

	res = sqlite3_bind_int(stmt, 1, 232332);
	if (res != SQLITE_OK)
		cerr << "Bind Failed : " << sqlite3_errmsg(db) << endl;

	res = sqlite3_bind_text(stmt, 2, "Amirreza", strlen("Amirreza"), NULL);
	if (res != SQLITE_OK)
		cerr << "Bind Failed : " << sqlite3_errmsg(db) << endl;

	res = sqlite3_step(stmt);
	if(res != SQLITE_DONE)
		cerr << "Execution Failed: " << sqlite3_errmsg(db) << endl;

	sqlite3_finalize(stmt);

	sql = "SELECT * from Student";
	char data[] = "Callback function called";
	char* err;
	res = sqlite3_exec(db, sql.c_str(), callback, (void*)data, &err);

	sqlite3_close(db);
}