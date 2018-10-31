#include "dbquery.h"
#include "exception.h"

using namespace mysql_db;

dbquery::dbquery(sql::Statement * s)
	:statement(s) {

}

dbquery::dbquery() {

}

dbquery::operator bool() const {
	return is_ok();
}

bool dbquery::is_ok() const {

	return nullptr!=statement;
}

resultset dbquery::query(const std::string& _qstr) {

	try {
		return resultset(statement, _qstr);
	}
	catch(std::exception& e) {

		std::string err=std::string(e.what())
			+" for query '"
			+_qstr
			+"'";

		throw exception(err);
	}
}

int dbquery::execute(const std::string& _qstr) {

	try {
		return statement->executeUpdate(_qstr);
	}
	catch(std::exception& e) {

		std::string err=std::string(e.what())+
			+" for execution '"
			+_qstr
			+"'";

		throw exception(err);
	}
}
