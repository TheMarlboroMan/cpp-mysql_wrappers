#include "conn_manager.h"

using namespace mysql_db;

conn_manager::conn_manager(const std::string& _host, const std::string& _user, const std::string& _pass, const std::string& _name):
	connection(_host, _user, _pass, _name), pq_last_insert_id(connection.generate_prepared_query("SELECT LAST_INSERT_ID() AS id")) {

}

mysql_db::connection&	conn_manager::get() {

	return connection;
}


int conn_manager::execute(mysql_db::prepared_query& _pq) {

	return connection.execute(_pq);
}

mysql_db::resultset conn_manager::query(mysql_db::prepared_query& _pq) {

	return connection.query(_pq);
}

int conn_manager::last_insert_id() {

	auto rs=query(pq_last_insert_id);
	rs.next();
	return rs.get_int("id");
}
