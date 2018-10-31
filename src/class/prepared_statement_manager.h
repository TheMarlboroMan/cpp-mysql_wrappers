#ifndef MYSQLDB_PREPARED_STATEMENT_MANAGER_H
#define MYSQLDB_PREPARED_STATEMENT_MANAGER_H

#include <map>

#include "connection.h"

namespace mysql_db {

enum class statements {};

class prepared_statement_manager {

	public:
										prepared_statement_manager(mysql_db::connection&);
	void 								check();
	virtual mysql_db::prepared_query&	get(statements);

	protected:

	void 								prepare(statements);
	void 								build_strings();

	mysql_db::connection&							conn;
	std::map<statements, std::string> 				qstr_map;
	std::map<statements, mysql_db::prepared_query>	stmt_map;
};

}

#endif
