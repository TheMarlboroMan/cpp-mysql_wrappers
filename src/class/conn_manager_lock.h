#ifndef MYSQLDB_CONN_MANAGER_LOCK_H
#define MYSQLDB_CONN_MANAGER_LOCK_H

#include <mutex>

#include "conn_manager.h"

namespace mysql_db {

class conn_manager_lock:
 	public conn_manager{

	public:
								conn_manager_lock(const std::string&, const std::string&, const std::string&, const std::string&);
	virtual int					last_insert_id();
	virtual int					execute(mysql_db::prepared_query&);
	virtual mysql_db::resultset	query(mysql_db::prepared_query&);

	private:

	std::mutex					mtx;
};

}

#endif
