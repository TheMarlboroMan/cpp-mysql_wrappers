#ifndef MYSQLDB_RESULTSET_H
#define MYSQLDB_RESULTSET_H

#include <memory>
#include <string>

#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/exception.h>

namespace mysql_db {

class resultset {
	public:

	//Constructor preparado para recibir un statment con texto. Atención,
	//porque puede lanzar!!!. En un principio lo usaríamos sólo desde dentro
	//de la clase BBDD_Mysql al lanzar una consulta (en cuyo caso estaría
	//controlado) pero por si acaso.

									resultset(std::shared_ptr<sql::Statement> pstat, const std::string& texto);

	//Constructor para un prepared statement
									resultset(std::shared_ptr<sql::PreparedStatement> ppstat);
									resultset();

									explicit operator bool() const;
	bool 							is_ok() const;
	bool 							first();
	bool 							last();
	bool							next();
	bool							previous();
	bool 							get_row() const;
	bool 							is_first() const;
	bool 							is_before_first() const;

	int 							find_column(const std::string& c);

	int 							get_int(const std::string& c) const;
	std::string						get_string(const std::string& c) const;
	double 							get_double(const std::string& c) const;

	int 							get_int(unsigned int c) const;
	std::string						get_string(unsigned int c) const;
	double 							get_double(unsigned int c) const;

	int 							get_total() const;

	private:

	std::shared_ptr<sql::ResultSet> rs;
	mutable int 					total;

	void 							calculate_total() const;

};
}

#endif
