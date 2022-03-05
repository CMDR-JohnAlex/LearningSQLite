// JOHN ALEXANDER LE ROUX
#include <iostream>
#include "database/database.hpp"

Database database{ "data/database.db" };

int main(int argc, char* argv[])
{
	std::string sql = "CREATE TABLE IF NOT EXISTS GRADES("
		"ID INTEGER PRIMARY KEY AUTOINCREMENT, "
		"NAME      TEXT NOT NULL, "
		"LNAME     TEXT NOT NULL, "
		"AGE       INT  NOT NULL, "
		"ADDRESS   CHAR(50), "
		"GRADE     CHAR(1) );";
	database.createTable(sql);



	sql = ("INSERT INTO GRADES (NAME, LNAME, AGE, ADDRESS, GRADE) VALUES('Alice', 'Chapa', 35, 'Tampa', 'A');"
		"INSERT INTO GRADES (NAME, LNAME, AGE, ADDRESS, GRADE) VALUES('Bob', 'Lee', 20, 'Dallas', 'B');"
		"INSERT INTO GRADES (NAME, LNAME, AGE, ADDRESS, GRADE) VALUES('Fred', 'Cooper', 24, 'New York', 'C');");
	database.exec_void(sql);



	sql = ("UPDATE GRADES SET GRADE = 'A' WHERE LNAME = 'Cooper'");
	database.exec_void(sql);



	sql = "SELECT * FROM GRADES;";
	auto result = database.exec(sql);
	for (const auto& row : result.rows)
	{
		for (const auto& [column, value] : row)
		{
			std::cout << column << " => " << value << '\n';
		}
		std::cout << '\n';
	}



	sql = "DELETE FROM GRADES;";
	database.exec_void(sql);
	return(0);
}
