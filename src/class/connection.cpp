#include <iostream>

#include "exception.h"
#include "connection.h"

using namespace mysql_db;

connection::connection()
	:driver(nullptr) {

}

connection::connection(const std::string& _host, const std::string& _user, const std::string& _pass)
	:driver(nullptr) {
	set_connection_params(_host, _user, _pass);
	connect();
}

connection::connection(const std::string& _host, const std::string& _user, const std::string& _pass, const std::string& _name)
	try :driver(nullptr) {
	set_connection_params(_host, _user, _pass);

	connect();
	use_db(_name);
}
catch(exception& e) {
	throw e;
}

void connection::connect() {

	if(!conn_data.is_ok()) {
		throw exception("Unable to connect: connection data must be specified");
	}

	if(!driver) {
		driver=get_driver_instance();
		if(!driver) {
			throw exception("Unable to get mysql driver instance");
		}
	}

	try {
		conn=std::shared_ptr<sql::Connection>(driver->connect(conn_data.host, conn_data.user, conn_data.pass));
	}
	catch(std::exception& e) {
		throw exception(std::string("Could not connect to database : ")+e.what());
	}
}

void connection::use_db(const std::string& _bbdd) {

	if(!conn) {
		throw exception("Unable to use database "+_bbdd);
	}

	conn->setSchema(_bbdd);
}

void connection::disconnect() {

	if(!conn || conn->isClosed()) {
		throw exception("Unable to disconnect from database");
	}

	conn->close();
	conn.reset();
}

void connection::set_connection_params(const std::string& _host, const std::string& _user, const std::string& _pass) {

	conn_data={_host, _user, _pass};
}

dbquery connection::generate_query() {

	if(!is_connected()) {
		throw exception("Unable to send query: database is disconnected");
	}

	return dbquery(conn->createStatement());
}

prepared_query connection::generate_prepared_query(const std::string& _qstr) {

	if(!is_connected()) {
		throw exception("Unable to send query: database is disconnected");
	}

	try {
		return prepared_query(conn->prepareStatement(_qstr), _qstr);
	}
	catch(std::exception& e) {

		std::string err=std::string(e.what())+
			+" for prepared execution '"
			+_qstr
			+"'";

		throw exception(err);
	}
}

resultset connection::query(dbquery& _c, const std::string& _qstr) {

	if(!is_connected()) {
		throw exception("Unable to send query: database is disconnected");
	}

	return _c.query(_qstr);
}

resultset connection::query(prepared_query& _c) {

	if(!is_connected()) {
		throw exception("Unable to send query: database is disconnected");
	}

	return _c.query();
}

resultset connection::query(const std::string& _qstr) {

	if(!is_connected()) {
		throw exception("Unable to send query: database is disconnected");
	}

	auto q=generate_query();
	return q.query(_qstr);
}

int connection::execute(dbquery& _c, const std::string& _qstr) {

	if(!is_connected()) {
		throw exception("Unable to send query: database is disconnected");
	}

	return _c.execute(_qstr);
}

int connection::execute(prepared_query& _c) {

	if(!is_connected()) {
		throw exception("Unable to send query: database is disconnected");
	}

	return _c.execute();
}

int connection::execute(const std::string& _qstr) {

	auto q=generate_query();
	return q.execute(_qstr);
}
