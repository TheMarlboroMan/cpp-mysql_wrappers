#ifndef MYSQLDB_DBQUERY_H
#define MYSQLDB_DBQUERY_H

#include <memory>
#include <string>

#include "resultset.h"

namespace mysql_db {

class connection;

//!The class query can only be manipulated from the connection.
class dbquery {

	public:

	explicit		 				operator bool() const;
	bool	 						is_ok() const;
									dbquery(sql::Statement * s);
									dbquery();

	friend class 					connection;

	private:

	std::shared_ptr<sql::Statement> statement;

	resultset 						query(const std::string& t);
	int 							execute(const std::string& t);
};

}
#endif
