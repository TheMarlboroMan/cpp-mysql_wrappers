#ifndef MYSQLDB_CONN_MANAGER_H
#define MYSQLDB_CONN_MANAGER_H

#include <string>

#include "connection.h"

namespace mysql_db {

class conn_manager {

	public:

								conn_manager(const std::string&, const std::string&, const std::string&, const std::string&);
	mysql_db::connection&		get();
	virtual int					last_insert_id();
	virtual int					execute(mysql_db::prepared_query&);
	virtual mysql_db::resultset	query(mysql_db::prepared_query&);

	protected:

	mysql_db::connection		connection;
	mysql_db::prepared_query	pq_last_insert_id;
};

}

#endif
