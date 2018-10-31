#include "prepared_statement_manager_lock.h"

using namespace mysql_db;

prepared_statement_manager_lock::prepared_statement_manager_lock(mysql_db::connection& _conn):
 	prepared_statement_manager(_conn){

}


mysql_db::prepared_query& prepared_statement_manager_lock::get(statements _index) {

	if(!stmt_map.count(_index)) {
		prepare(_index);
	}

	mtx.lock();
	stmt_map[_index].lock();
	stmt_map[_index].clear();
	mtx.unlock();
	return stmt_map[_index];
}
