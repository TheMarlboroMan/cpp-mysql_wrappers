#include "conn_manager_lock.h"

using namespace mysql_db;

conn_manager_lock::conn_manager_lock(const std::string& _host, const std::string& _user, const std::string& _pass, const std::string& _name): conn_manager(_host, _user, _pass, _name) {

}

int conn_manager_lock::execute(mysql_db::prepared_query& _pq) {

	mtx.lock();
	int result=connection.execute(_pq);
	mtx.unlock();
	_pq.unlock();
	return result;
}

mysql_db::resultset conn_manager_lock::query(mysql_db::prepared_query& _pq) {

	mtx.lock();
	auto result=connection.query(_pq);
	mtx.unlock();
	_pq.unlock();
	return result;
}

int conn_manager_lock::last_insert_id() {

	pq_last_insert_id.lock();
	auto rs=query(pq_last_insert_id);
	rs.next();
	auto result=rs.get_int("id");
	pq_last_insert_id.unlock();
	return result;
}
