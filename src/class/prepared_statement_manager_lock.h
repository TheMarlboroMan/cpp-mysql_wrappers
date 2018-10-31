#ifndef MYSQLDB_PREPARED_STATEMENT_MANAGER_LOCK_H
#define MYSQLDB_PREPARED_STATEMENT_MANAGER_LOCK_H

#include "prepared_statement_manager.h"
#include <mutex>

namespace mysql_db {

class prepared_statement_manager_lock:
 	public prepared_statement_manager {

	public:
										prepared_statement_manager_lock(mysql_db::connection&);
	virtual mysql_db::prepared_query&	get(statements);

	private:

	std::mutex							mtx;
};

}

#endif
