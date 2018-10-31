#include "prepared_query.h"
#include "exception.h"

#include <string>

using namespace mysql_db;

prepared_query::prepared_query(sql::PreparedStatement * ps, const std::string& _rs)
	:statement(ps), raw_statement(_rs) {

}

prepared_query::prepared_query(const prepared_query& c)
	:statement(c.statement), raw_statement(c.raw_statement) {

}

prepared_query::prepared_query() {

}

prepared_query& prepared_query::set_int(unsigned int _index, int _val) {

	try {
		statement->setInt(_index, _val);
		return *this;
	}
	catch(std::exception& e) {
		throw set_value_exception(_index, _val, raw_statement, e.what());
	}
}

prepared_query& prepared_query::set_double(unsigned int _index, double _val) {

	try {
		statement->setDouble(_index, _val);
		return *this;
	}
	catch(std::exception& e) {
		throw set_value_exception(_index, _val, raw_statement, e.what());
	}
}

prepared_query& prepared_query::set_string(unsigned int _index, const std::string& _val) {

	try {
		statement->setString(_index, _val);
		return *this;
	}
	catch(std::exception& e) {
		throw set_value_exception(_index, _val, raw_statement, e.what());
	}
}

prepared_query& prepared_query::set_null(unsigned int _index) {

	try {
		statement->setNull(_index, 0);
		return *this;
	}
	catch(std::exception& e) {
		throw set_value_exception(_index, raw_statement, e.what());
	}
}

prepared_query& prepared_query::clear() {

	statement->clearParameters();
	return *this;
}

prepared_query& prepared_query::lock() {

	mtx.lock();
	return *this;
}

prepared_query& prepared_query::unlock() {

	mtx.unlock();
	return *this;
}

prepared_query::operator bool() const {

	return is_ok();
}

bool prepared_query::is_ok() const {

	return nullptr!=statement;
}

resultset prepared_query::query() {

	try {
		return resultset(statement);
	}
	catch(std::exception& e) {

		std::string err=std::string(e.what())+
			+" for prepared query '"
			+raw_statement
			+"'";

		throw exception(err);
	}
}

int prepared_query::execute() {

	try {
		return statement->executeUpdate();
	}
	catch(std::exception& e) {

		std::string err=std::string(e.what())+
			+" for prepared execution '"
			+raw_statement
			+"'";

		throw exception(err);
	}
}
