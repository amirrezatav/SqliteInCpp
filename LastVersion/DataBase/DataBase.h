#ifndef DATABASE_H
#define DATABASE_H
#include <string>
#include "sqlite3.h"
#include <fstream>
#define ThrowError(db) throw exception(sqlite3_errmsg(db));
using namespace std;
struct Book
{
	int BookId;
	string BookName;
	string filename;
};
class DataBase
{
private:
	sqlite3* db;
public:
	DataBase();
	~DataBase();
	bool Open(string db , bool ThrowExc = true);
	void Close( bool ThrowExc = true);
#pragma region Insertion
	void InsertCustomer(int username, int listid, bool ThrowExc = true);
	void InsertList(int productid, int listid, bool ThrowExc = true);
	void InsertProduct(int id,string name ,int filesize,string filename, bool ThrowExc = true);
	int GetProductRowId(int id, bool ThrowExc = true);
	sqlite3_blob* OpenProductFile(int rowid, bool readonly ,bool ThrowExc = true);
	void WriteProductFile(sqlite3_blob* file,char*Buffer,long long Size , long long index, bool ThrowExc = true);
	void GetProductFile(int id , string path);
	void CloseProductFile(sqlite3_blob* file, bool ThrowExc = true);
	string GetProductFileName(int id, bool ThrowExc = true);
#pragma endregion
//#pragma region Delete
//	void DeleteCustomer(int username , int listid , bool ThrowExc );
//	void DeleteCustomer(int product = 0, int listid , bool ThrowExc );
//	void DeleteProduct(int id = 0, string name ="",  string filename = "", bool ThrowExc = true);
//#pragma endregion
//#pragma region Update
	void UpdateCustomerUsername(int usernamelast , int usernameNew, bool ThrowExc = true);
//	void UpdateCustomerListId(int username , int ListIdNew, bool ThrowExc = true);
//#pragma endregion
#ifndef Other
	int GetCount(string tablename);
	Book* SearchBook(string bookname,int &BookCount, bool ThrowExc = true);
	void Lock();
	void UnLock();
#endif // !Other


};
#endif // !DATABASE_H
