#ifndef MYSQLDB_PREPARED_QUERY_H
#define MYSQLDB_PREPARED_QUERY_H

#include <memory>
#include <string>
#include <mutex>

#include "resultset.h"

namespace mysql_db {

class connection;

//!The class query can only be manipulated from the connection.
class prepared_query {

	public:

							prepared_query(sql::PreparedStatement * ps, const std::string&);
							prepared_query(const prepared_query& c);
							prepared_query();
	prepared_query&			clear();
	prepared_query&			set_int(unsigned int c, int val);
	prepared_query&			set_double(unsigned int c, double val);
	prepared_query&			set_string(unsigned int c, const std::string& val);
	prepared_query&			set_null(unsigned int c);
	prepared_query&			lock();
	prepared_query&			unlock();


	explicit 				operator bool() const;
	bool 					is_ok() const;

	friend class 			connection;

	private:

	resultset 				query();
	int 					execute();

	std::shared_ptr<sql::PreparedStatement> statement;
	std::string				raw_statement;

	//!The mutex will only be engaged in the relevant managers.
	std::mutex				mtx;
};

}
#endif
