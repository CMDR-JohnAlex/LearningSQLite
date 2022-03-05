// JOHN ALEXANDER LE ROUX
#ifndef DATABASE_HPP
#define DATABASE_HPP
// User-Defined Headers

// 3rd Party Library Headers
#include "../../contrib/sqlite/sqlite3.h"

// Standard Library Headers
#include <iostream>
#include <vector>
#include <unordered_map>
#include <optional>

class Database
{
private:
	// Private Variables/Functions
	// Private members of a class A are not accessible outside of A's code, or from the code of any class derived from A.
protected:
	// Protected Variables/Functions
	// Protected members of a class A are not accessible outside of A's code, but is accessible from the code of any class derived from A.
public:
	// Public Variables/Functions
	// Public members of a class A are accessible for all and everyone.
	sqlite3* db = nullptr;

	Database(const std::string& path) {
		auto exit = sqlite3_open(path.c_str(), &db);
		if (exit != SQLITE_OK) {
			auto error = std::string{ "sqlite3_open failed: " } + sqlite3_errstr(exit);
			throw std::runtime_error(error);
		}
	}

	~Database() {
		sqlite3_close_v2(db);
	}

	struct query_result {
		std::vector<std::unordered_map<std::string, std::string>> rows;
	};

	int createTable(std::string sql);
	void exec_void(const std::string& sql);
	Database::query_result exec(const std::string& sql);
	static int sqlite_exec_callback(void* data, int argc, char** values, char** columns);
};

#endif
