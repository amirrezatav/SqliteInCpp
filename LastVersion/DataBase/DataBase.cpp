#include "DataBase.h"
DataBase::DataBase()
{

}
DataBase::~DataBase()
{
	Close();
}
bool DataBase::Open(string path, bool ThrowExc)
{
	int res = sqlite3_open(path.c_str(),&db);
	if (res != SQLITE_OK && ThrowExc)
	{
		ThrowError(SQLITE_OK);
	}
	return true;
}
void DataBase::Close(bool ThrowExc )
{
	int res = sqlite3_close(db);
	if (res != SQLITE_OK && ThrowExc)
		ThrowError(db);
}
#pragma region Insertion
void DataBase::InsertCustomer(int username, int listid, bool ThrowExc )
{
	Lock();
	const char* sql = "INSERT INTO Customer (Username,ListId)VALUES(?, ?);";
	sqlite3_stmt* stmt;
	int res = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
	if (res != SQLITE_OK && ThrowExc)
	{
		UnLock();
		sqlite3_finalize(stmt);
		ThrowError(db);
	}
	res = sqlite3_bind_int(stmt ,1, username);
	if (res != SQLITE_OK && ThrowExc)
	{
		UnLock();
		sqlite3_finalize(stmt);
		ThrowError(db);
	}
	res = sqlite3_bind_int(stmt, 2, listid);
	if (res != SQLITE_OK && ThrowExc)
	{
		UnLock();
		sqlite3_finalize(stmt);
		ThrowError(db);
	}
	res = sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	UnLock();
	if (res != SQLITE_DONE && ThrowExc)
		ThrowError(db);
}
void DataBase::InsertList(int productid, int listid, bool ThrowExc )
{
	Lock();
	const char* sql = "INSERT INTO List (ProductId,ListId,DateTime)VALUES(?, ?, datetime('now', 'localtime'));";
	sqlite3_stmt* stmt;
	int res = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
	if (res != SQLITE_OK && ThrowExc)
	{
		UnLock();
		sqlite3_finalize(stmt);
		ThrowError(db);
	}
	res = sqlite3_bind_int(stmt, 1, productid);
	if (res != SQLITE_OK && ThrowExc)
	{
		UnLock();
		sqlite3_finalize(stmt);
		ThrowError(db);
	}
	res = sqlite3_bind_int(stmt, 2, listid);
	if (res != SQLITE_OK && ThrowExc)
	{
		UnLock();
		sqlite3_finalize(stmt);
		ThrowError(db);
	}
	res = sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	UnLock();
	if (res != SQLITE_DONE && ThrowExc)
		ThrowError(db);
}
void DataBase::InsertProduct(int id, string name, int filesize, string filename, bool ThrowExc)
{
	Lock();
	const char* sql = "INSERT INTO Product (Id,Name,File,FileName)VALUES(?, ?, ? ,?);";
	sqlite3_stmt* stmt;
	int res = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
	if (res != SQLITE_OK && ThrowExc)
	{
		UnLock();
		sqlite3_finalize(stmt);
		ThrowError(db);
	}
	res = sqlite3_bind_int(stmt, 1, id);
	if (res != SQLITE_OK && ThrowExc)
	{
		UnLock();
		sqlite3_finalize(stmt);
		ThrowError(db);
	}
	res = sqlite3_bind_text(stmt, 2, name.c_str(), name.size() , nullptr);
	if (res != SQLITE_OK && ThrowExc)
	{
		UnLock();
		sqlite3_finalize(stmt);
		ThrowError(db);
	}
	res = sqlite3_bind_zeroblob(stmt, 3, filesize);
	if (res != SQLITE_OK && ThrowExc)
	{
		UnLock();
		sqlite3_finalize(stmt);
		ThrowError(db);
	}
	res = sqlite3_bind_text(stmt, 4, filename.c_str() , filename.size(),nullptr);
	if (res != SQLITE_OK && ThrowExc)
	{
		UnLock();
		sqlite3_finalize(stmt);
		ThrowError(db);
	}
	res = sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	UnLock();
	if (res != SQLITE_DONE && ThrowExc)
		ThrowError(db);
}
int DataBase::GetProductRowId(int id, bool ThrowExc)
{
	const char* sql = "Select rowid from product where id == ?";
	sqlite3_stmt* stmt;
	int res = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
	if (res != SQLITE_OK && ThrowExc)
	{
		UnLock();
		sqlite3_finalize(stmt);
		ThrowError(db);
	}
	res = sqlite3_bind_int(stmt, 1, id);
	if (res != SQLITE_OK && ThrowExc)
	{
		UnLock();
		sqlite3_finalize(stmt);
		ThrowError(db);
	}
	res = sqlite3_step(stmt);
	return sqlite3_column_int(stmt, 0);
}
string DataBase::GetProductFileName(int id, bool ThrowExc)
{
	const char* sql = "Select filename from product where id == ?";
	sqlite3_stmt* stmt;
	int res = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
	if (res != SQLITE_OK && ThrowExc)
	{
		UnLock();
		sqlite3_finalize(stmt);
		ThrowError(db);
	}
	res = sqlite3_bind_int(stmt, 1, id);
	if (res != SQLITE_OK && ThrowExc)
	{
		UnLock();
		sqlite3_finalize(stmt);
		ThrowError(db);
	}
	res = sqlite3_step(stmt);
	return string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
}
sqlite3_blob* DataBase::OpenProductFile(int rowid,bool readonly , bool ThrowExc )
{
	sqlite3_blob* file = nullptr;
	int res = sqlite3_blob_open(db, "main", "Product", "File", rowid, readonly ? 0 : 1, &file);
	if (res != SQLITE_OK && ThrowExc)
	{
		ThrowError(SQLITE_OK);
	}
	return file;
}
void DataBase::WriteProductFile(sqlite3_blob* file, char* Buffer, long long Size, long long index, bool ThrowExc )
{
	Lock();
	int res = sqlite3_blob_write(file , Buffer , Size, index);
	UnLock();
	if (res != SQLITE_OK && ThrowExc)
	{
		CloseProductFile(file);
		throw exception("Error");
	}
}
void DataBase::GetProductFile(int id, string path)
{
	int rowid = GetProductRowId(id);
	sqlite3_blob* file = OpenProductFile(rowid, 1);
	long long size = sqlite3_blob_bytes(file);
	long long index = 0;
	const int buffersize = 20 * 1024;
	char Buffer[buffersize];
	string Path = path + "\\" + GetProductFileName(id);
	ofstream ofs (Path,ios::binary);
	if (ofs.good())
	{
		while (index < size)
		{
			int read = size - index < buffersize ? size - index : buffersize;
			sqlite3_blob_read(file, Buffer, read, index);
			ofs.write(Buffer, read);
			index += read;
		}
	}
	ofs.close();
	CloseProductFile(file);
}
void DataBase::CloseProductFile(sqlite3_blob* file, bool ThrowExc )
{
	Lock();
	int res = sqlite3_blob_close(file);
	UnLock();
	if (res != SQLITE_OK && ThrowExc)
	{
		UnLock();
		ThrowError(db);
	}
}
//#pragma endregion
//#pragma region Delete
//void DataBase::DeleteCustomer(int username = 0, int listid = 0, bool ThrowExc = true)
//{
//
//}
//void DataBase::DeleteCustomer(int product = 0, int listid = 0, bool ThrowExc = true)
//{
//
//}
//void DataBase::DeleteProduct(int id = 0, string name = "", string filename = "", bool ThrowExc = true)
//{
//
//}
//#pragma endregion
//#pragma region Update
void DataBase::UpdateCustomerUsername(int usernamelast, int usernameNew, bool ThrowExc)
{
	Lock();
	const char* sql = "UPDATE Customer set username = ? where username = ?;";
	sqlite3_stmt* stmt;
	int res = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
	if (res != SQLITE_OK && ThrowExc)
	{
		UnLock();
		sqlite3_finalize(stmt);
		ThrowError(db);
	}
	res = sqlite3_bind_int(stmt, 1, usernameNew);
	if (res != SQLITE_OK && ThrowExc)
	{
		UnLock();
		sqlite3_finalize(stmt);
		ThrowError(db);
	}
	res = sqlite3_bind_int(stmt, 2, usernamelast);
	if (res != SQLITE_OK && ThrowExc)
	{
		UnLock();
		sqlite3_finalize(stmt);
		ThrowError(db);
	}
	res = sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	UnLock();
	if (res != SQLITE_DONE && ThrowExc)
		ThrowError(db);
}
//void database::updatecustomerlistid(int username, int listidnew, bool throwexc = true)
//{
//
//}
//#pragma endregion
#ifndef Other
int DataBase::GetCount(string tablename)
{
	string sql = "Select count(*) from " + tablename;
	sqlite3_stmt* stmt;
	int res = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
	if (res != SQLITE_OK)
	{
		UnLock();
		sqlite3_finalize(stmt);
		ThrowError(db);
	}
	res = sqlite3_step(stmt);
	if (res != SQLITE_OK )
	{
		UnLock();
		sqlite3_finalize(stmt);
		ThrowError(db);
	}
	return sqlite3_column_int(stmt, 0);
}
Book* DataBase::SearchBook(string bookname, int& BookCount, bool ThrowExc)
{
	Lock();
	bookname = "%" + bookname + "%";
	const char* sql = "Select count(*) from product where name like ?;";
	sqlite3_stmt* stmt;
	int res = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
	if (res != SQLITE_OK && ThrowExc)
	{
		UnLock();
		sqlite3_finalize(stmt);
		ThrowError(db);
	}
	res = sqlite3_bind_text(stmt, 1, bookname.c_str(), bookname.size(), nullptr);
	if (res != SQLITE_OK && ThrowExc)
	{
		UnLock();
		sqlite3_finalize(stmt);
		ThrowError(db);
	}
	res = sqlite3_step(stmt);
	if (res != SQLITE_OK && ThrowExc)
	{
		UnLock();
		sqlite3_finalize(stmt);
		ThrowError(db);
	}
	BookCount = sqlite3_column_int(stmt, 0);
	sql = "Select id,name,filename form product where name like ? ;";
	res = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
	if (res != SQLITE_OK && ThrowExc)
	{
		UnLock();
		sqlite3_finalize(stmt);
		ThrowError(db);
	}
	res = sqlite3_bind_text(stmt, 1, bookname.c_str(), bookname.size(), nullptr);
	if (res != SQLITE_OK && ThrowExc)
	{
		UnLock();
		sqlite3_finalize(stmt);
		ThrowError(db);
	}
	Book* books = new Book[BookCount];
	/*while (sqlite3_step(stmt) != SQLITE_DONE)
	{

	}*/
	/*while (sqlite3_step(stmt) == SQLITE_ROW)
	{

	}*/
	for (int i = 0; i < BookCount; i++)
	{
		sqlite3_step(stmt);
		Book book;
		book.BookId = sqlite3_column_int(stmt, 0);
		book.BookName = string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
		book.filename = string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
		books[i] = book;
	}
	sqlite3_finalize(stmt);
	UnLock();
	return books;

}
void DataBase::Lock()
{
	sqlite3_mutex_enter(sqlite3_db_mutex(db));
}
void DataBase::UnLock()
{
	sqlite3_mutex_leave(sqlite3_db_mutex(db));
}
#endif // !Other