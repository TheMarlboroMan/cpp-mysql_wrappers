#ifndef MYSQLDB_DATABASE_H
#define MYSQLDB_DATABASE_H

#include <memory>
#include <iostream>
#include <stack>
#include <string>
#include <sstream>

#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/exception.h>

#include "exception.h"
#include "resultset.h"
#include "dbquery.h"
#include "prepared_query.h"

namespace mysql_db {

class connection {

	public:

							connection();
	 						connection(const std::string&, const std::string&, const std::string&);
							connection(const std::string&, const std::string&, const std::string&, const std::string&);

	dbquery 				generate_query();
	dbquery 				generate_query(const std::string&);
	prepared_query 			generate_prepared_query(const std::string&);
	resultset 				query(dbquery&, const std::string&);
	resultset 				query(prepared_query&);
	resultset				query(const std::string&);
	int 					execute(dbquery& , const std::string&);
	int						execute(prepared_query&);
	int						execute(const std::string&);
	void 					disconnect();
	void 					set_connection_params(const std::string&, const std::string&, const std::string&);
	void 					connect();
	void 					use_db(const std::string& bbdd);
	bool					is_connected() const {return conn.get();}

	private:

	struct connection_data
	{
		std::string			host,
							user,
							pass;

		bool				is_ok() const {
			return host.size() && user.size() && pass.size();
		}
	}						conn_data;

	sql::Driver * 			driver;
	std::shared_ptr<sql::Connection> 	conn;
};

}

#endif
