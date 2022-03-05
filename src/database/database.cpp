// JOHN ALEXANDER LE ROUX
#include "database.hpp"

int Database::createTable(std::string sql)
{
	char* messageError;
	/* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
	int exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError);
	if (exit != SQLITE_OK) {
		std::cout << "Error in createTable function.\n";
		sqlite3_free(messageError);
	}
	else
		std::cout << "Table created Successfully\n";
	return exit;
}

Database::query_result Database::exec(const std::string& sql)
{
	Database::query_result result = {};
	char* messageError = nullptr;
	int res = sqlite3_exec(db, sql.c_str(), sqlite_exec_callback, &result, &messageError);
	if (res != SQLITE_OK) {
		auto error = std::string{ "sqlite3_exec failed: " } + sqlite3_errstr(res) + ": " + (messageError ? messageError : "");
		sqlite3_free(messageError);
		throw std::runtime_error(error);
	}
	return result;
}

void Database::exec_void(const std::string& sql)
{
	char* messageError = nullptr;
	int res = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &messageError);
	if (res != SQLITE_OK) {
		auto error = std::string{ "sqlite3_exec failed: " } + sqlite3_errstr(res) + ": " + (messageError ? messageError : "");
		sqlite3_free(messageError);
		throw std::runtime_error(error);
	}
}

int Database::sqlite_exec_callback(void* data, int argc, char** values, char** columns)
{
	auto result = static_cast<Database::query_result*>(data);
	auto& row = result->rows.emplace_back();
	for (int i = 0; i < argc; i++)
		row[columns[i]] = values[i];
	return 0;
}