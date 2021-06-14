#include <iostream>
#include "DataBase.h"

int main()
{
	DataBase db;
	try
	{
		if (db.Open("..\\Uni.db"))
		{
			db.UpdateCustomerUsername(1050, 1051);
		}
	}
	catch (const std::exception& ex)
	{
		cerr << ex.what();
	}
}