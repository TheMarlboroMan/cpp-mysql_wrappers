#include "prepared_statement_manager.h"

using namespace mysql_db;

prepared_statement_manager::prepared_statement_manager(mysql_db::connection& _conn):
 	conn(_conn){

	build_strings();
}

void prepared_statement_manager::check() {

	for(const auto& pair : qstr_map) {
		prepare(pair.first);
	}

}
void prepared_statement_manager::prepare(statements _index) {

	stmt_map.insert({_index, conn.generate_prepared_query(qstr_map.at(_index))});
}

void prepared_statement_manager::build_strings() {

	//qstr_map[statements::something]="SELECT * FROM somewhere WHERE this = ?"
}

mysql_db::prepared_query& prepared_statement_manager::get(statements _index) {

	if(!stmt_map.count(_index)) {
		prepare(_index);
	}

	stmt_map[_index].clear();
	return stmt_map[_index];
}
